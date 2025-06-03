#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Person{
private:
	int id = 0;
	string name = "";

public:
	Person() : id(0), name("") {}
	Person(int id, string name) {
		this->id = abs(id);
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

