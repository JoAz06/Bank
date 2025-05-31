#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;
class Account{
private:
	int accountNumber;
	double balance;
	Person owner;
	static int numberOfAccounts;
	
public:
	Account(int accountNumber, double balance, Person owner){
	this -> accountNumber = accountNumber;
	this -> balance = balance;
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


};

