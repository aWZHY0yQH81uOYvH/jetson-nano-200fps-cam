/*
 * imx219_tables.h - sensor mode tables for imx219 HDR sensor.
 *
 * Copyright (c) 2015-2020, NVIDIA CORPORATION, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __IMX219_I2C_TABLES__
#define __IMX219_I2C_TABLES__

#define IMX219_TABLE_WAIT_MS	0
#define IMX219_TABLE_END	1

#define imx219_reg struct reg_8

static imx219_reg imx219_start_stream[] = {
	{0x0100, 0x01},
	{IMX219_TABLE_WAIT_MS, 3},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_stop_stream[] = {
	{0x0100, 0x00},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_common[] = {
	{IMX219_TABLE_WAIT_MS, 10},
	/* software reset */
	{0x0103, 0x01},
	/* sensor config */
	{0x0114, 0x01}, /* D-Phy, 2-lane */
	{0x0128, 0x00},
	{0x012A, 0x18}, /* 24 MHz INCK */
	{0x012B, 0x00},
	/* access code - vendor addr. ranges */
	{0x30EB, 0x05},
	{0x30EB, 0x0C},
	{0x300A, 0xFF},
	{0x300B, 0xFF},
	{0x30EB, 0x05},
	{0x30EB, 0x09},
	/* cis tuning */
	{0x455E, 0x00},
	{0x471E, 0x4B},
	{0x4767, 0x0F},
	{0x4750, 0x14},
	{0x4540, 0x00},
	{0x47B4, 0x14},
	{0x4713, 0x30},
	{0x478B, 0x10},
	{0x478F, 0x10},
	{0x4793, 0x10},
	{0x4797, 0x0E},
	{0x479B, 0x0E},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_3264x2464_21fps[] = {
	/* capture settings */
	{0x0157, 0x00}, /* ANALOG_GAIN_GLOBAL[7:0] */
	{0x015A, 0x09}, /* COARSE_INTEG_TIME[15:8] */
	{0x015B, 0xbd}, /* COARSE_INTEG_TIME[7:0] */
	/* format settings */
	{0x0160, 0x09}, /* FRM_LENGTH[15:8] */
	{0x0161, 0xC1}, /* FRM_LENGTH[7:0] */
	{0x0162, 0x0D}, /* LINE_LENGTH[15:8] */
	{0x0163, 0x78}, /* LINE_LENGTH[7:0] */
	{0x0164, 0x00},
	{0x0165, 0x08},
	{0x0166, 0x0C},
	{0x0167, 0xC7},
	{0x0168, 0x00},
	{0x0169, 0x00},
	{0x016A, 0x09},
	{0x016B, 0x9F},
	{0x016C, 0x0C},
	{0x016D, 0xC0},
	{0x016E, 0x09},
	{0x016F, 0xA0},
	{0x0170, 0x01},
	{0x0171, 0x01},
	{0x0174, 0x00},
	{0x0175, 0x00},
	{0x018C, 0x0A},
	{0x018D, 0x0A},
	{0x0264, 0x00},
	{0x0265, 0x08},
	{0x0266, 0x0C},
	{0x0267, 0xC7},
	{0x026C, 0x0C},
	{0x026D, 0xC0},
	/* clock dividers */
	{0x0301, 0x05},
	{0x0303, 0x01},
	{0x0304, 0x03},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x39},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030C, 0x00},
	{0x030D, 0x72},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_3264x1848_28fps[] = {
	/* capture settings */
	{0x0157, 0x00}, /* ANALOG_GAIN_GLOBAL[7:0] */
	{0x015A, 0x07}, /* COARSE_INTEG_TIME[15:8] */
	{0x015B, 0x55}, /* COARSE_INTEG_TIME[7:0] */
	/* format settings */
	{0x0160, 0x07}, /* FRM_LENGTH[15:8] */
	{0x0161, 0x59}, /* FRM_LENGTH[7:0] */
	{0x0162, 0x0D}, /* LINE_LENGTH[15:8] */
	{0x0163, 0x78}, /* LINE_LENGTH[7:0] */
	{0x0164, 0x00},
	{0x0165, 0x08},
	{0x0166, 0x0C},
	{0x0167, 0xC7},
	{0x0168, 0x01},
	{0x0169, 0x34},
	{0x016A, 0x08},
	{0x016B, 0x6B},
	{0x016C, 0x0C},
	{0x016D, 0xC0},
	{0x016E, 0x07},
	{0x016F, 0x38},
	{0x0170, 0x01},
	{0x0171, 0x01},
	{0x0174, 0x00},
	{0x0175, 0x00},
	{0x018C, 0x0A},
	{0x018D, 0x0A},
	{0x0264, 0x00},
	{0x0265, 0x08},
	{0x0266, 0x0C},
	{0x0267, 0xC7},
	{0x026C, 0x0C},
	{0x026D, 0xC0},
	/* clocks dividers */
	{0x0301, 0x05},
	{0x0303, 0x01},
	{0x0304, 0x03},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x39},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030C, 0x00},
	{0x030D, 0x72},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_1920x1080_30fps[] = {
	/* capture settings */
	{0x0157, 0x00}, /* ANALOG_GAIN_GLOBAL[7:0] */
	{0x015A, 0x06}, /* COARSE_INTEG_TIME[15:8] */
	{0x015B, 0xde}, /* COARSE_INTEG_TIME[7:0] */
	/* format settings */
	{0x0160, 0x06}, /* FRM_LENGTH[15:8] */
	{0x0161, 0xE2}, /* FRM_LENGTH[7:0] */
	{0x0162, 0x0D}, /* LINE_LENGTH[15:8] */
	{0x0163, 0x78}, /* LINE_LENGTH[7:0] */
	{0x0164, 0x02},
	{0x0165, 0xA8},
	{0x0166, 0x0A},
	{0x0167, 0x27},
	{0x0168, 0x02},
	{0x0169, 0xB4},
	{0x016A, 0x06},
	{0x016B, 0xEB},
	{0x016C, 0x07},
	{0x016D, 0x80},
	{0x016E, 0x04},
	{0x016F, 0x38},
	{0x0170, 0x01},
	{0x0171, 0x01},
	{0x0174, 0x00},
	{0x0175, 0x00},
	{0x018C, 0x0A},
	{0x018D, 0x0A},
	/* clocks dividers */
	{0x0301, 0x05},
	{0x0303, 0x01},
	{0x0304, 0x03},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x39},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030C, 0x00},
	{0x030D, 0x72},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_1640x1232_30fps[] = {
	/* capture settings */
	{0x0157, 0x00}, /* ANALOG_GAIN_GLOBAL[7:0] */
	{0x015A, 0x06}, /* COARSE_INTEG_TIME[15:8] */
	{0x015B, 0xA8}, /* COARSE_INTEG_TIME[7:0] */
	/* format settings */
	{0x0160, 0x06}, /* FRM_LENGTH[15:8] */
	{0x0161, 0xE2}, /* FRM_LENGTH[7:0] */
	{0x0162, 0x0D}, /* LINE_LENGTH[15:8] */
	{0x0163, 0x78}, /* LINE_LENGTH[7:0] */
	{0x0164, 0x00},
	{0x0165, 0x00},
	{0x0166, 0x0C},
	{0x0167, 0xCF},
	{0x0168, 0x00},
	{0x0169, 0x00},
	{0x016A, 0x09},
	{0x016B, 0x9F},
	{0x016C, 0x06},
	{0x016D, 0x68},
	{0x016E, 0x04},
	{0x016F, 0xD0},
	{0x0170, 0x01},
	{0x0171, 0x01},
	{0x0174, 0x01},
	{0x0175, 0x01},
	{0x018C, 0x0A},
	{0x018D, 0x0A},
	/* clocks dividers */
	{0x0301, 0x05},
	{0x0303, 0x01},
	{0x0304, 0x03},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x39},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030C, 0x00},
	{0x030D, 0x72},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_1280x720_60fps[] = {
	/* capture settings */
	{0x0157, 0x00}, /* ANALOG_GAIN_GLOBAL[7:0] */
	{0x015A, 0x03}, /* COARSE_INTEG_TIME[15:8] */
	{0x015B, 0x6c}, /* COARSE_INTEG_TIME[7:0] */
	/* format settings */
	{0x0160, 0x03}, /* FRM_LENGTH[15:8] */
	{0x0161, 0x70}, /* FRM_LENGTH[7:0] */
	{0x0162, 0x0D}, /* LINE_LENGTH[15:8] */
	{0x0163, 0x78}, /* LINE_LENGTH[7:0] */
	{0x0164, 0x01},
	{0x0165, 0x68},
	{0x0166, 0x0B},
	{0x0167, 0x67},
	{0x0168, 0x02},
	{0x0169, 0x00},
	{0x016A, 0x07},
	{0x016B, 0x9F},
	{0x016C, 0x05},
	{0x016D, 0x00},
	{0x016E, 0x02},
	{0x016F, 0xD0},
	{0x0170, 0x01},
	{0x0171, 0x01},
	{0x0174, 0x01},
	{0x0175, 0x01},
	{0x018C, 0x0A},
	{0x018D, 0x0A},
	/* clocks dividers */
	{0x0301, 0x05},
	{0x0303, 0x01},
	{0x0304, 0x03},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x39},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030C, 0x00},
	{0x030D, 0x72},
	{IMX219_TABLE_END, 0x00}
};


static imx219_reg imx219_mode_1280x720_120fps[] = {
	// capture settings
	{0x0157, 0x00}, // ANALOG_GAIN_GLOBAL[7:0]
	{0x015A, 0x01}, // COARSE_INTEG_TIME[15:8]
	{0x015B, 0x85}, // COARSE_INTEG_TIME[7:0]
	// format settings
	{0x0160, 0x01}, // FRM_LENGTH[15:8]
	{0x0161, 0x89}, // FRM_LENGTH[7:0]
	{0x0162, 0x0D}, // LINE_LENGTH[15:8]
	{0x0163, 0xE8}, // LINE_LENGTH[7:0]
	{0x0164, 0x01},
	{0x0165, 0x68},
	{0x0166, 0x0B},
	{0x0167, 0x67},
	{0x0168, 0x02},
	{0x0169, 0x00},
	{0x016A, 0x07},
	{0x016B, 0x9F},
	{0x016C, 0x05},
	{0x016D, 0x00},
	{0x016E, 0x02},
	{0x016F, 0xD0},
	{0x0170, 0x01},
	{0x0171, 0x01},
	{0x0174, 0x03},
	{0x0175, 0x03},
	{0x018C, 0x0A},
	{0x018D, 0x0A},
	// clocks dividers
	{0x0301, 0x05},
	{0x0303, 0x01},
	{0x0304, 0x03},
	{0x0305, 0x03},
	{0x0306, 0x00},
	{0x0307, 0x35},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030C, 0x00},
	{0x030D, 0x66},
	{IMX219_TABLE_END, 0x00}
};

static imx219_reg imx219_mode_640x480_180fps[] = {
	// capture settings
	{0x0157, 0x00}, // ANALOG_GAIN_GLOBAL[7:0]
	{0x015A, 0x01}, // COARSE_INTEGRATION_TIME_A[15:8]
	{0x015B, 0xF5}, // COARSE_INTEGRATION_TIME_A[7:0] supposed to be 4 less than FRM_LENGTH ================================================
	// format settings
	{0x0160, 0x01}, // FRM_LENGTH_A[15:8] (frame_length_lines; units are 1 line when BINNING_MODE is 0,1,2 or 2 lines when it's 3)
	{0x0161, 0xF9}, // FRM_LENGTH_A[7:0]
	{0x0162, 0x0D}, // LINE_LENGTH_A[15:8] (line_length_pck; units are pixels)
	{0x0163, 0x78}, // LINE_LENGTH_A[7:0]
	{0x0164, 0x01}, // X_ADD_STA_A[11:8] (x_addr_start; x address of the top left corner of pixel data)
	{0x0165, 0x68}, // X_ADD_STA_A[7:0]
	{0x0166, 0x0B}, // X_ADD_END_A[11:8] (x_addr_end; x address of the bottom right corner of pixel data)
	{0x0167, 0x67}, // X_ADD_END_A[7:0]
	{0x0168, 0x01}, // Y_ADD_STA_A[11:8] (y_addr_start; y address of the top left corner of pixel data)
	{0x0169, 0x10}, // Y_ADD_STA_A[7:0]
	{0x016A, 0x08}, // Y_ADD_END_A[11:8] (y_addr_end; y address of the bottom right corner of pixel data)
	{0x016B, 0x8F}, // Y_ADD_END_A[7:0]
	{0x016C, 0x02}, // x_output_size[11:8] (width of image data output from the sensor module)
	{0x016D, 0x80}, // x_output_size[7:0]
	{0x016E, 0x01}, // y_output_size[11:8] (height of image data output from the sensor module)
	{0x016F, 0xE0}, // y_output_size[7:0]
	{0x0170, 0x01}, // X_ODD_INC_A[2:0] (x_odd_inc; increment for odd pixels; 1 or 3)
	{0x0171, 0x01}, // Y_ODD_INC_A[2:0] (y_odd_inc; increment for odd pixels; 1 or 3)
	{0x0174, 0x02}, // BINNING_MODE_H_A (horizontal binning) (0 = none, 1 = 2x, 2 = 4x, 3 = 2x analog)
	{0x0175, 0x02}, // BINNING_MODE_V_A (vertical binning) (0 = none, 1 = 2x, 2 = 4x, 3 = 2x analog)
	{0x018C, 0x0A}, // CSI_DATA_FORMAT_A [15:8] (CSI data format; 0x0A0A = raw 10 bit, 0x0808 = raw 8 bit)
	{0x018D, 0x0A}, // CSI_DATA_FORMAT_A [7:0]
	// clocks dividers
	{0x0301, 0x05}, // VTPXCK_DIV[4:0] (vt_pix_clk_div; video timing pixel clock divider value)
	{0x0303, 0x01}, // VTSYCK_DIV[1:0] (vt_sys_clk_div; video timing system clock divider value)
	{0x0304, 0x03}, // PREPLLCK_VT_DIV[7:0] (pre_pll_clk_vt_div or prepllck_vt_div; pre-PLL clock video timing system divider; values 1, 2, 3?; should probably be left alone)
	{0x0305, 0x03}, // PREPLLCK_OP_DIV[7:0] (pre_pll_clk_op_div or prepllck_vt_div; pre-PLL clock output system divider value; values 1, 2, 3?; should probably be left alone)
	{0x0306, 0x00}, // PLL_VT_MPY[10:8] (pll_vt_multiplier; PLL video timing system multiplier value)
	{0x0307, 0x6D}, // PLL_VT_MPY[7:0]
	{0x0309, 0x0A}, // OPPXCK_DIV[4:0] (op_pix_clk_div; output pixel clock divider value)
	{0x030B, 0x01}, // OPSYCK_DIV[1:0] (op_sys_clk_div; output system clock divider value)
	{0x030C, 0x00}, // PLL_OP_MPY[10:8] (pll_op_multiplier; PLL output system multiplier value)
	{0x030D, 0xDA}, // PLL_OP_MPY[7:0]
	{IMX219_TABLE_END, 0x00}
};

enum {
	IMX219_MODE_3264x2464_21FPS,
	IMX219_MODE_3264x1848_28FPS,
	IMX219_MODE_1920x1080_30FPS,
	IMX219_MODE_1640x1232_30FPS,
	IMX219_MODE_1280x720_60FPS,
	IMX219_MODE_1280x720_120FPS,
	IMX219_MODE_640x480_180FPS,

	IMX219_MODE_COMMON,
	IMX219_START_STREAM,
	IMX219_STOP_STREAM,
};

static imx219_reg *mode_table[] = {
	[IMX219_MODE_3264x2464_21FPS] = imx219_mode_3264x2464_21fps,
	[IMX219_MODE_3264x1848_28FPS] = imx219_mode_3264x1848_28fps,
	[IMX219_MODE_1920x1080_30FPS] = imx219_mode_1920x1080_30fps,
	[IMX219_MODE_1640x1232_30FPS] = imx219_mode_1640x1232_30fps,
	[IMX219_MODE_1280x720_60FPS] = imx219_mode_1280x720_60fps,
	[IMX219_MODE_1280x720_120FPS] = imx219_mode_1280x720_120fps,
	[IMX219_MODE_640x480_180FPS] = imx219_mode_640x480_180fps,

	[IMX219_MODE_COMMON]  = imx219_mode_common,
	[IMX219_START_STREAM]  = imx219_start_stream,
	[IMX219_STOP_STREAM]  = imx219_stop_stream,
};

static const int imx219_21fps[] = {
	21,
};

static const int imx219_28fps[] = {
	28,
};

static const int imx219_30fps[] = {
	30,
};

static const int imx219_60fps[] = {
	60,
};

static const int imx219_120fps[] = {
	120,
};

static const int imx219_180fps[] = {
	180,
};



/*
 * WARNING: frmfmt ordering need to match mode definition in
 * device tree!
 */
static const struct camera_common_frmfmt imx219_frmfmt[] = {
	{{3264, 2464},	imx219_21fps, 1, 0, IMX219_MODE_3264x2464_21FPS},
	/* Add modes with no device tree support after below */
	{{3264, 1848},	imx219_28fps, 1, 0, IMX219_MODE_3264x1848_28FPS},
	{{1920, 1080},	imx219_30fps, 1, 0, IMX219_MODE_1920x1080_30FPS},
	{{1640, 1232},	imx219_30fps, 1, 0, IMX219_MODE_1640x1232_30FPS},
	{{1280, 720},	imx219_60fps, 1, 0, IMX219_MODE_1280x720_60FPS},
	{{1280, 720},	imx219_120fps, 1, 0, IMX219_MODE_1280x720_120FPS},
	{{640, 480},	imx219_180fps, 1, 0, IMX219_MODE_640x480_180FPS},
};

#endif /* __IMX219_I2C_TABLES__ */
