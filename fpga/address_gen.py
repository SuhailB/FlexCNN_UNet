import sys
import os

prj_path = 'D:/Winter2021/Research/FlexCNN/SDx_project/FlexCNN_opt'
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



inSizeList = []
outSizeList = []
inPadding = []
outPadding = []
for instDict in instDicts:
  inSizeList.append(instDict['IN_NUM_HW']*instDict['IN_H_HW']*instDict['IN_W_HW'])
  outSizeList.append(instDict['OUT_NUM_HW']*instDict['OUT_H_HW']*instDict['OUT_W_HW'])
  inPad = (instDict['IN_H_HW']-instDict['IN_H'])/2
  inPadding.append(instDict['IN_NUM_HW']*(instDict['IN_H_HW']*inPad+inPad))
  outPad = (instDict['OUT_H_HW']-instDict['OUT_H'])/2
  outPadding.append(instDict['OUT_NUM_HW']*(instDict['OUT_H_HW']*outPad+outPad))
# print(inPadding)
# print(outPadding)


cinAddressList = []
coutAddressList = []

startAddress = instDicts[0]['CIN_OFFSET']

cinAddressList.append(startAddress)
coutAddressList.append(cinAddressList[0]+inSizeList[0]+inSizeList[1])

cinAddressList.append(startAddress+inSizeList[0])#outPadding[0]
coutAddressList.append(coutAddressList[0]+outSizeList[0]+outPadding[1])

cinAddressList.append(coutAddressList[1]-inPadding[2])
coutAddressList.append(cinAddressList[2]+inSizeList[2]+outPadding[2])

cinAddressList.append(coutAddressList[2]-inPadding[3])
coutAddressList.append(cinAddressList[3]+inSizeList[3]+outPadding[3])

cinAddressList.append(coutAddressList[3]-inPadding[4])
coutAddressList.append(cinAddressList[4]+inSizeList[4]+outPadding[4])

# print(cinAddressList)
# print(coutAddressList)
# for num in cinAddressList:
#   print(int(num))

for i in range(5):
  print(int(cinAddressList[i]), int(coutAddressList[i]))
# cinAddressList.append(startAddress)
# coutAddressList.append(startAddress+inSizeList[0]+inSizeList[1])


# # for instDict in instDicts:
# #   print(instDict)
# # targetlayerIndex = int(sys.argv[1])
# # sourcelayerIndex = int(sys.argv[2])
# # target_inst = instDicts[targetlayerIndex-1]
# # source_inst = instDicts[sourcelayerIndex-1]


# # def add(source_inst, target_inst):
# #   padding = (source_inst['FILTER_S2']-1)/2
# #   offset = source_inst['COUT_OFFSET']-(source_inst['OUT_W_HW']*padding+padding)*source_inst['OUT_NUM_HW']
# #   return offset
# # print(get_CIN_OFFSET(source_inst, target_inst))