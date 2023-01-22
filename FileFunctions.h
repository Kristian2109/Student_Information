#pragma once

#include <iostream>
#include <fstream>
#include "Student.h"
#include "HelperFunctions.h"
using namespace std;
const string DATA_FILE = "data.txt";
const int MAX_LENGTH_LINE = 300;
const int MAX_STUDENTS_COUNT = 200;

void GetName(string rawData, string& name) {
	int index = 0;
	while (rawData[index] != ';') {
		if (index != 0 && isHighLetter(rawData[index])) {
			name.push_back(' ');
		}
		name.push_back(rawData[index]);
		index++;
	}
}

vector<int> DelimiterIndexes(string rawData) {
	vector<int> indexes;
	for (int i = 0; i < rawData.size(); i++) {
		if (rawData[i] == ';') indexes.push_back(i);
	}
	return indexes;
}

void SplitDisciplines(string rawDisciplines, vector<string>& disciplines) {
	int currentIndex = 0;
	for (int i = 0; i < rawDisciplines.size(); i++) {
		if (rawDisciplines[i] == ',') {
			currentIndex++; i++;
		}
		if (disciplines.size() == currentIndex) {
			string newString;
			disciplines.push_back(newString);
		}
		disciplines[currentIndex].push_back(rawDisciplines[i]);
	}
}

void SplitNotes(string rawNotes, vector<double>& notes) {
	string noteString;
	for (int i = 0; i < rawNotes.size(); i++) {
		if (rawNotes[i] == ',') {
			i++;
			double note = stod(noteString);
			notes.push_back(note);
			noteString.clear();
		}
		noteString.push_back(rawNotes[i]);
		if (i + 1 == rawNotes.size()) {
			double note = stod(noteString);
			notes.push_back(note);
		}
	}
}

void SplitStudentData(string rawData, string& name, string& idNumber, double& group, vector<string>& disciplines, vector<double>& notes) {
	GetName(rawData, name);
	vector<int> delimiters = DelimiterIndexes(rawData);
	idNumber = rawData.substr(delimiters[0] + 1, delimiters[1] - delimiters[0] - 1);
	group = rawData[delimiters[1] + 1] - '0';
	if (delimiters.size() > 2) {
		string rawDisciplines = rawData.substr(delimiters[2] + 1, delimiters[3] - delimiters[2] - 1);
		SplitDisciplines(rawDisciplines, disciplines);
		string rawNotes = rawData.substr(delimiters[3] + 1);
		SplitNotes(rawNotes, notes);
	}
}

void GetDataFromFile(vector<Student>& students) {
	ifstream file(DATA_FILE, ios::in);
	vector<string> rawStudentData (MAX_STUDENTS_COUNT);
	
	if (!file.is_open()) return;
	int indexUnit = 0;
	while (file >> rawStudentData[indexUnit]) {
		string name;
		string idNumber;
		double group;
		vector<string> disciplines;
		vector<double> notes;
		SplitStudentData(rawStudentData[indexUnit], name, idNumber, group, disciplines, notes);
		/*cout << "Student: " << name << "  " << idNumber << "  " << group << "  ";
		cout << endl;*/
		Student student(name, idNumber, group);
		for (string disc : disciplines) {
			student.setDiscipline(disc);
		}
		for (double note : notes) {
			student.setNote(note);
		}
		students.push_back(student);
		indexUnit++;
	}
	//for (string student : rawStudentData) {
	//	cout << student << endl;
	//}
	file.close();
}

string NameWithoutSpaces(string name) {
	string result;
	for (char symbol : name) {
		if (symbol != ' ') result.push_back(symbol);
	}
	return result;
}

void AppendStudentToFile(Student student) {
	ofstream file(DATA_FILE, ios::out | ios::app);
	string name = NameWithoutSpaces(student.getName());
	file << name << ';' << student.getId() << ';'
		 << student.getGroup();
	if (student.getDisciplines().size() > 0) {
		file << ';';
		for (int i = 0; i < student.getDisciplines().size(); i++) {
			file << student.getDisciplines()[i];
			if ((i + 1) != student.getDisciplines().size()) file << ',';
		}
		file << ';';
		for (int i = 0; i < student.getNotes().size(); i++) {
			file << student.getNotes()[i];
			if ((i + 1) != student.getNotes().size()) file << ',';
		}
	}
	file << '\n';
	file.close();
}

void OverwriteFile(vector<Student> students) {
	ofstream file(DATA_FILE, ios::out);
	file.close();
	for (Student student : students) {
		AppendStudentToFile(student);
	}
}