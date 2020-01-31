//progamming assignment 6c
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;


struct stdRecord
{
	string firstName;
	string lastName;
	double score;
};

//prototypes
void sortByScore(stdRecord myArray[], int numOfRecords);
void sortByName(stdRecord myArray[], int numOfRecords);

int main()
{
	int numStudents=0, indexChoice;
	stdRecord myStdRecords[100];
	double total=0, average, highest=0, lowest, newScore; //score array max 100 scores
	char menuOption;
	bool isInService=true;
	string filename, newName;
	ifstream fin;
	ofstream fout;

	do
	{
		cout << "-------------Student Scores File Input/Output-------------" << endl
			<< "Please select an option from the choices listed below: " << endl << endl
			<< "(K): Enter student information." << endl
			<< "(W): Write  to a file the number of students and the respective scores." << endl
			<< "(R): Read from a file the number of students and the respective scores." << endl
			<< "(D): Display all scores, and display the average, highest, and lowest scores." << endl
			<< "(M): Modify one of the scores." << endl
			<< "(S): Sort by Score." << endl
			<< "(N): Sort by Name." << endl
			<< "(Q): Quit the program." << endl;
		cin >> menuOption;

		switch (menuOption)
		{
			case 'k':
			{
				cout << "Please enter the number of students: ";
				cin >> numStudents;
				if (numStudents <= 100 && numStudents > 0)
					for (int k = 1; k <= numStudents; k++)
					{
						cout << "Please enter the first name for Student #" << k << ": ";
						cin >> myStdRecords[k].firstName;
						cout << "Please enter the last name for Student #" << k << ": ";
						cin >> myStdRecords[k].lastName;
						cout << "Please enter the score for Student #" << k << ": ";
						cin >> myStdRecords[k].score;
					}
				else
				{
					cout << "Invalid number. Please enter a number of 100 or less." << endl;
					continue;
				}
				cout << endl;
				break;
			}
			case 'w':
			{
				cout << "Please enter the name of a file into which you would like to\n"
					<< "save the currently recorded scores(no more than 20 characters): ";
				cin >> setw(20) >> filename;
				fout.open(filename.c_str());
				if (fout) //if file successfully opened
				{
					cout << "Now writing data to " << filename << "..." << endl;
					fout << numStudents << endl; //first value is number of students
					for (int k = 1; k <= numStudents; k++)
					{
						fout << myStdRecords[k].firstName << endl //all other values are the scores in the array
							 << myStdRecords[k].lastName << endl
							 << myStdRecords[k].score << endl;
					}
					fout.close();
					cout << endl << "Scores saved to " << filename << "." << endl << endl;
					break;
				}
				else
				{
					cout << "Error opening file." << endl;
					continue;
				}
			}
			case 'r':
			{
				cout << "Please enter the name of a file you would like to open: ";
				cin >> filename;
				fin.open(filename.c_str());
				if (fin)
				{
					fin >> numStudents;//reads the first line and adds it to numStudents
					cout << "Now reading data from " << filename << "..." << endl << endl
						<< "Number of students: " << numStudents << endl;
					for (int k = 1; k <= numStudents; k++)
					{
						cout << "Student #" << k << "\t";
						fin >> myStdRecords[k].firstName;//all other values are the scores in the array
						fin >> myStdRecords[k].lastName;
						fin	>> myStdRecords[k].score;
						cout << myStdRecords[k].firstName << " " 
							 << myStdRecords[k].lastName << "\t" 
							 << myStdRecords[k].score << endl;
					}
				fin.close();
				cout << endl;
				break;
				}
				else
				{
					cout << "Error opening file." << endl;
					continue;
				}
				
			}
			case 'd':
			{
				total = 0;
				lowest = myStdRecords[1].score; //initializes lowest to the second value in the array
				cout << "------Student Scores------" << endl
					<< "Number of students: " << numStudents << endl;
					for (int k = 1; k <= numStudents; k++) //display all scores and calculate average
					{
						cout << "Student #" << k << "\t"
							<< myStdRecords[k].firstName << " "
							<< myStdRecords[k].lastName << "\t"
							<< myStdRecords[k].score << endl;
						total+=myStdRecords[k].score; //adds the score array value to total
						if (myStdRecords[k].score>highest)//finds highest value
						highest=myStdRecords[k].score;
						if (myStdRecords[k].score<lowest)//finds lowest value
							lowest = myStdRecords[k].score;
					}
				cout << endl;
				average = total/numStudents;
				cout << "Highest score: " << highest << endl
					 << "Lowest score:  " << lowest << endl 
					 << "Average score: " << average << endl << endl;
				break;	
			}
			case 'm':
			{
				cout << "Please enter the number of the student whose score\nyou would like to modify: ";
				cin >> indexChoice;
				if (indexChoice<=numStudents&&indexChoice>0)
				{
				cout << "-----CURRENT INFO-----" << endl
					<< "Student #" << indexChoice << "\t" << myStdRecords[indexChoice].firstName
					<< " " << myStdRecords[indexChoice].lastName
					<< "\t" << myStdRecords[indexChoice].score << endl
					<< "Please reenter first name for Student #" << indexChoice << ": ";
				cin >> newName;
				myStdRecords[indexChoice].firstName = newName;
				cout << "Please reenter last name for Student #" << indexChoice << ": ";
				cin >> newName;
				myStdRecords[indexChoice].lastName = newName;
				cout << "Please enter new score for Student #" << indexChoice << ": ";
				cin >> newScore;
				myStdRecords[indexChoice].score = newScore;

				cout << "-------NEW INFO-------" << endl
					 << "Student #" << indexChoice << "\t"
					 << myStdRecords[indexChoice].firstName << " "
					 << myStdRecords[indexChoice].lastName << "\t"
					 << myStdRecords[indexChoice].score << endl << endl;
				break;
				}
				else
				{
					cout << "Invalid index." << endl;
					continue;
				}
			}
			case 's':
			{
				sortByScore(myStdRecords, numStudents);
				cout << "Records have been sorted by score." << endl;
				break;
			}
			case 'n':
			{
				sortByName(myStdRecords, numStudents);
				cout << "Records have been sorted by name." << endl;
				break;
			}
			default:
			{
				cout << "Would you like to save your information to a file before exiting?(y/n): ";
				cin >> menuOption;
				if (menuOption == 'y')
				{
					cout << "Please enter the name of a file into which you would like to\n"
						<< "save the currently recorded scores(no more than 20 characters): ";
					cin >> setw(20) >> filename;
					fout.open(filename.c_str());
					if (fout) //if file successfully opened
					{
						cout << "Now writing data to " << filename << "..." << endl;
						fout << numStudents << endl; //first value is number of students
						for (int k = 1; k <= numStudents; k++)
						{
							fout << myStdRecords[k].firstName << endl //all other values are the scores in the array
								<< myStdRecords[k].lastName << endl
								<< myStdRecords[k].score << endl;
						}
						fout.close();
						cout << endl << "Scores saved to " << filename << "." << endl << endl;
						isInService = false;
						break;
					}
					else
					{
						cout << "Error opening file." << endl;
						continue;
					}
				}
				else
				{
					cout << "Now exiting program..." << endl;
					isInService = false;
					break;
				}
			}
		}
	} while (isInService);

	return 0;
}

void sortByScore(stdRecord myArray[], int numOfRecords)
{
	double temp;
	bool flag = true;

	for (int k = 1; (k <= numOfRecords) && flag; k++) //iterates through all records
	{
		flag = false;
		for (int i = 0; i < (numOfRecords - 1); i++) //for each record, iterate through each myArray[k].score
		{
			if (myArray[k].score>=myArray[k+1].score) //if this score is greater than the score next to it
			{
				temp = myArray[k].score;
				myArray[k].score = myArray[k+1].score;
				myArray[k+1].score = temp; //^switch the two scores
				flag = true;
			}
		}
	}
	for (int k = 1; k <= numOfRecords; k++) //display all scores and calculate average
	{
		cout << "Student #" << k << "\t"
			<< myArray[k].firstName << " "
			<< myArray[k].lastName << "\t"
			<< myArray[k].score << endl;
	}
	cout << endl;
}


void sortByName(stdRecord myArray[], int numOfRecords)
{
	string tempF, tempL;
	bool flag = true;
	double tempS;

	for (int k = 1; (k <= numOfRecords) && flag; k++)
	{
		flag = false;
		for (int i = 0; i < (numOfRecords - 1); i++)
		{
			if ((myArray[k].lastName > myArray[k + 1].lastName) || //if last names are different
				((myArray[k].lastName == myArray[k + 1].lastName) && 
				(myArray[k].firstName >= myArray[k + 1].firstName))) //or if last names are the same and first names are different
			{
				tempF = myArray[k].firstName;
				tempL = myArray[k].lastName;
				tempS = myArray[k].score;
				myArray[k].firstName = myArray[k + 1].firstName;
				myArray[k].lastName = myArray[k + 1].lastName;
				myArray[k].score = myArray[k + 1].score;
				myArray[k + 1].firstName = tempF;
				myArray[k + 1].lastName = tempL;
				myArray[k + 1].score = tempS;
				flag = true; //^swaps all array values with corresponding array values
			}
		}
	}
	for (int k = 1; k <= numOfRecords; k++) //display all scores and calculate average
	{
		cout << "Student #" << k << "\t"
			<< myArray[k].firstName << " "
			<< myArray[k].lastName << "\t"
			<< myArray[k].score << endl;
	}
	cout << endl;
}
