#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sqlite3.h>
#include "Account.h"
#include "Person.h"

using namespace std;

vector<vector<string>> queryResults;

//Functions :
static bool Equals(string string1, string string2) {
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


static vector<string> Split(string phrase, char splitter) {
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
    if(!(word == ""))
        result.push_back(word);
    return result;
}

static vector<string> Split(string phrase) {
    return Split(phrase, ' ');
}

static bool isNumber(string x) {
    for (char y : x) {
        if (!isdigit(y)) {
            return false;
        }
    }
    return true;
}

static void createDB() {
    sqlite3* DB;
    sqlite3_open("Bank.db", &DB);
    sqlite3_close(DB);
}

static void executeSQL(string sql) {
    sqlite3* DB;
    sqlite3_open("Bank.db", &DB);
    sqlite3_exec(DB, sql.c_str(), nullptr, nullptr,nullptr);
    sqlite3_close(DB);
}

static int callback(void* notUsed, int count, char** colName, char** colData) {
    vector<string> temp(count);
    for (int i = 0; i < count; i++) {
        temp[i] = colData[i];
    }
    queryResults.push_back(temp);
    temp.clear();
    return 0;
}

static void selectSQL(string sql) {
    queryResults.clear();
    sqlite3* DB;
    sqlite3_open("Bank.db", &DB);
    sqlite3_exec(DB, sql.c_str() , callback , nullptr , nullptr);
}
//------------------------------------------------------//

int main(){
    string userInput;
    vector<string> command;
    vector<Account> accounts;

    //Commands :
    vector<string> exit = {"exit","exit - Close the program\n"};
    vector<string> add = {"add","add account [account number] [account balance] [account owner id] - Add a new account with already existing owner\nadd account [account number] [account balance] [owner id] [owner name] - Add a new account with a new owner\nadd person [person id] [person name] - Add a new person\n"};
    vector<string> help = { "help","help - Show this message\n"};
	vector<string> info = { "info","info account [account number] - Show the info of the account\ninfo person [person id] - Show the info of the person\ninfo - Show the info of the whole bank\n" };
	vector<vector<string>> commandList = {exit, add, help, info};

    //Preparations for the database
    vector<string> sql = {"create table if not exists Person(id int primary key,name varchar(255) not null);",
    "create table if not exists Account(accountNumber int primary key,balance double,owner int not null,foreign key(owner) references Person(id));",
        "create table if not exists Owning(owner int not null,accountNumber int not null,foreign key(owner) references Person(id),foreign key(accountNumber) references Account(accountNumber),delete on cascade); "};
    
    createDB();
    for (int i = 0; i < sql.size(); i++) {
        executeSQL(sql[i]);
    }
    
    bool running = true;
	cout << "Welcome to bank of America" << endl;
    do {
		cout << "Enter a command: ";
        getline(cin, userInput);
        command = Split(userInput);
        bool valid = true;

        //Info
        if (Equals(command[0], info[0])) {
            if (command.size() == 1) {
				
            }
            else if(command.size() == 3){
                if (Equals(command[1],"account")) {

                }
                else if(Equals(command[1],"person")){

                }
                else {
                    valid = false;
                }
            }
            else {
                valid = false;
            }
        }

        //Add
        else if(Equals(command[0], add[0]) && command.size() >=2) {
            if(Equals(command[1],"account")){
                if (true /*check before if account already exists*/) {
                    if (command.size() == 5 && isNumber(command[2])) {

                    }
                    else if (command.size() == 6  && isNumber(command[4])) {

                    }
                    else {
                        valid = false;
                    }
                }
                else {
                    valid = false;
                }
            }
            else if (Equals(command[1] , "person") && isNumber(command[3])) {
                if (true /*checkk if person already exists*/) {
                    /*
                        if not add to database by creating new Person
                        then add with sql then delete person
                        */
                }
                else {
                    valid = false;
                }
            }
            else {
                valid = false;
            }
		}

        //Help
        else if (Equals(command[0], help[0])) {
            if (command.size() <= 2) {
                if (command.size() == 1) {
                    for (vector<string> cmd : commandList) {
                        cout << cmd[1];
                    }

                }
                else {
                    for (vector<string> cmd : commandList) {
                        valid = true;
                        if (Equals(command[1], cmd[0])) {
                            cout << cmd[1];
                            break;
                        }
                        valid = false;
                        
                    }
                }
            }
            
        }

        //Exit
        else if (Equals(command[0],exit[0])) {
            cout << "Closing the program...\n";
            running = false;
        }

        //Invalid Input
        else {
            valid = false;
        }

        if (!valid) {
				cout << "Invalid command, please try again.\n";
            }

    } while (running);
    return 0;
}



