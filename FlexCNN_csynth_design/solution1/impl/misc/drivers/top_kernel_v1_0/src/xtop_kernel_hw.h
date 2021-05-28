// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of global_cin
//        bit 31~0 - global_cin[31:0] (Read/Write)
// 0x14 : Data signal of global_cin
//        bit 31~0 - global_cin[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of global_prev_cin
//        bit 31~0 - global_prev_cin[31:0] (Read/Write)
// 0x20 : Data signal of global_prev_cin
//        bit 31~0 - global_prev_cin[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of global_cout
//        bit 31~0 - global_cout[31:0] (Read/Write)
// 0x2c : Data signal of global_cout
//        bit 31~0 - global_cout[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of global_weight
//        bit 31~0 - global_weight[31:0] (Read/Write)
// 0x38 : Data signal of global_weight
//        bit 31~0 - global_weight[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of global_bias
//        bit 31~0 - global_bias[31:0] (Read/Write)
// 0x44 : Data signal of global_bias
//        bit 31~0 - global_bias[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of layer_config
//        bit 31~0 - layer_config[31:0] (Read/Write)
// 0x50 : Data signal of layer_config
//        bit 31~0 - layer_config[63:32] (Read/Write)
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XTOP_KERNEL_CONTROL_ADDR_AP_CTRL              0x00
#define XTOP_KERNEL_CONTROL_ADDR_GIE                  0x04
#define XTOP_KERNEL_CONTROL_ADDR_IER                  0x08
#define XTOP_KERNEL_CONTROL_ADDR_ISR                  0x0c
#define XTOP_KERNEL_CONTROL_ADDR_GLOBAL_CIN_DATA      0x10
#define XTOP_KERNEL_CONTROL_BITS_GLOBAL_CIN_DATA      64
#define XTOP_KERNEL_CONTROL_ADDR_GLOBAL_PREV_CIN_DATA 0x1c
#define XTOP_KERNEL_CONTROL_BITS_GLOBAL_PREV_CIN_DATA 64
#define XTOP_KERNEL_CONTROL_ADDR_GLOBAL_COUT_DATA     0x28
#define XTOP_KERNEL_CONTROL_BITS_GLOBAL_COUT_DATA     64
#define XTOP_KERNEL_CONTROL_ADDR_GLOBAL_WEIGHT_DATA   0x34
#define XTOP_KERNEL_CONTROL_BITS_GLOBAL_WEIGHT_DATA   64
#define XTOP_KERNEL_CONTROL_ADDR_GLOBAL_BIAS_DATA     0x40
#define XTOP_KERNEL_CONTROL_BITS_GLOBAL_BIAS_DATA     64
#define XTOP_KERNEL_CONTROL_ADDR_LAYER_CONFIG_DATA    0x4c
#define XTOP_KERNEL_CONTROL_BITS_LAYER_CONFIG_DATA    64

