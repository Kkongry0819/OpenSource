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
typedef struct employee_data_node //ְԱ���ݴ洢����һ��ʹ�ü�ֵ�ԣ�map�������Ż�ʱ��Ϳռ临�Ӷȣ��ڶ�������salary��from_chars��������
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
bool InitDatatype();//ְԱ��Ϣ���,���
void InitDepartment();//��ʼ���������ƣ����
bool InitEmployee_list(employee_list&);//��ʼ��ְ�������
bool Empolyee_Data_Storage(employee_list&);//ְ����Ϣ����洢�����
void Excel_Dealing(employee_list_node*);//���,������excel��δ���
void Print_Sheet_By_Department();//���ղ��Ŵ�ӡְ����Ϣ�����
void Print_Sheet(employee_list&);//��ӡ����ְ����Ϣ�����
void Print_TotalSalary_By_Department();//���ղ��Ŵ�ӡ�����ܶ���
void Sort_Sheet(employee_list_node*);//ְ���������,���
void Delete_Field(employee_list&);//ɾ��Ա����Ϣ�����
void ChangeSalary_By_Job(employee_list&);//����ְ�Ƹ��Ĺ��� ���
//������ĺã�����ĺ�
#endif
