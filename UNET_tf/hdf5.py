import h5py
layers = h5py.File('recut_server.h5', 'r')

# print(layers.keys())

# layer1 = layers['conv2d_res0']
# print(layer1.keys())
for i in layers:
  for j in layers[i]:
    for k in layers[i][j]:
      for l in layers[i][j][k]:
        for m in layers[i][j][k][l]:
          print(type(layers[i][j][k][l][m]))