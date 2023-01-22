#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isHighLetter(char letter) {
	return (letter >= 'A' && letter <= 'Z');
}

bool isLowLetter(char letter) {
	return (letter >= 'a' && letter <= 'z');
}

bool isValidName(string name) {
	if (!isHighLetter(name[0])) return false;

	int countSpaces = 0;
	for (int i = 1; i < name.size(); i++) {
		if (name[i] == ' ') {
			countSpaces++; i++;
			if (i < name.size() && !isHighLetter(name[i])) {
				return false;
			}
		}
		else {
			if (!isLowLetter(name[i])) {
				return false;
			}
		}
	}
	return countSpaces == 2;
}

bool isDigit(char digit) {
	return digit >= '0' && digit <= '9';
}

bool isRightIdNumber(string IdNumber) {
	for (int i = 0; i < IdNumber.size(); i++) {
		if (!isLowLetter(IdNumber[i]) && !isHighLetter(IdNumber[i]) &&
			!isDigit(IdNumber[i])) {
			return false;
		}
	}
	return true;
}
