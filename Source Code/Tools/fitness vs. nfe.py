import os
import matplotlib.pyplot as plt
import numpy as np
from numpy import genfromtxt
from matplotlib.ticker import FormatStrFormatter

def checkval(val):
    for i in range(10):
        if(val - 1.0 >= pow(10, -i)):
            return i
    return 10

filenames= os.listdir (".") # get all files' and folders' names in the current directory

result = []
for filename in filenames: # loop through all the files and folders
    if os.path.isdir(os.path.join(os.path.abspath("."), filename)): # check whether the current object is a folder or not
        result.append(filename)        
result.sort()

plt.figure()
ymin, ymax = [float(v) for v in input('Input the min and max of y axis :').split()]

total_data = []
for folder in result:
    data = genfromtxt(folder + '\\best_fitness.csv', delimiter=',')
    x_data = data[:, 0]
    y_data = data[:, 1]
    total_data.append([x_data, y_data])
    plt.cla()
    plt.clf()
    plt.xlabel('nFEs')
    plt.ylabel('fitness')
    axes = plt.gca()
    if ymin != -1 and ymax != -1:
        axes.set_ylim([ymin, ymax])
    plt.plot(x_data, y_data)
    plt.savefig(folder+'.png')


plt.cla()
plt.clf()
if ymin != -1 and ymax != -1:
    plt.gca().set_ylim([ymin, ymax])
plt.gcf().subplots_adjust(bottom=0.15)
plt.xticks(rotation=45)

for i, d in enumerate(total_data):
    if checkval(d[1][-1]) == 10: 
        plt.plot(d[0], d[1], color='red')
    else:
        plt.plot(d[0], d[1], color='green')
plt.savefig('total.png')
