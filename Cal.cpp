#include <iostream>
#include<time.h>
#include<Windows.h>
#include<stdio.h>
using namespace std;
struct student
{
	int num;
	char name[20];
	int score;
}student[100], student1;
int n = 0, d = 0, k = 0, n0 = 0;
int menu();
int practise();
int exam();
int query();
int sort();
int del();
int main()
{
	menu();
	return 0;
}
int practise()
{
	srand((int)time(0));
	int ANSWER, a, b, p, q, i, p1, q1, ANSWER1, ANSWER2, ANSWER3, ANSWER4, next, t, j;
	double rate;
	n = n + 1;
	a = rand() % 100;
	b = rand() % 100;
	t = rand() % 100;
	ANSWER1 = a + b;
	if (a < b)
	{
		j = a; a = b; b = j;
		ANSWER2 = a - b;
	}
	else ANSWER2 = a - b;

	ANSWER3 = a * b;

	for (i = 0; i < 100000; i++)
	{
		p1 = rand() % 100;
		q1 = rand() % 100;
		if (p1 % q1 == 0)
		{
			p = p1;
			q = q1;
			ANSWER4 = p / q;
			break;
		}
	}

	if (t % 4 == 0)
	{
		cout << "\t\t\t\t" << a << "+" << b << "=" << endl;
		cout << "\t\t\t\t��������ȷ�𰸣�";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER1)
			{
				cout << "����ȷ";
				d = d + 1; break;
			}
			cout << "\t\t\t\t�𰸴���,�㻹��" << i << "�λ���" << endl;
			cout << "\t\t\t\t��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
		}
		cout << "��Ϊ:" << ANSWER1 << endl;
	}

	if (t % 4 == 1)
	{
		cout << "\t\t\t\t" << a << "-" << b << "=" << endl;
		cout << "\t\t\t\t��������ȷ�𰸣�";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER2)
			{
				cout << "\t\t\t\t����ȷ";
				d = d + 1; break;
			}
			cout << "\t\t\t\t�𰸴���,�㻹��" << i << "�λ���" << endl;
			cout << "\t\t\t\t��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
		}
		cout << "��Ϊ:" << ANSWER2 << endl;
	}

	if (t % 4 == 2)
	{
		cout << "\t\t\t\t" << a << "*" << b << "=" << endl;
		cout << "\t\t\t\t��������ȷ�𰸣�";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER3)
			{
				cout << "����ȷ";
				d = d + 1; break;
			}
			cout << "\t\t\t\t�𰸴���,�㻹��" << i << "�λ���" << endl;
			cout << "\t\t\t\t��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
		}
		cout << "��Ϊ:" << ANSWER3 << endl;
	}

	if (t % 4 == 3)
	{
		cout << "\t\t\t\t" << p << "/" << q << "=" << endl;
		cout << "\t\t\t\t��������ȷ�𰸣�";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER4)
			{
				cout << "����ȷ";
				d = d + 1; break;
			}
			cout << "\t\t\t\t�𰸴���,�㻹��" << i << "�λ���" << endl;
			cout << "\t\t\t\t��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
		}
		cout << "��Ϊ:" << ANSWER4 << endl;
	}

	cout << "\t\t\t\t1.������ϰ" << endl << "\t\t\t\t0.�˳���ϰ" << endl << "��ѡ��";
	cin >> next;
	system("cls");
	if (next == 1)
		practise();
	if (next == 0)
	{
		double t1, t2;
		t1 = d; t2 = n;
		rate = t1 / t2 * 100;
		cout << "������Ϊ��" << n << endl
			<< "��ȷ����Ϊ:" << d << endl
			<< "��ȷ��Ϊ:" << rate << "%" << endl;
	}
	return 0;


}
int exam()
{
	srand((int)time(0));
	int ANSWER, a, b, p, q, i, p1, q1, j, ANSWER1, ANSWER2, ANSWER3, ANSWER4, c, t, next;
	int d1 = 0;
	double rate;
	cout << "������ѧ�ź�����:";
	cin >> student[k].num >> student[k].name;
	system("cls");
	cout << endl << "����������:";
	cin >> next;
	system("cls");
	n0 = n0 + 1;
	for (j = 0; j < next; j++)
	{
		a = rand() % 100;
		b = rand() % 100;
		t = rand() % 100;
		ANSWER1 = a + b;
		ANSWER2 = a - b;
		ANSWER3 = a * b;
		for (i = 0; i < 100000; i++)
		{
			p1 = rand() % 100;
			q1 = rand() % 100;
			if (p1 % q1 == 0)
			{
				p = p1;
				q = q1;
				ANSWER4 = p / q;
				break;
			}
		}

		if (t % 4 == 0)
		{
			cout << a << "+" << b << "=" << endl;
			cout << "��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
			if (ANSWER == ANSWER1)
			{
				cout << "����ȷ";
				d1 = d1 + 1;
			}
			else
				cout << "�𰸴���" << endl;
			cout << "��Ϊ:" << ANSWER1 << endl;
		}

		if (t % 4 == 1)
		{
			if (a >= b)
			{
				cout << a << "-" << b << "=" << endl;
				cout << "��������ȷ�𰸣�";
				cin >> ANSWER;
				system("cls");
				if (ANSWER == ANSWER2)
				{
					cout << "����ȷ";
					d1 = d1 + 1;
				}
				else
					cout << "�𰸴���" << endl;
				cout << "��Ϊ:" << ANSWER2 << endl;
			}
			else
			{
				j = a; a = b; b = j;
				cout << a << "-" << b << "=" << endl;
				cout << "��������ȷ�𰸣�";
				cin >> ANSWER;
				system("cls");
				if (ANSWER == ANSWER2)
				{
					cout << "����ȷ";
					d1 = d1 + 1;
				}
				else
					cout << "�𰸴���" << endl;
				cout << "��Ϊ:" << ANSWER2 << endl;
			}
		}

		if (t % 4 == 2)
		{
			cout << a << "*" << b << "=" << endl;
			cout << "��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
			if (ANSWER == ANSWER3)
			{
				cout << "����ȷ";
				d1 = d1 + 1;
			}
			else
				cout << "�𰸴���" << endl;
			cout << "��Ϊ:" << ANSWER3 << endl;
		}

		if (t % 4 == 3)
		{
			cout << p << "/" << q << "=" << endl;
			cout << "��������ȷ�𰸣�";
			cin >> ANSWER;
			system("cls");
			if (ANSWER == ANSWER4)
			{
				cout << "����ȷ";
				d1 = d1 + 1;
			}
			else
				cout << "�𰸴���" << endl;
			cout << "��Ϊ:" << ANSWER4 << endl;
		}
	}


	double t1, t2;
	t1 = d1; t2 = next;
	rate = t1 / t2 * 100;
	student[k].score = rate;
	cout << "��ķ���Ϊ��" << student[k].score;
	k = k + 1;
	return 0;
}
int query()
{
	int a, i, k1;
	cout << endl << "��������Ҫ��ѯ��ѧ��ѧ��:";
	cin >> a;
	system("cls");
	cout << endl;
	for (i = 0; i < n0; i++)
	{
		if (a == student[i].num)
		{
			k1 = i;
			cout << "��ѧ���ķ���Ϊ��" << student[k1].score << endl;
			break;
		}
	}
	if (i == n0)
		cout << "���޴���,���һ���Ƿ�������ȷ��" << endl;
	return 0;
}
int sort()
{
	int j, i;
	for (j = 0; j < n0; j++)
		for (i = 0; i < n0 + 1 - j; i++)
			if (student[i].score < student[i + 1].score)
			{
				student1 = student[i];
				student[i] = student[i + 1];
				student[i + 1] = student1;
			}
	for (i = 0; i < n0; i++)
		cout << student[i].num << " " << student[i].name << " " << student[i].score << endl;
	return 0;
}
int del()
{
	int b, i, h;
	cout << endl << "��������Ҫɾ����ѧ��ѧ��:";
	cin >> b;
	system("cls");
	cout << endl;
	for (i = 0; i < n0; i++)
	{
		if (b == student[i].num)
		{
			for (h = i; h < n0; h++)
			{
				student[h] = student[h + 1];
			}
			n0 = n0 - 1;
			break;
		}
	}
	if (h == n0)
		cout << "����ɾ����" << endl;
	return 0;
}
int menu()
{
	int choose;
	cout << "��ӭ������Сѧ������" << endl;
	cout << "1.������ϰ" << endl << endl;
	cout << "2.���㿼��" << endl << endl;
	cout << "3.�ɼ���ѯ" << endl << endl;
	cout << "4.�ɼ�����" << endl << endl;
	cout << "5.�ɼ�ɾ��" << endl << endl;
	cout << "0.�˳�" << endl;
	cout << "��ѡ��";
	cin >> choose;
	system("cls");
	switch (choose)
	{
	case 1:practise(); menu(); break;
	case 2:exam(); menu(); break;
	case 3:query(); menu(); break;
	case 4:sort(); menu(); break;
	case 5:del(); menu(); break;
	case 0:break;
	}
	return 0;
}
//tzx all right reserved