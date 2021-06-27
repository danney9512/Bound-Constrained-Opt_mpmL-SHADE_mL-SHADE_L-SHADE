import os
import numpy as np
import matplotlib.pyplot as plt
import time


times = int(input('每隔幾筆畫一次: '))
start = time.time()
dirlists = [int(d) for d in os.listdir (".") if os.path.isdir(d)]
for d in dirlists:
    with open(str(d)+'//parameter.txt', 'r') as f:
        data = f.readlines()    
    nfe = [int(x) for x in data[0::7*times]]
    omf = [[float(y) for y in x.split()[1:]] for x in data[1::7*times]]
    omcr = [[float(y) for y in x.split()[1:]] for x in data[2::7*times]]
    mf = [[min(x), sum(x) / len(x), max(x)] for x in omf]
    mcr = [[min(x), sum(x) / len(x), max(x)] for x in omcr]
    saf = [[float(y) for y in x.split()[1:]] for x in data[3::7*times]]
    sacr = [[float(y) for y in x.split()[1:]] for x in data[4::7*times]]
    suf = [[float(y) for y in x.split()[1:]] for x in data[5::7*times]]
    sucr = [[float(y) for y in x.split()[1:]] for x in data[6::7*times]]

    fig = plt.figure(figsize=(13, 6), dpi=250)
    fig.suptitle('History Memory', fontsize=18)
    plt.subplot(1,2,1)
    plt.title('F values', fontsize=16)
    plt.xticks(rotation=18.375)
    plt.xlabel('nFEs', fontsize=16)
    plt.ylabel('value', fontsize=16)
    x = [nfe[i] for i, data in enumerate(mf) for j in range(len(data))]
    y = [val for data in mf for val in data]
    plt.scatter(x, y, c=['green', 'black', 'red'] * (len(y) // 3), marker='x', s=4)

    plt.subplot(1,2,2)
    plt.title('CR values', fontsize=16)
    plt.xticks(rotation=18.375)    
    plt.xlabel('nFEs', fontsize=16)
    plt.ylabel('value', fontsize=16)
    x = [nfe[i] for i, data in enumerate(mcr) for j in range(len(data))]
    y = [val for data in mcr for val in data]
    plt.scatter(x, y, c=['green', 'black', 'red'] * (len(y) // 3), marker='x', s=4)
    plt.savefig('memory run '+str(d)+'.png')

    plt.clf()
    fig = plt.figure(figsize=(13, 6), dpi=250)
    fig.suptitle('Parameter Evolution', fontsize=18)
    plt.subplot(1,2,1)
    plt.title('F values', fontsize=16)
    plt.xticks(rotation=18.375)
    plt.xlabel('nFEs', fontsize=16)
    plt.ylabel('value', fontsize=16)
    x = [nfe[i] for i, data in enumerate(saf) for j in range(len(data))]
    y = [val for data in saf for val in data]
    plt.scatter(x, y, c='green', marker='x', s=4)
    x = [nfe[i] for i, data in enumerate(suf) for j in range(len(data))]
    y = [val for data in suf for val in data]
    plt.scatter(x, y, c='black', marker='x', s=4)

    plt.subplot(1,2,2)
    plt.title('CR values', fontsize=16)
    plt.xticks(rotation=18.375)
    plt.xlabel('nFEs', fontsize=16)
    plt.ylabel('value', fontsize=16)
    x = [nfe[i] for i, data in enumerate(sacr) for j in range(len(data))]
    y = [val for data in sacr for val in data]
    plt.scatter(x, y, c='green', marker='x', s=4)
    x = [nfe[i] for i, data in enumerate(sucr) for j in range(len(data))]
    y = [val for data in sucr for val in data]
    plt.scatter(x, y, c='black', marker='x', s=4)

    plt.savefig('parameter run '+str(d)+'.png')
    plt.close('all')
    
end = time.time()
print(end - start)
