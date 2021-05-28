local_file = open('output_local.dat', 'r')
remote_file = open('output_remote.dat', 'r')

l_lines = local_file.readlines()
r_lines = remote_file.readlines()
for i in range(len(l_lines)):
  if(abs(float(l_lines[i])-float(r_lines[i]))>0.000001):
    print('error at :' + str(i))
print('success')