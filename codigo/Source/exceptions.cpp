#include "../Headers/exceptions.h"
#include <iostream>
#include<string>
using namespace std;

InvalidPlayer::InvalidPlayer(string name, Date birth) {
	this->name = name;
	this->birth = birth;
}

void InvalidPlayer::show() const { 
	cout << name << " born on: " << birth << " is not a valid player of the team.\n";
}