#include <iostream>
#include <string>
using namespace std;

int main(){
    cout << "Welcome to bank of America" << endl;
    string userInput;

    //Commands :
	string exit = "exit";
    string add = "add";

	bool running = true;
    do {
        getline(cin, userInput);

        if(equals(userInput, add)) {
            
		}

        else if (equals(userInput,exit)) {
            cout << "Closing the program...\n";
            running = false;
        }

        else {
            cout << "Ivalid command, please try again.\n";
        }

    } while (running);
}

bool equals(string string1, string string2) {
    if (string1.length() == string2.length()) {
        bool valid = true;
        for (int i = 0; i < string1.length(); i++) {
            if (!(tolower(string1[i]) == tolower(string2[i]))) {
                valid = false;
            }
        }
    }
}

