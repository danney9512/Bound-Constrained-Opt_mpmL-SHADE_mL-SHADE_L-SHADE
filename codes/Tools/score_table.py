from numpy import genfromtxt
import warnings
import os
import csv

def getScore(file):
	with warnings.catch_warnings():
		warnings.simplefilter("ignore")
		my_data = genfromtxt(file, delimiter=",")
	k = -1
	score = []
	tempScore = -1
	if (my_data.ndim == 1):
		if (my_data.size == 0):
			score.append(0)
		else:
			score.append(my_data[3])
	else:
		for row in my_data:
			if row[0] != k:
				k = row[0]
				if tempScore != -1:
					score.append(tempScore)
			tempScore = row[3]
	if tempScore != -1:
		score.append(tempScore)
	score.extend([0] * (50 - len(score)))
	return sorted(score, reverse=True)

sumScore = 0
scores = []
for dir in next(os.walk('.'))[1]:
	functionData = {}
	score = getScore(dir + "/score.csv")
	for i in range(0, 11):
		functionData[str(i)] = 0
	# print(len(score))
	for i in score:
		functionData[str(int(i))] = functionData[str(int(i))] + 1

	finalScore = sum(score[0:25])/25
	sumScore += finalScore
	scores.append([dir, functionData, finalScore])

Ackley = scores.pop(0)
scores.append(Ackley)

with open('table.csv', 'w', newline='') as csvfile:
	writer = csv.writer(csvfile)
	writer.writerow([0,1,2,3,4,5,6,7,8,9,10,'all'])
	for score in scores:
		row = []
		for i in range(0, 11):
			row.append(score[1][str(i)])
		row.append(score[2])
		writer.writerow(row)
		print (score[0] + " score: " + str(score[2]))
	writer.writerow([sumScore])
	print (str(sumScore))
input()