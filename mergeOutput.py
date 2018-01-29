import csv
from os import listdir
from os.path import isfile, join
from math import log

rootDir = 'data_xtimesy/'
fileList = [f for f in listdir(rootDir) if isfile(join(rootDir, f))]

completeDataset = []

for fileIndex, file in enumerate(fileList):
	filePath = rootDir + file
	incrementLimit = float(file.split('.c')[0].split('_')[1]) / 1000.0
	print(incrementLimit)
	completeDataset.append([file, filePath, [], [], [], incrementLimit])
	print(filePath)
	with open(filePath, 'r') as csvfile:
		csvreader = list(csv.reader(csvfile, delimiter=',', quotechar='|'))
		rowIndex = 0
		for row in csvreader:
			rowIndex += 1
			if rowIndex == 1 or rowIndex == 2:
				continue
			completeDataset[fileIndex][2].append(float(row[1]))
			completeDataset[fileIndex][3].append(float(row[2]))
			completeDataset[fileIndex][4].append(float(row[3]))


for dataBatch in completeDataset:
	doubleMax = max(dataBatch[3])
	dataBatch[3] = [(x / doubleMax) * 100.0 for x in dataBatch[3]]
	#dataBatch[4] = [(x / doubleMax) * 100.0 for x in dataBatch[4]]

accumulator = 0
with open('merged.csv', 'w') as outFile:
	outFile.write('Iteration Count, Double Sum')
	for fileName, _, _, _, _, incrementLimit in completeDataset:
		if incrementLimit == 0: 
			outFile.write(", 2^0")
		else:
			outFile.write(', 2^' + str(int(round(log(incrementLimit, 2), 0))))

	outFile.write('\n')
	for index, _ in enumerate(completeDataset[0][2]):
		accumulator += 25
		outFile.write(str(accumulator) + ", " + str(completeDataset[0][3][index]))
		for entry in completeDataset:
			outFile.write(", " + str(entry[4][index]))
		outFile.write('\n')
