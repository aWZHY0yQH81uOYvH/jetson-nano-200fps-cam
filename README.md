# Jetson Nano V4L2 driver modifications to add a 640x480 200FPS mode for the Sony IMX219 (Raspberry Pi Camera 2)
To enable this mode, you must recompile and install the L4T Linux kernel with the included modifications. `imx219_mode_tbls.h` adds a new set of image sensor register settings to enable this mode and re-enables the 720p binned mode that was removed for some reason. The modifications to the two .dtsi files are also necessary so the driver knows that these modes exist.

## Recompiling the kernel
To recompile the kernel, you'll need to download the sources from Nvidia (linked somewhere in their Jetpack downloads area) and download a cross-compilation toolchain. I followed [this guide](https://developer.ridgerun.com/wiki/index.php?title=Jetson_Nano/Development/Building_the_Kernel_from_Source). Once you have things downloaded, these are the commands I ran (obviously, substitute the things in [] for what they ask for):
```
TEGRA_KERNEL_OUT = [full path to]/Linux_for_Tegra/source/public/build
TOOLCHAIN_PREFIX = [full path to]/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
KERNEL_MODULES_OUT = [full path to]/Linux_for_Tegra/source/public/modules

cd Linux_for_Tegra/source/public
make -C kernel/kernel-4.9/ ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra CROSS_COMPILE=${TOOLCHAIN_PREFIX} tegra_defconfig
make -C kernel/kernel-4.9/ ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra CROSS_COMPILE=${TOOLCHAIN_PREFIX} -j[number of CPU cores you have]
make -C kernel/kernel-4.9/ ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra INSTALL_MOD_PATH=$KERNEL_MODULES_OUT modules_install

sudo cp build/arch/arm64/boot/Image [card root]/boot/Image
sudo rm -rf [card root]/boot/dtb/*
sudo cp -r build/arch/arm64/boot/dts/* [card root]/boot/dtb
sudo cp -r build/arch/arm64/boot/dts/* [card root]/boot
```

Once the files are copied to the SD card, you'll need to modify `/boot/extlinux/extlinux.conf` on the Jetson's filesystem to add `FDT /boot/tegra210-p3448-0000-p3449-0000-a02.dtb`. This makes the kernel load the device tree files we modified. You may need to use a different .dtb file for a different Jetson model. This one works for the Jetson Nano with SD card, but the compilation process generates ones for other boards too.

## About the new mode
The new mode is 640x480 pixels and should work at up to 200FPS. If you are displaying the images in realtime, you may get lower than that since Xorg tends to have a hard time keeping up. The sensor is set to 4x binning mode, which means 16 adjacent pixels are merged into one pixel on the output. Therefore the image is actually occupying 2560x1920 pixels on the sensor. This is less than the 3280x2464 active area since I wanted a standard resolution, so there's a bit of a crop (though it's much less of a crop than the 1280x720 modes). If you want the full sensor FOV, you can adjust all the register values and associated things in the other two device tree files. I've included a spreadsheet with my notes on the register values since I had to figure out how they worked based on the other modes.


If you are running a long ribbon cable, you may have some signal integrity problems (a few pixels are the wrong color). Either use a shorter ribbon cable or lower the frame rate and clock speed (which is currently maxed out based on what the datasheet says). Again, I've included my notes in a spreadsheet. A higher frame rate doesn't seem to be possible (without overclocking the sensor) because you need to read out a fixed number of pixels across it seems regardless of the horizontal resolution. If you want more FPS but a smaller image, you can reduce the number of rows.

## Getting frames
This mode is accessible through the V4L2 driver, for which there is documentation and some examples on the normal Linux kernel docs site. These are the main things you need to do to make this specific driver work:

1. Open `/dev/video0`
2. Set the `sensor_mode` control to 6 (see `v4l2-ctl --all` for the corresponding control ID number; mode 6 should be the 200FPS mode; see `v4l2-ctl --list-formats-ext` for the other available modes). Use `VIDIOC_S_EXT_CTRLS` with the control class `V4L2_CTRL_CLASS_CAMERA`.
3. Set the `bypass_mode` and `override_enable` controls to 0 (other camera reading things on the Jetson use these to bypass the driver)
4. Set the video format to 640x480 with the pixel format `V4L2_PIX_FMT_SRGGB10` using the `VIDIOC_S_FMT` IOCTL
5. Set up and queue whatever style of buffers you want (`VIDIOC_REQBUFS`/`VIDIOC_QBUF`). It seems like you need at least 4 buffers.
6. Start the stream (`VIDIOC_STREAMON`)
7. Dequeue buffers (acquired frames) and requeue them when you're done with `VIDIOC_DQBUF` and `VIDIOC_QBUF`
8. Set the gain and exposure after the stream starts. It seems like if you try to set them to a value they were already at before, it won't actually update (even if the image sensor has reset after restarting the stream). So, set the gain and exposure controls twice to two different values to make sure it actually updates. You can play with this while the stream is running with `v4l2-ctl -c`.


Whenever sending a struct to an IOCTL, remmeber to zero it out before and set as many of the parameters as you can (I've only mentioned the somewhat hard to figre out ones here).

## Interpreting the frames
The frames are returned directly from the image sensor in raw bayer RGGB 10-bit format. If you want a useful image, you'll need to debayer and white balance it yourself. This is relatively easy and fast if written in CUDA. The bayer pattern looks like this (two bytes per pixel in the returned data):
```
R G R G R G R G R G
G B G B G B G B G B
R G R G R G R G R G
G B G B G B G B G B
R G R G R G R G R G
```

I've found that you can use V4L2 user pointer buffer mode with pointers returned from `cudaMallocManaged` to read the camera sensor data directly into GPU-accessible memory for maximum performance (zero-copy). This zero-copy behavior and high level of control is why I went down this rabbit hole in the first place. I really don't understand why a low resolution mode like this wasn't included by default given the use cases for the Jetson. This was way more difficult that it needed to be.
