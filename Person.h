#pragma once
#include <iostream>
#include <string>
using namespace std;
class Person{
private:
	int id;
	string name;

public:
	Person() {}

	Person(int id, string name) {
		this->id = id;
		this->name = name;
	}

	//Getters :
	int getId() const {
		return id;
	}
	string getName() const {
		return name;
	}

	//Setters :
	void changeName(string name) {
		this->name = name;
	}
};

