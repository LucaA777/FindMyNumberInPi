#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <tuple>
#include <string>


using namespace std;

bool validInput(char* &str);
tuple<int, int> findIndexInPi(char* &num, vector<int> &pi);


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
	cout << "Checking numbers..." << endl;
 
	//find the smallest number not in these digits of pi
	tuple<int, int> results = {0, 0};
	int counter = 0;

	while (get<0>(results) != -1) {
		//convert int to char*
		string s = to_string(counter);
		char* num = new char[s.length() + 1];
		strcpy(num, s.c_str());	

		//find the number in pi
		results = findIndexInPi(num, pi);		

		counter++;

	}

	cout << "The highest consecutive number in these digits of pi is: " << counter - 2 << endl;

	//begin user loop
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
		
		//find the number in pi
		results = findIndexInPi(num, pi);


		//check if there was a result or of nothing was found
		if (get<0>(results) == -1) {
			cout << endl << "No match was found in the first " << pi.size() << " digits of pi." << endl;

		}
		else {
			cout << endl << "Match found from indexs " << get<0>(results) << " to " << get<1>(results) << "." << endl;
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

tuple<int, int> findIndexInPi(char* &num, vector<int> &pi) {

	//go through pi and see if there are any matches
	for (int i = 0; i < pi.size(); i++) {
			
		//check for match
		for (int j = 0; j < strlen(num); j++) {
					
			if (i + j > pi.size() - 1) {
				//ensures that the search doesn't go past the end
				break;
			}

			if (pi.at(i + j) != num[j] - 48) {
				//pattern broken, go to the next point
				break;
			}

			if (j == strlen(num) - 1) {
				//full match found!!!
				return {i, i + j};
			}
		}


	}

	return {-1, -1};

}
