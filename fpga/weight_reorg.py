
import sys
import os
import math
import numpy as np

prj_path = 'D:/Spring2021/recut/recut/fpga'
layerIndex = int(sys.argv[1])


instFile = open('address.insts', 'r')
lines = instFile.readlines()

insts = []

for i in range(0,layerIndex):
  inst = []
  for line in range(0,6):
    instLine = lines[i*7+line].split()
    for num in instLine:
      inst.append(int(num))
  insts.append(inst)

instDicts = []

for inst in insts:
  instDict = {}
  instDict['IN_NUM_HW'	      ] = inst[0 ]
  instDict['OUT_NUM_HW'	      ] = inst[1 ]
  instDict['IN_H_HW'		      ] = inst[2 ]
  instDict['IN_W_HW'		      ] = inst[3 ]
  instDict['OUT_H_HW'		      ] = inst[4 ]
  instDict['OUT_W_HW'		      ] = inst[5 ]
  instDict['IN_NUM'			      ] = inst[6 ]
  instDict['OUT_NUM'		      ] = inst[7 ]
  instDict['IN_H'				      ] = inst[8 ]
  instDict['IN_W'				      ] = inst[9 ]
  instDict['OUT_H'			      ] = inst[10]
  instDict['OUT_W'			      ] = inst[11]
  instDict['CIN_OFFSET'	      ] = inst[12]
  instDict['WEIGHT_OFFSET'  	] = inst[13]
  instDict['BIAS_OFFSET'		  ] = inst[14]
  instDict['COUT_OFFSET'		  ] = inst[15]
  instDict['FILTER_S1'	    	] = inst[16]
  instDict['FILTER_S2'		    ] = inst[17]
  instDict['STRIDE'			      ] = inst[18]
  instDict['EN'				        ] = inst[19]
  instDict['PREV_CIN_OFFSET'	] = inst[20]
  instDict['IN_NUM_T'			    ] = inst[21]
  instDict['OUT_NUM_T'		    ] = inst[22]
  instDict['IN_H_T'			      ] = inst[23]
  instDict['IN_W_T'			      ] = inst[24]
  instDict['BATCH_NUM'		    ] = inst[25]
  instDict['TASK_NUM1'		    ] = inst[26]
  instDict['TASK_NUM2'		    ] = inst[27]
  instDict['LOCAL_ACCUM_NUM'	] = inst[28]
  instDict['LOCAL_REG_NUM'	  ] = inst[29]
  instDict['ROW_IL_FACTOR'	  ] = inst[30]
  instDict['COL_IL_FACTOR'	  ] = inst[31]
  instDict['CONV_TYPE'		    ] = inst[32]
  instDict['FILTER_D0'		    ] = inst[33]
  instDict['FILTER_D1'		    ] = inst[34]
  instDict['DILATION_RATE'	  ] = inst[35]
  instDict['TCONV_STRIDE'		  ] = inst[36]
  instDict['K_NUM'			      ] = inst[37]
  instDict['KH_KW'			      ] = inst[38]
  instDicts.append(instDict)

inst = instDicts[0]

in_num = inst['IN_NUM']
in_num_t = inst['IN_NUM_T']
out_num = inst['OUT_NUM']
out_num_t = inst['OUT_NUM_T']
filter_s = inst['FILTER_S2']

weights_reorg = []

instFile = open('weights_in.dat', 'r')
weights_in = instFile.readlines()

##in  data layout (1, 1, 128, 1, 1, 64)
##out data layout (2, 2, 64, 1, 1, 32)


weights_raw = np.zeros((out_num, filter_s, filter_s, in_num))
for o in range(out_num):
  for p in range(filter_s):
    for q in range(filter_s):
      for i in range(in_num):
        L4 = o*filter_s*filter_s*in_num
        L3 = p*filter_s*in_num
        L2 = q*in_num
        L1 = i
        index = L4 + L3 + L2 + L1
        weights_raw[o][p][q][i] = float(weights_in[index])

# weights_raw = np.reshape(weights_raw, (2, 2, 64, 1, 1, 32))
# weights_raw.tofile(prj_path + "/weights_out_1.dat", sep="\n", format="%s")

weights_reorg = np.zeros((int(math.ceil(float(out_num) / out_num_t)), int(math.ceil(float(in_num) / in_num_t)), out_num_t, filter_s, filter_s, in_num_t))
for o1 in range(int(math.ceil(float(out_num) / out_num_t))):
  for i1 in range(int(math.ceil(float(in_num) / in_num_t))):
    for o2 in range(out_num_t):
      for p in range(filter_s):
        for q in range(filter_s):
          for i2 in range(in_num_t):
            # L6 = o1*int(math.ceil(float(in_num) / in_num_t))*out_num_t*filter_s*filter_s*in_num_t
            # L5 = i1*out_num_t*filter_s*filter_s*in_num_t
            # L4 = o2*filter_s*filter_s*in_num_t
            # L3 = p*filter_s*in_num_t
            L2 = o1*out_num_t+o2
            L1 = i1*in_num_t+i2
            # index = L6 + L5 + L4 + L3 + L2 + L1

            # print(index)
            if (o1 * out_num_t + o2 < out_num) and (i1 * in_num_t + i2 < in_num):
              weights_reorg[o1][i1][o2][p][q][i2] = weights_raw[L2][p][q][L1]
            else:
              weights_reorg[o1][i1][o2][p][q][i2] = float(0.0)

weights_reorg.tofile(prj_path + "/weights_out.dat", sep="\n", format="%s")
# # print(weights_reorg)
# # # print(weights_reorg)
# # # weights_reorg = np.array(weights_reorg)
# # for i in range(len(weights_raw)):
# #   if((weights_reorg[i]-float(weights_raw[i]))!=0):
# #     print('error')
#   # print()
# # print(weights_reorg)