#include "pch.h"
#include "course.h"
#include <fstream>
#include <iostream>

Course cou[12];
int Course::courseNumAll = 0;

void Course::initial()
{
	int i = 0;
	ifstream fin;
	fin.open("course.txt", ios_base::in);
	if (fin.fail())
		cout << "打开文件失败";
	course A;
	while (fin >> A.order >> A.type >> A.name >> A.credit) 
	{
		cou[i] = Course(A.order, A.type, A.name, A.credit);
		i = i + 1;
	}                   
}         
                        