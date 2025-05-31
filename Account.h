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
	static int numberOfAccounts;
	

public:
	Account(int accountNumber, double balance, Person owner) {
		this->accountNumber = accountNumber;
		this->balance = balance;
		this->owner = owner;

		if (isnan(numberOfAccounts)) {
			numberOfAccounts++;
		}
		else {
			numberOfAccounts = 1;
		}
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
		}
		else {
			cout << "Withdraw failed\n";
		}
	}
	static int getnumberOfAccounts() {
		return numberOfAccounts;
	}
	void printAccountDetails() {
		cout << "Account Number: " << accountNumber << endl;
		cout << "Balance: " << balance << endl;
		cout << "Owner: " << owner.getId() << "  " <<owner.getName() << endl;
	}

};

