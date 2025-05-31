#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Account.h"
#include "Person.h"

using namespace std;

//Functions :
bool Equals(string string1, string string2) {
    bool valid = true;
    if (string1.length() == string2.length()) {
        for (int i = 0; i < string1.length(); i++) {
            if (!(tolower(string1[i]) == tolower(string2[i]))) {
                valid = false;
                break;
            }
        }
    }
    else {
        valid = false;
    }
    if (valid) {
        return true;
    }
    else {
        return false;
    }
}


vector<string> Split(string phrase, char splitter) {
    vector<string> result;
    string word = "";
    for (char chr : phrase) {
        if (chr == splitter) {
            if (!word.empty()) {
                result.push_back(word);
                word = "";
            }
        }
        else {
            word += chr;
        }
    }
    result.push_back(word);
    return result;
}

vector<string> Split(string phrase) {
    return Split(phrase, ' ');
}
//-----------------------------

int main(){
    cout << "Welcome to bank of America" << endl;
    string userInput;
    vector<string> command;
    vector<Account> accounts;

    //Commands :
    
    vector<string> exit = {"exit","exit - Close the program\n"};
    vector<string> add = {"add","add [account number] [account balance] [account owner id] - Add a new account with already existing owner\nadd [account number] [account balance] [owner id] [owner name] - Add a new account with a new owner\nadd [person id] [person name] - Add a new person\n"};
    vector<string> help = { "help","help - Show this message\n"};

	vector<vector<string>> commandList = {exit, add, help};

	bool running = true;
    do {
		cout << "Enter a command: ";
        getline(cin, userInput);
        command = Split(userInput);
        

        if(Equals(command[0], add[0])) {
            
		}

        else if (Equals(command[0], help[0])) {
            bool valid = false;
            if (command.size() <= 2) {
                if (command.size() == 1) {
                    for (vector<string> cmd : commandList) {
                        cout << cmd[1];
						valid = true;
                    }

                }
                else {
                    for (vector<string> cmd : commandList) {
                        if (Equals(command[1], cmd[0])) {
                            cout << cmd[1];
                            valid = true;
                            break;
                        }
                        
                    }
                }
            }
            if (!valid) {
				cout << "Invalid command, please try again.\n";
            }
        }

        else if (Equals(command[0],exit[0])) {
            cout << "Closing the program...\n";
            running = false;
        }

        else {
            cout << "Ivalid command, please try again.\n";
        }

    } while (running);
    return 0;
}



