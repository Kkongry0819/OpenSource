#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<Windows.h>
#include<iomanip>
#define N 1000
using namespace std;
int account = 0;//�������,����
char arrY[] = "Y";
char arry[] = "y";
char arrN[] = "N";
char arrn[] = "n";
typedef struct singer
{
	int number;
	char name[50];
	char music_name[100];
	int public_vote;
	int five_judge1 ;
	int five_judge2 ;
	int five_judge3 ;
	int five_judge4 ;
	int five_judge5 ;
    int  five_judge ;
	double total_score ;
} copy_sing;
singer sing[N];
int judge(int* i)
{
	char arr[10];
	bool flag = true;
	while (flag)
	{
		cout << "�Ƿ��������?(Y/N)" << endl;
		cin >> arr;
		if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0 ||strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
		{
			flag = false;
		}
		else
			cout << "�����������������\n";
	}
	if (strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
	{
		(*i)++;
		return 0;
	}
	return 1;
}
void menu()
{
	cout << "#####################################\n";
	cout << "########1      ���������Ϣ  ########\n";
	cout << "########2      ���������Ϣ  ########\n";
	cout << "########3      ���ֳɼ�����  ########\n";
	cout << "########4      ��Ӹ�����Ϣ  ########\n";
	cout << "########5      ��ѯ������Ϣ  ########\n";
	cout << "########6      ɾ��������Ϣ  ########\n";
	cout << "########7      ʹ�������    ########\n";
	cout << "########0      �˳����Ǹ���  ########\n";
	cout << "#####################################\n";
	cout << "������...\n";
}
int input(singer* sing, int acc)//���ֱ�ţ�������������Ŀ���ƣ�������ί��ͶƱ����5��רҵ��ί�Ĵ�֣��ܷ�
{
	int i = 0;
	for (i = acc;i < N;i++)
	{
		sing[i].number = i + 1;
		cout << "������ѡ������\n";
		cin >> sing[i].name;
		cout << "�������������Ŀ����\n";
		cin >> sing[i].music_name;
		cout << "�����������ί��ͶƱ��\n";
		cin >> sing[i].public_vote;
		cout << "������רҵ��ί1�Ĵ��\n";
		cin >> sing[i].five_judge1;
		cout << "������רҵ��ί2�Ĵ��\n";
		cin >> sing[i].five_judge2;
		cout << "������רҵ��ί3�Ĵ��\n";
		cin >> sing[i].five_judge3;
		cout << "������רҵ��ί4�Ĵ��\n";
		cin >> sing[i].five_judge4;
		cout << "������רҵ��ί5�Ĵ��\n";
		cin >> sing[i].five_judge5;
		sing[i].five_judge = sing[i].five_judge1 + sing[i].five_judge2 + sing[i].five_judge3 + sing[i].five_judge4 + sing[i].five_judge5;
		sing[i].total_score = ((double)sing[i].public_vote + sing[i].five_judge) / 6;
		cout << "�Ѿ��ɹ�¼����Ϊ" << sing[i].number << "�ĸ��֣�\a" << endl;
		Sleep(2000);
		system("cls");
		if (judge(&i) == 0)
		{
			break;
		}
	}
	system("cls");
	return i;
}
void output(singer* sing, int p)//���ֱ�ţ�������������Ŀ���ƣ�������ί��ͶƱ����5��רҵ��ί�Ĵ�֣��ܷ�
{
	for (int i = 0;i < p;i++)
	{
		if (sing[i].number)
		{
			cout << "���ֱ�� " << sing[i].number << endl << "�������� " << sing[i].name << endl << "������Ŀ���� " << sing[i].music_name
				<< endl << "������ί��ͶƱ�� " << sing[i].public_vote << endl << "5��רҵ��ί���ܴ�� " << sing[i].five_judge << endl
				<< "�ܷ� " <<  setiosflags(ios::fixed) << setprecision(1)<<sing[i].total_score << endl << endl;
		}
	}
	system("pause");
	system("cls");
}
void struct_bubble_sort(singer* copy_sing)
{
	for (int i = 0; i < account - 1; i++)
	{
		for (int j = 0; j < account - i - 1; j++)
		{
			if (copy_sing[j].total_score < copy_sing[j + 1].total_score) //�Ƚ��ֵܷĴ�С
			{
				singer temp = copy_sing[j + 1];    //�ִܷ�Ľ������ڵ�����Ԫ��
				copy_sing[j + 1] = copy_sing[j];
				copy_sing[j] = temp;
			}
		}
	}
	for (int i = 0;i < account;i++)
	{
		if (copy_sing[i].number)
		{
			cout << "��" << i + 1 << "\t" << "��� " << copy_sing[i].number << "\t" << "�������� " << sing[i].name << "\t" << "����������Ŀ "
				<< copy_sing[i].music_name << "\t�ܷ� " << setiosflags(ios::fixed) << setprecision(1) << copy_sing[i].total_score << endl;
		}
		else
			i--;
	}
	system("pause");
	system("cls");
}
void ADD(singer* sing)
{
	cout << "��ע�⣬������¼����Ϊ" << account + 1 << "�ĸ��ֵ���Ϣ..." << endl;
	Sleep(3000);
	system("cls");
	cout << "������ѡ��" << account + 1 << "������\n";
	cin >> sing[account].name;
	cout << "�������������Ŀ����\n";
	cin >> sing[account].music_name;
	cout << "�����������ί��ͶƱ��\n";
	cin >> sing[account].public_vote;
	cout << "������רҵ��ί1�Ĵ��\n";
	cin >> sing[account].five_judge1;
	cout << "������רҵ��ί2�Ĵ��\n";
	cin >> sing[account].five_judge2;
	cout << "������רҵ��ί3�Ĵ��\n";
	cin >> sing[account].five_judge3;
	cout << "������רҵ��ί4�Ĵ��\n";
	cin >> sing[account].five_judge4;
	cout << "������רҵ��ί5�Ĵ��\n";
	cin >> sing[account].five_judge5;
	sing[account].five_judge = sing[account].five_judge1 + sing[account].five_judge2 + sing[account].five_judge3 + sing[account].five_judge4 + sing[account].five_judge5;
	sing[account].total_score = ((double)sing[account].public_vote + sing[account].five_judge) / 6;
	sing[account].number = account + 1;
	cout << "�Ѿ��ɹ�¼����Ϊ" << sing[account].number << "�ĸ��֣�\a" << endl;
	account++;
	Sleep(1500);
	system("cls");
}
void search()
{
	int i = 0;
	while (1)
	{
		cout << "�����ѯ�ĸ��ֵı����...\n";
		cin >> i;
		printf("���ڲ�ѯ��...\n");
		Sleep(1000);
		if (i > 0)
		{
			if (sing[i - 1].number)
			{
				if (i <= account)
				{
					cout << "���ֱ�� " << i << endl << "�������� " << sing[i - 1].name << endl << "������Ŀ���� " << sing[i - 1].music_name
						<< endl << "������ί��ͶƱ�� " << sing[i - 1].public_vote << endl << "5��רҵ��ί���ܴ�� " << sing[i - 1].five_judge << endl
						<< "�ܷ� " << setiosflags(ios::fixed) << setprecision(1) << sing[i - 1].total_score << endl;
					break;
				}
				else
				{
					cout << "���޴��ˣ�����������\n";
					continue;
				}
			}
			else
			{
				cout << "���޴��ˣ�����������\n";
				continue;
			}
		}
		else
		{
			cout << "����Ƿ�������������\n";
			continue;
		}

	}
	system("pause");
	system("cls");
}
void _delete(singer* sing)
{
	while (1)
	{
		int p = 0;
		char arr[5];
		while (1)
		{
			cout << "��������ɾ�����Ϊ���ٵĸ��ֵ���Ϣ" << endl;
			cin >> p;
			if (p)
			{
				p--;
				break;
			}
			else
				cout << "����ֵ�������������룡\n";
		}
		sing[p].number = 0;
		cout << "�Ѿ�ɾ�����Ϊ" << ++p << "�ĸ��ֵ���Ϣ��\a" << endl;
		Sleep(1500);
		system("cls");
		bool flag = true;
		while (flag)
		{
			cout << "�Ƿ��������?(Y/N)" << endl;
			cin >> arr;
			if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0 ||
				strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
			{
				flag = false;
				system("cls");
			}
			else
				cout << "�����������������\n";
		}
		if (strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
		{
			return;
		}
	}

}
void help()
{
	printf("������1���������������Ϣģʽ��������ʾ������������ֱ�ţ�������������Ŀ���ƣ�������ί��ͶƱ����5��רҵ��ί�Ĵ�֡�\n(������ί�ܹ�100Ʊ��רҵ��ίÿ��100Ʊ,������Զ�����ܷ֣����������Ѿ��ɹ�¼����ΪX�ĸ���ʱ����������ɹ���\n���ϵͳ��ѯ���Ƿ�������룬�밴��Ը����Y / Nѡ���Ƿ�������롣\n\
������2���������д�ӡ�Ѿ�¼������Եĸ�����Ϣ��\n\
������3�����򽫰����ֽܷ���ķ�ʽ���д�ӡ������Ϣ��\n\
������4�������ṩһ��¼�������Ϣ�Ļ��ᣬʹ�÷���������1���ƣ�����׸����\n\
������5������������ı�ţ���ӡ��Ӧ��ŵĸ�����Ϣ��\n\
������6��ɾȥ�����ŵĸ��ֵ������Ϣ��ʹ֮�޷�����ѯ��\n\
������0�������˳�����ӡ��������Ϣ��\n");
	system("pause");
	system("cls");
}
int main()
{
	char i[10]="0";
	int count = 0;
	puts("\twelcome to use \"���Ǹ��ִ��ϵͳ\"\n\a");
	Sleep(1500);
	system("cls");
	while (i)
	{
		menu();
		cin >> i;
		if (strlen(i) == 1)
		{
			if (i[0] >= '0' && i[0] <= '7')
			{
				switch (i[0]-48)
				{
				case 1://���������Ϣ
				{
					count = input(sing, account);
					account = count;
					break;
				}
				case 2://���������Ϣ
				{
					output(sing, account);
					break;
				}
				case 3://���ֳɼ�����
				{
					singer copy_sing[N];
					for (int i = 0;i < account;i++)
					{
						memcpy(&copy_sing[i], &sing[i], sizeof(singer));
					}
					struct_bubble_sort(copy_sing);
					break;
				}
				case 4://��Ӹ�����Ϣ
				{
					ADD(sing);
					break;
				}
				case 5://��ѯ������Ϣ
				{
					search();
					break;
				}
				case 6://ɾ��������Ϣ
				{
					_delete(sing);
					break;
				}
				case 7://����
				{
					help();
					break;
				}
				case 0://�˳�
					cout << "���Ǹ��ִ��ϵͳ\n";
					Sleep(1000);
					system("cls");
					system("pause");
					return 0;
				default:
				{
					cout << "��������һ���Ƿ�ֵ�����������룺\n";
					break;
				}
				}
			}
			else
				cout << "��������һ���Ƿ�ֵ�����������룺\n";
		}
		else
			cout << "��������һ���Ƿ�ֵ�����������룺\n";
	}
	
}

//Athley all right reserved