// #pragma once
#ifndef _STUDENT_H
#define _STUDENT_H

#include <iostream>
#include <fstream>
#include "course.h"
using namespace std;

struct student
{
	int order;
	char name[20];
	char id[20];
	char teacher[20];

};
int tuition(Student& T);

class Student 
{
protected:
	int studentOrder;
	char studentName[20];
	char studentId[20];
	int studentSelect;//选课门数
	int studentCredit;//总学分
	Course *studentCourse[5];
	int studentTuition;
	char teacherName[20];

public:
	friend class CC5Dlg;

	Student(int order, char name[], char id[]) 
	{
		studentOrder = order;
		strcpy(studentName, name);
		strcpy(studentId, id);
		strcpy(teacherName, "noname");
		studentSelect = 0;
		studentCredit = 0;
		studentTuition = 0;
	}

	Student() 
	{
		studentOrder = 0;
		strcpy(studentName, "noname1");
		strcpy(studentId, "0000000");
		strcpy(teacherName, "noname");
		studentSelect = 0;
		studentCredit = 0;
		studentTuition = 0;
	}

	~Student() {}

	int select(Course* A)//选课
	{
		for(int i=0;i<studentSelect;i++)
			if (studentCourse[i] == A)
			{
				cout << "重复选课"<<endl;
				return 0;
			}
		if (studentSelect == 5)
		{
			cout << "选课已达上限"<<endl; 
			return 0;
		}
			
		studentCourse[studentSelect] = A;
		A->addNum();
		studentSelect++; 
		return 1;
	} 
	int quit(Course* A)//退课
	{
		for (int i = 0; i < studentSelect; i++)
			if (studentCourse[i] == A)
			{
				int j = i + 1;
				for(j;j<studentSelect;j++)
					studentCourse[j-1] = studentCourse[j];
				studentSelect--; 
				A->subNum();
			}
		return 0;
	}
	virtual int calculate()
	{
		return studentTuition;
	};
	 
	void show()//显示选课信息
	{
		cout <<endl<< studentName << "   " << studentSelect << endl;
		for (int i = 0; i < studentSelect; i++)
			studentCourse[i]->put();
		cout << "学费：" << tuition(*this); 
		cout << endl<<endl;
	}
	char* getid()
	{
		return studentId;
	}
	char* getname()
	{
		return studentName;
	}

	int getcredit()
	{
		studentCredit = 0;
		for (int i = 0; i < studentSelect; i++)
		{
			studentCredit += studentCourse[i]->courseCredit;
		}
		return studentCredit;
	}
	virtual void getteacher(){}
	char* getteachername() 
	{
		getteacher();
		return teacherName;

	}
}; 


class Ugstudent:public Student
{
private:
	char ugstudentTeacher[20];
public:
	Ugstudent()
	{
		strcpy(ugstudentTeacher, "noTeachername");
	}
	Ugstudent(int order, char name[], char id[], char teacher[]) :Student(order, name, id)
	{
		strcpy(ugstudentTeacher, teacher);
	}
	void initial();
	virtual int calculate();
	void getteacher() 
	{
		strcpy(teacherName, ugstudentTeacher);
	}

};
   
class Gstudent :public Student
{
private:
	char gstudentProfessor[20];
public:
	Gstudent()  
	{
		strcpy(gstudentProfessor, "noProfessorname");
	}
	Gstudent(int order, char name[], char id[], char teacher[]) :Student(order, name, id)
	{
		strcpy(gstudentProfessor, teacher);
	}
	void initial();
	virtual int calculate();
	void getteacher()
	{
		strcpy(teacherName, gstudentProfessor);
	}

}; 
  

#endif