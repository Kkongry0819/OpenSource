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
	cout << "\033[31m" << " 1 ����ְ����Ϣ";
	cout << left << setw(20);
    cout<<  "      2 ��ӡ����ְ����Ϣ" << endl;
	cout << left << setw(20);
	cout << "\033[32m" << " 3 ��ӡ�ò��Ź����ܶ�";
	cout << left << setw(20);
	cout <<"4 �����Ŵ�ӡְ����Ϣ" << endl;
	cout << left << setw(20);
	cout << "\033[33m" << " 5 ɾ��ְ����Ϣ";
	cout << left << setw(20);
	cout << "      6 ��ְ�Ƶ�������" << endl;
	cout << left << setw(20);
	cout << "\033[34m" << " 7 �������ְ������";
	cout << left << setw(20);
	cout <<"  8 ����ְ����Ϣ��Excel" << endl;
	cout << left << setw(20);
	cout << "\033[0m" << "9 ��������";
	cout << left << setw(20);
	cout << "          0 �˳�����"<<endl;
}
void table(employee_list&A)
{
	
	for(;;)
	{
		int i = 0;
		string temp;
		start:
		cout << "����ѡ��..." << endl;
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
					cout << "�洢�ɹ���" << endl;
				}
				else
				{
					cerr << "�洢ʧ�ܣ���������ԣ�" << endl;
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
			cout << "�Ƿ����룬���������룡\a" << endl;
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
		cout << "������Ϣ����ϵͳ��ʼ���ɹ���" << endl;
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