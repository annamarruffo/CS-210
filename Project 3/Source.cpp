#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//display menu to the screen and get user input
int displayMenu() {

	int userInput;

	try {
		cout << "1: Display list of items purchased and the amount." << endl;
		cout << "2: Display how many times a given item was purchased on a given day" << endl;
		cout << "3: Display a histogram of all items purchased and a representation of how many times each item was purchased." << endl;
		cout << "4: Quit Program." << endl;
		cin >> userInput;

		//check if input is valid
		if (cin.fail()) {
			cin.clear();
			cin.ignore();

			//if not valid throw exception
			throw ("Please enter an Integer 1-4");
		}

		//check if input is valid
		if ((userInput < 1) || (userInput > 4)) {
			cin.clear();
			cin.ignore();

			//if not valid throw exception
			throw (userInput);

		}
	}

	//catch exception and recall func to get new input
	catch (int num) {
		cout << num << " is invalid. Please try again." << endl;
		displayMenu();
	}
	
	//catch exception and recll func to get new input
	catch (const char* exception) {
		cout << exception << endl;
		displayMenu();
	}

	
	return userInput;
}

string getInput() {
	
	string userItem;
	bool itemInList;
	try {
		cout << "Please enter an item: " << endl;
		cin >> userItem;

		//check if useritem is in the text file
		itemInList = callIntFunc("checkIteminList", userItem);

		//check if input is valid
		if (itemInList == false) {
			cin.clear();
			cin.ignore();
			throw (userItem);
		}

		//check if input is valid
		if (itemInList == true) {
			return userItem;
		}
	}
	catch (string item) {
		cout << item << " is invalid. Try again." << endl;
		getInput();
	}
}

void printStars(int num) {
	int i;

	//print stars 
	for (i = 0; i < num; ++i) {
		cout << "*";
	}

}

void openAndReadFile() {
	ifstream myfile;
	string item;
	int itemCount;

	//open file
	myfile.open("frequency.dat");

	//check if file is open
	if (myfile.is_open()) {

		//read until end of file
		while (!myfile.fail()) {
			myfile >> item;
			myfile >> itemCount;
			cout << left << setw(15) << item;
			printStars(itemCount);
			cout << endl;
		}
	}
}

void main(){
	int userInput;
	string userItem;

	userInput = displayMenu();
	
	//check if user entered 4
	while (userInput != 4) {

		//check if user entered 1
		if (userInput == 1) {

			CallProcedure("CountandDisplay");
			userInput = displayMenu();
		}

		//check if user entered 2
		if (userInput == 2) {
			userItem = getInput();
			int temp = callIntFunc("individualItemCount", userItem);
			userInput = displayMenu();
		}

		//check if user entered 3
		if (userInput == 3) {
			CallProcedure("countToFile");
			openAndReadFile();
			userInput = displayMenu();

			}

	}
		
}
