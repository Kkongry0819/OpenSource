#include"Employee.h"
department_name department = NULL;
int Count = 0;
int DepartmentNum = 0;
std::map<short, std::string> value;
short KEY = 0;
datatype* Type = NULL;
void menu()
{
	cout << left << setw(20);
	cout << "\033[31m" << " 1 新增职工信息";
	cout << left << setw(20);
    cout<<  "      2 打印所有职工信息" << endl;
	cout << left << setw(20);
	cout << "\033[32m" << " 3 打印该部门工资总额";
	cout << left << setw(20);
	cout <<"4 按部门打印职工信息" << endl;
	cout << left << setw(20);
	cout << "\033[33m" << " 5 删除职工信息";
	cout << left << setw(20);
	cout << "      6 按职称调整工资" << endl;
	cout << left << setw(20);
	cout << "\033[34m" << " 7 按升序对职工排序";
	cout << left << setw(20);
	cout <<"  8 导出职工信息到Excel" << endl;
	cout << left << setw(20);
	cout << "\033[0m" << "9 关于作者";
	cout << left << setw(20);
	cout << "          0 退出程序"<<endl;
}
void table(employee_list&A)
{
	
	for(;;)
	{
		int i = 0;
		string temp;
		start:
		cout << "功能选择..." << endl;
		menu();
		cin >> temp;
		if (temp == "0" || temp == "1" || temp == "" || temp == "2" || temp == "3" || temp == "4" || temp == "5" || temp == "6" || temp == "7" || temp == "8")
		{
			i = stoi(temp);
			switch (i)
			{
			case 1:
			{
				if (Empolyee_Data_Storage(A))
				{
					cout << "存储成功！" << endl;
				}
				else
				{
					cerr << "存储失败，请检查后重试！" << endl;
				}
				system("pause");
				system("cls");
				break;
			}
			case 2:
			{
				Print_Sheet(A);
				system("pause");
				system("cls");
				break;
			}
			case 3:
			{
				Print_TotalSalary_By_Department();
				system("pause");
				system("cls");
				break;
			}
			case 4:
			{
				Print_Sheet_By_Department();
				system("pause");
				system("cls");
				break;
			}
			case 5:
			{
				Delete_Field(A);
				system("pause");
				system("cls");
				break;
			}
			case 6:
			{
				ChangeSalary_By_Job(A);
				system("pause");
				system("cls");
				break;
			}
			case 7:
			{
				Sort_Sheet(A);
				system("pause");
				system("cls");
				break;
			}
			case 8:
			{
				Excel_Dealing(A);
				system("pause");
				system("cls");
				break;
			}
			case 9:
			{
				cout << "Developed By R.Z CHEN\a\n"<<"R.Z CHEN All Right Reserved\n";
				system("pause");
				system("cls");
				break;
			}
			case 0:
			{
				return;
			}
			}
		}
		else
		{
			cout << "非法输入，请重新输入！\a" << endl;
			Sleep(1500);
			system("cls");
			goto start;
		}
	}
	
}
int main()
{
	employee_list list ;
	std::locale loc("Chinese-simplified");
	std::wcin.imbue(loc);
	std::wcout.imbue(loc);
	if (InitEmployee_list(list)&& InitDatatype())
	{
		cout << "人事信息管理系统初始化成功！" << endl;
		Sleep(1000);
		system("cls");
	}
	else
	{
		return -1;
	}
	table(list);
	return 0;
}