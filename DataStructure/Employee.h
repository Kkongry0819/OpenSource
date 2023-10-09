#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<math.h>
#include<Windows.h>
#include<map>
#include<iomanip>
#include <charconv>
#include<libxl.h>
#include <cwchar>
#include <sstream>
#include <locale>
using namespace std;
using namespace libxl;
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#define MAX_NO_SIZE 9
extern int Count;
extern int DepartmentNum;
extern std::map<short, std::string> value;
extern short KEY;

typedef struct datatype
{
	char type[100];
	datatype* next;
};
extern datatype* Type;
typedef struct employee_data_node //职员数据存储，第一个使用键值对（map）处理，优化时间和空间复杂度，第二个遇到salary用from_chars函数处理
{
	short key;
	string data;
	employee_data_node* next;
}*employee_data;
typedef struct employee_list_node
{
	char NO[MAX_NO_SIZE];
	employee_data_node* data;
	employee_list_node* next;
}*employee_list;
typedef struct address
{
	employee_list_node* ADDRESS;
	address* next;
};
typedef struct department_name_node 
{
	string name;
	address Address;
	department_name_node* next;
}*department_name;
extern department_name department;
typedef struct Job
{
	employee_data_node* jOb;
	Job* next;
};
bool InitDatatype();//职员信息类别,完成
void InitDepartment();//初始化部门名称，完成
bool InitEmployee_list(employee_list&);//初始化职工表，完成
bool Empolyee_Data_Storage(employee_list&);//职工信息输入存储，完成
void Excel_Dealing(employee_list_node*);//大饼,输出表格到excel，未完成
void Print_Sheet_By_Department();//按照部门打印职工信息，完成
void Print_Sheet(employee_list&);//打印所有职工信息，完成
void Print_TotalSalary_By_Department();//按照部门打印工资总额，完成
void Sort_Sheet(employee_list_node*);//职工编号排序,完成
void Delete_Field(employee_list&);//删除员工信息，完成
void ChangeSalary_By_Job(employee_list&);//根据职称更改工资 完成
//把输出改好，界面改好
#endif
