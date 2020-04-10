//#pragma once
#ifndef _COURSE_H
#define _COURSE_H

#include <iostream>
#include <fstream>      
using namespace std;
 
struct course
{
	int order;
	char name[20];
	char type[20];
	int credit;
};
           
class Course
{
private:
	int courseOrder;
	char courseType[20];
	char courseName[20];
	int courseCredit;  
	int courseNum;
	static int courseNumAll;

public:
	friend class Student;
	friend class Ugstudent;
	friend class Gstudent;  
	friend class CC5Dlg;

	Course(int order, char type[], char name[], int credit)
	{
		courseOrder = order;
		strcpy(courseName, name);
		strcpy(courseType, type);
		courseCredit = credit;
		courseNum = 0;

	}
	Course()
	{
		courseOrder = 0;
		strcpy(courseName, "noname");
		strcpy(courseType, "notype");
		courseCredit = 0;
		courseNum = 0; 
	}
	~Course() {}
	void put() {
		cout << courseOrder << "\t" << courseType << "\t" << courseName << "\t" << courseCredit << "\t" << courseNum << "\t" << courseNumAll << endl;
	}
	void addNum() {
		courseNum++;
		courseNumAll++;
	}
	void subNum()
	{
		courseNum--;
		courseNumAll--;
	}              
	void initial();
};
     
#endif