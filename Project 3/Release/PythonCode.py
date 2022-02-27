import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def readFile():

	#open file for reading
	myfile = open('InputFile.txt')

	#read lines to a list
	groceryList = myfile.read().splitlines()

	#close the file
	myfile.close()
	
	#return the list
	return groceryList
	

def CountandDisplay():
	groceryDict = {}
	groceryList = readFile()

	#get an item from the list
	for i in range(len(groceryList)):
		
		#check if item is already in the dictionary and if it is add 1
		if groceryList[i] in groceryDict:
			groceryDict[groceryList[i]] += 1

			#if not then value equals 1
		else:
			groceryDict[groceryList[i]] = 1

			#print the dictionary
	for key, value in groceryDict.items():
		print (key, ':', value)

def checkIteminList(userItem):
	
	#open and read file
	groceryList = readFile()
	
	#check if userItem is in groceryList
	if userItem in groceryList:
		return True
	return False

def individualItemCount(userItem):
	groceryList = readFile()
	count = 0
	
	#count how many times i appears in groceryList
	for i in groceryList:
		if i.strip() == userItem:
			count += 1

	print (userItem, ':', count)
	return 0

def countToFile():
	groceryDict = {}
	groceryList = readFile()

	#get an item from the list
	for i in range(len(groceryList)):
		
		if groceryList[i] in groceryDict:
			groceryDict[groceryList[i]] += 1
		else:
			groceryDict[groceryList[i]] = 1
	
	#open file
	myfile = open("frequency.dat", "w")

	#iterate through dictionary and write to file
	for key, value in groceryDict.items():
		myfile.write('%s %s\n' % (key, value))

		#close file
	myfile.close()