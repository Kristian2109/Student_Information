#include <iostream>
#include "Services.h"
#include "FileFunctions.h"
#include "RenderFunctions.h"
vector<Student> students;

void ExecuteStudentInformationProject() {
	GetDataFromFile(students);
	char action = 0;
	while (action != 'Q' && action != 'q') {
		system("CLS");
		RenderLogo();
		action = GetCharInput();
		switch (action) {
		case 'R':
		case 'r':
			RegisterStudent(students);
			break;
		case 'A':
		case 'a':
			ExecuteSort(students);
			ShowStudents(students, 0);
			break;
		case 'G':
		case 'g':
			ExecuteSort(students);
			ShowStudents(students, 1);
			break;
		case 'C':
		case 'c':
			ExecuteChangeStudentData(students);
			break;
		default:
			break;
		}
	}
	OverwriteFile(students);
}

int main()
{
	ExecuteStudentInformationProject();
}
