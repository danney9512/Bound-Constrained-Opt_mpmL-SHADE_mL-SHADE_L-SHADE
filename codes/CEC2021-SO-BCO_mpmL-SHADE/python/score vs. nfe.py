import numpy as np
import matplotlib.pyplot as plt
data = np.genfromtxt('score.csv', delimiter=',')
data = data[:, [0,1,3]]

plt.figure()
sg_list = [data[data[:,0]==k] for k in np.unique(data[:,0])]
for sg in sg_list:
    sg_x = []
    sg_y = []
    for row in sg:
        plt.cla()
        plt.clf()
        plt.xlabel('nFEs')
        plt.ylabel('Score')
        sg_x.append(row[1])
        sg_y.append(row[2])
    plt.gca().set_ylim([0, 10])
    plt.plot(sg_x, sg_y)
    plt.savefig('Run'+str(int(sg[0][0]))+'.png')
