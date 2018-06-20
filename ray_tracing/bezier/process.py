
f = open("teapot.bpt", 'r')
n = int(f.readline())
for i in range(n):
    f.readline()
    filename = 'controlvoxel' + str(i) + '.txt'
    g = open(filename, 'w')
    for j in range(16):
        g.write(f.readline())
    g.close()
f.close()
        
    
