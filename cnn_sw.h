#include "util.h"
#define OUT_OFFSET2 1195088
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define FILTER_S2 1
#define LAYER 2
#define OUTFILE "/data/L2_outputs.dat"
#define OUT_OFFSET1 1186864
#define OUT_OFFSET2 1195088
#define CHANGE_LAYOUT 1
#define IN_NUM_HW 8
#define OUT_NUM_HW 32
#define IN_H_HW 256
#define IN_W_HW 256
#define OUT_H_HW 256
#define OUT_W_HW 256
#define IN_NUM 3
#define OUT_NUM 32
#define IN_H 256
#define IN_W 256
#define OUT_H 256
#define OUT_W 256
#define IN_NUM_T 8
#define OUT_NUM_T 32
#define IN_H_T 8
#define IN_W_T 64
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