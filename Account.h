#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "Person.h"
#include "Account.h"

using namespace std;
class Account {
private:
	int accountNumber;
	double balance;
	Person owner;

public:
	//Temperary Account
	Account(int accountNumber, double balance) {
		this->accountNumber = abs(accountNumber);
		this->balance = abs(balance);
	}

	Account(int accountNumber, double balance, Person owner) {
		this->accountNumber = abs(accountNumber);
		this->balance = abs(balance);
		this->owner = owner;
	}

	//Getters :
	int getAccountNumber() {
		return accountNumber;
	}
	double getBalance() {
		return balance;
	}
	Person getOwner() {
		return owner;
	}

	//Methods :
	void deposit(double amount) {
		if (amount > 0) {
			balance += amount;
			cout << "Deposited " << amount << endl;
		}
		else {
			cout << "Deposit failed\n";
		}
	}
	void withdraw(double amount) {
		if (amount > 0 && amount <= balance) {
			balance -= amount;
			cout << "Withdrew " << amount << endl;
		}
		else {
			cout << "Withdraw failed\n";
		}
	}
	void print() {
		cout << "Account Number: " << accountNumber << endl;
		cout << "Balance: " << balance << endl;
		cout << "Owner: " << owner.getId() << "  " <<owner.getName() << endl;
	}

};

