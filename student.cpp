#include "pch.h"
#include "student.h"
#include <fstream>
#include <iostream>

Ugstudent ugstu[30];
Gstudent gstu[15];

void Ugstudent::initial()
{
	int i = 0;
	ifstream fin;
	fin.open("UGstudent.txt", ios_base::in);
	if (fin.fail())
		cout << "打开文件失败";
	student B;
	while (fin >> B.order >> B.teacher >> B.id >> B.name)
	{
		ugstu[i] = Ugstudent(B.order, B.name, B.id, B.teacher);
		i = i + 1;
	}
}              

void Gstudent::initial()
{
	int i = 0;
	ifstream fin;
	fin.open("Gstudent.txt", ios_base::in);
	if (fin.fail())
		cout << "打开文件失败";
	student C;
	while (fin >> C.order >> C.teacher >> C.id >> C.name)
	{
		gstu[i] = Gstudent(C.order, C.name, C.id, C.teacher);
		i = i + 1;
	}
}          

int Ugstudent::calculate() 
{ 
	studentTuition = 0;
	for (int i = 0; i < studentSelect; i++)
	{
		if (!strcmp(studentCourse[i]->courseType , "学科基础"))
			studentTuition += studentCourse[i]->courseCredit * 200; 
		else if (!strcmp(studentCourse[i]->courseType , "专业基础"))
			studentTuition += studentCourse[i]->courseCredit * 150;
		else if (!strcmp(studentCourse[i]->courseType, "专业核心"))
			studentTuition += studentCourse[i]->courseCredit * 100;
	}
	return studentTuition; 
}
 
int Gstudent::calculate()
{
	studentTuition = 0;
	for (int i = 0; i < studentSelect; i++)
	{
		if (!strcmp(studentCourse[i]->courseType, "学科基础"))
			studentTuition += studentCourse[i]->courseCredit * 200;
		else if (!strcmp(studentCourse[i]->courseType, "专业基础"))
			studentTuition += studentCourse[i]->courseCredit * 180;
		else if (!strcmp(studentCourse[i]->courseType, "专业核心"))
			studentTuition += studentCourse[i]->courseCredit * 150;  
	}
	return studentTuition;
}   
int tuition(Student& T)
{
	return T.calculate();
}