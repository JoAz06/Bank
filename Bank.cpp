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

static void printOutResult() {
    for (vector<string> x : queryResults) {
        for (string y : x) {
            cout << y << endl;
        }
    }
}

static void executeSQL(string sql) {
    sqlite3* DB;
    sqlite3_open("Bank.db", &DB);
    sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    sqlite3_exec(DB, sql.c_str(), nullptr, nullptr,nullptr);
    sqlite3_close(DB);
}

static int callback(void* notUsed, int count, char** colData, char** colName) {
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
    sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    sqlite3_exec(DB, sql.c_str() , callback , nullptr , nullptr);
    
}
//------------------------------------------------------//

int main(){
    string userInput;
    vector<string> command;
    vector<Account> accounts;

    //Commands :
    vector<string> exit = {"exit","exit - Close the program\n"};
    vector<string> add = {"add","add account [account number] [account balance] [account owner id] - Add a new account with already existing owner\nadd account [account number] [account balance] [owner id] [owner name] - Add a new account with a new owner\nadd person [person id] \"[person name]\" - Add a new person\n"};
    vector<string> help = { "help","help - Show this message\n"};
	vector<string> show = { "show","show account [account number] - Show the info of the account\nshow person [person id] - Show the info of the person\nshow - Show the info of the whole bank\n" };
    vector<string> remove = { "remove","remove account [account number] - Delete the account with that number\bremove person [person id] - Delete the person wwith that ID\n" };
	vector<vector<string>> commandList = {exit, add, help, show, remove};

    //Preparations for the database
    vector<string> sql = {"create table if not exists Person(id int primary key,name varchar(255) not null);",
    "create table if not exists Account(accountNumber int primary key,balance double,owner int not null,foreign key(owner) references Person(id) on delete cascade);"};

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
        vector<string> commandNames = Split(userInput,'"');
        bool valid = true;

        if (command.size() == 0) {
            valid = false;
        }

        //show
        if (valid && Equals(command[0], show[0])) {
            if (command.size() == 1) {
				
            }
            else if(command.size() >= 3 && isNumber(command[2])) {
                if (Equals(command[1],"account")) {
                    selectSQL("select * from Account where accountNumber = " + command[2] + ";");
                    if (queryResults.size() != 0) {
                        cout << "Account with Number : " << queryResults[0][0] << endl;
                        cout << "Has a balance of : " << queryResults[0][1] << "$\n";
                        selectSQL("select * from Person where id = " + queryResults[0][2] + ";");
                        cout << "Owned by " << queryResults[0][1] << " with id : " << queryResults[0][0] << endl;
                    }
                    else {
                        cout << "Account does not exist.\n";
                    }
                }
                else if(Equals(command[1],"person")){
                    selectSQL("select * from Person where id = " + command[2] + ";");
                    if (queryResults.size() != 0) {
                        cout << "Person with ID : " << queryResults[0][0] << endl;
                        cout << "With name : " << queryResults[0][1] << endl;
                        selectSQL("select count(*) from account having owner = " + command[2] + ";");
                        cout << "Owns " << queryResults[0][0] << " accounts with a total balance of ";
                        selectSQL("select sum(balance) from account having owner = " + command[2] + ";");
                        cout << queryResults[0][0] << "$\n";
                    }
                    else {
                        cout << "Person does not exist.\n";
                    }
                }
                else {
                    valid = false;
                }
            }
            else {
                valid = false;
            }
        }

        //Delete
        else if (valid && Equals(command[0], remove[0]) && isNumber(command[2])) {
            if (Equals(command[1], "account")) {
                selectSQL("select * from Account where accountNumber = " + command[2] + ";");
                if (queryResults.size() != 0) {
                    executeSQL("delete from Account where accountNumber = " + command[2] + ";");
                    cout << "Delete was successfull.\n";
                }
                else {
                    cout << "Account does not exist.\n";
                }
            }
            else if (Equals(command[1], "person")) {
                selectSQL("select * from Person where id = " + command[2] + ";");
                if (queryResults.size() != 0) {
                    executeSQL("delete from Person where id = " + command[2] + ";");
                    cout << "Delete was successfull.\n";
                }
                else {
                    cout << "Person does not exist.\n";
                }
            }
            else {
                valid = false;
            }
        }

        //Add
        else if(valid && Equals(command[0], add[0]) && command.size() >=2) {
            if(Equals(command[1],"account")){
                selectSQL("select * from Account where accountNumber = " + command[2] + ";");
                if (queryResults.size() == 0 && isNumber(command[4])) {
                    if (command.size() == 5) {
                        selectSQL("select * from Person where id = " + command[4] + ";");
                        if (queryResults.size() == 1) {
                            Person* temperaryPerson = new Person(stoi(queryResults[0][0]), queryResults[0][1]);
                            Account* temperaryAccount = new Account(stoi(command[2]), stod(command[3]), *temperaryPerson);
                            executeSQL("INSERT INTO Account VALUES (" + to_string(temperaryAccount->getAccountNumber()) + ", " + to_string(temperaryAccount->getBalance()) + " , "+ to_string(temperaryPerson->getId()) +"); ");
                            delete temperaryAccount;
                            delete temperaryPerson;
                        }
                        else {
                            cout << "Person with ID : " << command[4] << " doesnt exist.\n";
                        }
                    }
                    else if (command.size() >= 6 && commandNames.size() == 2) {
                        selectSQL("select * from Person where id = " + command[4] + ";");
                        if (queryResults.size() == 0) {
                            Person* temperaryPerson = new Person(stoi(command[4]), commandNames[1]);
                            executeSQL("INSERT INTO Person VALUES (" + to_string(temperaryPerson->getId()) + ", '" + temperaryPerson->getName() + "');");
                            Account* temperaryAccount = new Account(stoi(command[2]), stod(command[3]), *temperaryPerson);
                            executeSQL("INSERT INTO Account VALUES (" + to_string(temperaryAccount->getAccountNumber()) + ", " + to_string(temperaryAccount->getBalance()) + " , " + to_string(temperaryPerson->getId()) + "); ");
                            delete temperaryAccount;
                            delete temperaryPerson;
                        }
                        else {
                            cout << "Person with the same ID already exist.\n";
                        }
                    }
                    else {
                        valid = false;
                    }
                }
                else {
                    cout << "Account with number : " << command[2] << " already exists or invalid data.";
                }
            }
            else if (Equals(command[1] , "person") && isNumber(command[2]) && commandNames.size()==2) {
                selectSQL("select * from Person where id = " + command[2] + ";");
                if (queryResults.size() == 0) {
                    Person* temperaryPerson = new Person( stoi(command[2]), commandNames[1]);
                    executeSQL("INSERT INTO Person VALUES (" + to_string(temperaryPerson->getId()) + ", '" + temperaryPerson->getName() + "');");
                    delete temperaryPerson;
                }
                else {
                    cout << "Person with the same ID already exist.\n";
                }
            }
            else {
                valid = false;
            }
		}

        //Help
        else if (valid && Equals(command[0], help[0])) {
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
        else if (valid && Equals(command[0],exit[0])) {
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



