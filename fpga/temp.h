#include "util.h"
#define LOAD_PROGRESS 1
#define SAVE_PROGRESS 1
#define PRJ_PATH "D:/Spring2021/recut/recut/fpga"
#define STRIDE 2
#define FILTER_S2 1
#define CIN_OFFSET 16959232
#define LAYER 15
#define OUTFILE "/data/L15_outputs.dat"
#define OUT_OFFSET1 17483520
#define OUT_OFFSET2 17483520
#define CHANGE_LAYOUT 1
#define IN_NUM_HW 128
#define OUT_NUM_HW 128
#define IN_H_HW 64
#define IN_W_HW 64
#define OUT_H_HW 32
#define OUT_W_HW 32
#define IN_NUM 128
#define OUT_NUM 128
#define IN_H 64
#define IN_W 64
#define OUT_H 32
#define OUT_W 32
#define IN_NUM_T 128
#define OUT_NUM_T 128
#define IN_H_T 8
#define IN_W_T 16
void instInit(uint* config);
void preprocess(
  data_t0* cin_hw,
  data_t1* weight_hw,
  data_t2* bias_hw,
  data_t0  outputs_sw[OUT_NUM][OUT_H][OUT_W]
);
void postprocess(
  data_t0* cin_hw,
  data_t0  outputs_hw[OUT_NUM][OUT_H][OUT_W],
  data_t0  outputs_py[OUT_NUM][OUT_H][OUT_W]
);
void compareResults(data_t0  outputs_hw[OUT_NUM][OUT_H][OUT_W], data_t0  outputs_sw[OUT_NUM][OUT_H][OUT_W]);
void save_progress(data_t0* cin_hw, uint data_offset);
void load_progress(data_t0* cin_hw);