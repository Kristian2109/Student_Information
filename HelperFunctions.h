#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Student.h"
using namespace std;
const int NUM_TABS_CENTER = 5;

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

void SwapStudent(Student& student1, Student& student2) {
	Student tempStudent = student1;
	student1 = student2;
	student2 = tempStudent;
}

void PrintSymbol(char symbol, int times) {
	for (int i = 0; i < times; i++) cout << symbol;
}

void PrintCenterLine(string text) {
	cout << '\n';
	PrintSymbol('\t', NUM_TABS_CENTER);
	cout << text;
}

void Pause() {
	PrintCenterLine("Press enter to continue.");
	system("pause");
}

char GetCharInput() {
	PrintCenterLine("Enter :  ");
	string someAction;
	getline(cin, someAction);
	return (someAction.size() > 1) ? '!' : someAction[0];
}

char GetChar() {
	string someAction;
	getline(cin, someAction);
	return (someAction.size() > 1) ? '!' : someAction[0];
}

int FindUserById(vector<Student> students, string ID) {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getId() == ID) return i;
	}
	return -1;
}

void SortAllStudents(vector<Student>& students, string criteria) {
	for (int i = 0; i < students.size() - 1; i++) {
		for (int j = 0; j < students.size() - 1 - i; j++) {
			if (criteria == "ID") {
				if (students[j].getId() > students[j + 1].getId()) {
					SwapStudent(students[j], students[j + 1]);
				}
			}
			else if (criteria == "Grade") {
				if (students[j].getAvgNote() < students[j + 1].getAvgNote()) {
					SwapStudent(students[j], students[j + 1]);
				}
			}
		}
	}
}

