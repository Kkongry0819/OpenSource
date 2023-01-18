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
		cout << "\t\t\t\t请输入正确答案：";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER1)
			{
				cout << "答案正确";
				d = d + 1; break;
			}
			cout << "\t\t\t\t答案错误,你还有" << i << "次机会" << endl;
			cout << "\t\t\t\t请输入正确答案：";
			cin >> ANSWER;
			system("cls");
		}
		cout << "答案为:" << ANSWER1 << endl;
	}

	if (t % 4 == 1)
	{
		cout << "\t\t\t\t" << a << "-" << b << "=" << endl;
		cout << "\t\t\t\t请输入正确答案：";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER2)
			{
				cout << "\t\t\t\t答案正确";
				d = d + 1; break;
			}
			cout << "\t\t\t\t答案错误,你还有" << i << "次机会" << endl;
			cout << "\t\t\t\t请输入正确答案：";
			cin >> ANSWER;
			system("cls");
		}
		cout << "答案为:" << ANSWER2 << endl;
	}

	if (t % 4 == 2)
	{
		cout << "\t\t\t\t" << a << "*" << b << "=" << endl;
		cout << "\t\t\t\t请输入正确答案：";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER3)
			{
				cout << "答案正确";
				d = d + 1; break;
			}
			cout << "\t\t\t\t答案错误,你还有" << i << "次机会" << endl;
			cout << "\t\t\t\t请输入正确答案：";
			cin >> ANSWER;
			system("cls");
		}
		cout << "答案为:" << ANSWER3 << endl;
	}

	if (t % 4 == 3)
	{
		cout << "\t\t\t\t" << p << "/" << q << "=" << endl;
		cout << "\t\t\t\t请输入正确答案：";
		cin >> ANSWER;
		system("cls");
		for (i = 2; i > 0; i--)
		{
			if (ANSWER == ANSWER4)
			{
				cout << "答案正确";
				d = d + 1; break;
			}
			cout << "\t\t\t\t答案错误,你还有" << i << "次机会" << endl;
			cout << "\t\t\t\t请输入正确答案：";
			cin >> ANSWER;
			system("cls");
		}
		cout << "答案为:" << ANSWER4 << endl;
	}

	cout << "\t\t\t\t1.继续练习" << endl << "\t\t\t\t0.退出练习" << endl << "请选择：";
	cin >> next;
	system("cls");
	if (next == 1)
		practise();
	if (next == 0)
	{
		double t1, t2;
		t1 = d; t2 = n;
		rate = t1 / t2 * 100;
		cout << "总题数为：" << n << endl
			<< "正确题数为:" << d << endl
			<< "正确率为:" << rate << "%" << endl;
	}
	return 0;


}
int exam()
{
	srand((int)time(0));
	int ANSWER, a, b, p, q, i, p1, q1, j, ANSWER1, ANSWER2, ANSWER3, ANSWER4, c, t, next;
	int d1 = 0;
	double rate;
	cout << "请输入学号和姓名:";
	cin >> student[k].num >> student[k].name;
	system("cls");
	cout << endl << "请输入题量:";
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
			cout << "请输入正确答案：";
			cin >> ANSWER;
			system("cls");
			if (ANSWER == ANSWER1)
			{
				cout << "答案正确";
				d1 = d1 + 1;
			}
			else
				cout << "答案错误" << endl;
			cout << "答案为:" << ANSWER1 << endl;
		}

		if (t % 4 == 1)
		{
			if (a >= b)
			{
				cout << a << "-" << b << "=" << endl;
				cout << "请输入正确答案：";
				cin >> ANSWER;
				system("cls");
				if (ANSWER == ANSWER2)
				{
					cout << "答案正确";
					d1 = d1 + 1;
				}
				else
					cout << "答案错误" << endl;
				cout << "答案为:" << ANSWER2 << endl;
			}
			else
			{
				j = a; a = b; b = j;
				cout << a << "-" << b << "=" << endl;
				cout << "请输入正确答案：";
				cin >> ANSWER;
				system("cls");
				if (ANSWER == ANSWER2)
				{
					cout << "答案正确";
					d1 = d1 + 1;
				}
				else
					cout << "答案错误" << endl;
				cout << "答案为:" << ANSWER2 << endl;
			}
		}

		if (t % 4 == 2)
		{
			cout << a << "*" << b << "=" << endl;
			cout << "请输入正确答案：";
			cin >> ANSWER;
			system("cls");
			if (ANSWER == ANSWER3)
			{
				cout << "答案正确";
				d1 = d1 + 1;
			}
			else
				cout << "答案错误！" << endl;
			cout << "答案为:" << ANSWER3 << endl;
		}

		if (t % 4 == 3)
		{
			cout << p << "/" << q << "=" << endl;
			cout << "请输入正确答案：";
			cin >> ANSWER;
			system("cls");
			if (ANSWER == ANSWER4)
			{
				cout << "答案正确";
				d1 = d1 + 1;
			}
			else
				cout << "答案错误！" << endl;
			cout << "答案为:" << ANSWER4 << endl;
		}
	}


	double t1, t2;
	t1 = d1; t2 = next;
	rate = t1 / t2 * 100;
	student[k].score = rate;
	cout << "你的分数为：" << student[k].score;
	k = k + 1;
	return 0;
}
int query()
{
	int a, i, k1;
	cout << endl << "请输入您要查询的学生学号:";
	cin >> a;
	system("cls");
	cout << endl;
	for (i = 0; i < n0; i++)
	{
		if (a == student[i].num)
		{
			k1 = i;
			cout << "该学生的分数为：" << student[k1].score << endl;
			break;
		}
	}
	if (i == n0)
		cout << "查无此人,检查一下是否输入正确！" << endl;
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
	cout << endl << "请输入您要删除的学生学号:";
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
		cout << "不能删除呐" << endl;
	return 0;
}
int menu()
{
	int choose;
	cout << "欢迎你来到小学生算数" << endl;
	cout << "1.计算练习" << endl << endl;
	cout << "2.计算考试" << endl << endl;
	cout << "3.成绩查询" << endl << endl;
	cout << "4.成绩排序" << endl << endl;
	cout << "5.成绩删除" << endl << endl;
	cout << "0.退出" << endl;
	cout << "请选择：";
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