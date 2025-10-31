#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

bool validInput(char* &str);

int main() {
	
	cout << "Opening file..." << endl;	

	//open file
	ifstream piFile("pi.txt");
	
	//vector to store true int values
	vector<int> pi;

	cout << "Storing numbers..." << endl;

	//goes through the file and adds all numbers
	while(true) {

		//saves current number
		int num = piFile.get() - 48;

		//adds it if its a number from 0-9
		if (num >= 0 && num <= 9) {
		
			pi.push_back(num);
		}

		//checks to see if the end of the file has been reached
		if (num == -49) {
			break;
		}
	}

	cout << "Stored " << pi.size() << " digits of pi." << endl;

	while (true) {

		cout << endl << endl;
		
		//ask for number from user
		char* num = new char[21];
		
		do {
	
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
			}
			cout << "Enter your number (max 20 digits):" << endl;
			cin.get(num, 21);

		} while(cin.fail() || !validInput(num) || strlen(num) == 0);


		bool matchFound = false;	

		//go through pi and see if there are any matches
		for (int i = 0; i < pi.size(); i++) {

			
			//check for match
			for (int j = 0; j < strlen(num); j++) {
				
				/*
				if (i + j > strlen(num) - 1) {
					cout << "Overflow break" << endl;		
					break;
				}
				*/
				if (pi.at(i + j) != num[j] - 48) {
					break;
				}
				if (j == strlen(num) - 1) {
					//full match found!!!
					cout << endl << "Match found from indexs " << i << " to " << (i + j) << "." << endl;
					matchFound = true;
					break;
				}
			}

			//if a match has been found, break
			if (matchFound) {
				break;
			}	


		}

		if (!matchFound) {
			cout << endl << "No match was found in the first " << pi.size() << " digits of pi." << endl;
		}	


	}
	return 0;
}

bool validInput(char* &str) {

	//check that everything is a number
	for (int i = 0; i < strlen(str); i++) {
		if ((int)str[i] < 48 || (int)str[i] > 57) {
			cout << "Invalid input, try again." << endl;
			str = new char[21];
			return false;
		}
	}
	return true;
}
