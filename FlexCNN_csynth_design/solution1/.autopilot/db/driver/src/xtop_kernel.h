// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XTOP_KERNEL_H
#define XTOP_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xtop_kernel_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XTop_kernel_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XTop_kernel;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XTop_kernel_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XTop_kernel_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XTop_kernel_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XTop_kernel_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XTop_kernel_Initialize(XTop_kernel *InstancePtr, u16 DeviceId);
XTop_kernel_Config* XTop_kernel_LookupConfig(u16 DeviceId);
int XTop_kernel_CfgInitialize(XTop_kernel *InstancePtr, XTop_kernel_Config *ConfigPtr);
#else
int XTop_kernel_Initialize(XTop_kernel *InstancePtr, const char* InstanceName);
int XTop_kernel_Release(XTop_kernel *InstancePtr);
#endif

void XTop_kernel_Start(XTop_kernel *InstancePtr);
u32 XTop_kernel_IsDone(XTop_kernel *InstancePtr);
u32 XTop_kernel_IsIdle(XTop_kernel *InstancePtr);
u32 XTop_kernel_IsReady(XTop_kernel *InstancePtr);
void XTop_kernel_EnableAutoRestart(XTop_kernel *InstancePtr);
void XTop_kernel_DisableAutoRestart(XTop_kernel *InstancePtr);

void XTop_kernel_Set_global_cin(XTop_kernel *InstancePtr, u64 Data);
u64 XTop_kernel_Get_global_cin(XTop_kernel *InstancePtr);
void XTop_kernel_Set_global_prev_cin(XTop_kernel *InstancePtr, u64 Data);
u64 XTop_kernel_Get_global_prev_cin(XTop_kernel *InstancePtr);
void XTop_kernel_Set_global_cout(XTop_kernel *InstancePtr, u64 Data);
u64 XTop_kernel_Get_global_cout(XTop_kernel *InstancePtr);
void XTop_kernel_Set_global_weight(XTop_kernel *InstancePtr, u64 Data);
u64 XTop_kernel_Get_global_weight(XTop_kernel *InstancePtr);
void XTop_kernel_Set_global_bias(XTop_kernel *InstancePtr, u64 Data);
u64 XTop_kernel_Get_global_bias(XTop_kernel *InstancePtr);
void XTop_kernel_Set_layer_config(XTop_kernel *InstancePtr, u64 Data);
u64 XTop_kernel_Get_layer_config(XTop_kernel *InstancePtr);

void XTop_kernel_InterruptGlobalEnable(XTop_kernel *InstancePtr);
void XTop_kernel_InterruptGlobalDisable(XTop_kernel *InstancePtr);
void XTop_kernel_InterruptEnable(XTop_kernel *InstancePtr, u32 Mask);
void XTop_kernel_InterruptDisable(XTop_kernel *InstancePtr, u32 Mask);
void XTop_kernel_InterruptClear(XTop_kernel *InstancePtr, u32 Mask);
u32 XTop_kernel_InterruptGetEnabled(XTop_kernel *InstancePtr);
u32 XTop_kernel_InterruptGetStatus(XTop_kernel *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
