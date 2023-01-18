#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<Windows.h>
#include<iomanip>
#define N 1000
using namespace std;
int account = 0;//输入计数,个数
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
		cout << "是否继续输入?(Y/N)" << endl;
		cin >> arr;
		if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0 ||strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
		{
			flag = false;
		}
		else
			cout << "输入错误，请重新输入\n";
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
	cout << "########1      输入歌手信息  ########\n";
	cout << "########2      输出歌手信息  ########\n";
	cout << "########3      歌手成绩排序  ########\n";
	cout << "########4      添加歌手信息  ########\n";
	cout << "########5      查询歌手信息  ########\n";
	cout << "########6      删除歌手信息  ########\n";
	cout << "########7      使用与帮助    ########\n";
	cout << "########0      退出我是歌手  ########\n";
	cout << "#####################################\n";
	cout << "请输入...\n";
}
int input(singer* sing, int acc)//歌手编号，姓名，比赛曲目名称，大众评委的投票数，5个专业评委的打分，总分
{
	int i = 0;
	for (i = acc;i < N;i++)
	{
		sing[i].number = i + 1;
		cout << "请输入选手姓名\n";
		cin >> sing[i].name;
		cout << "请输入比赛的曲目名称\n";
		cin >> sing[i].music_name;
		cout << "请输入大众评委的投票数\n";
		cin >> sing[i].public_vote;
		cout << "请输入专业评委1的打分\n";
		cin >> sing[i].five_judge1;
		cout << "请输入专业评委2的打分\n";
		cin >> sing[i].five_judge2;
		cout << "请输入专业评委3的打分\n";
		cin >> sing[i].five_judge3;
		cout << "请输入专业评委4的打分\n";
		cin >> sing[i].five_judge4;
		cout << "请输入专业评委5的打分\n";
		cin >> sing[i].five_judge5;
		sing[i].five_judge = sing[i].five_judge1 + sing[i].five_judge2 + sing[i].five_judge3 + sing[i].five_judge4 + sing[i].five_judge5;
		sing[i].total_score = ((double)sing[i].public_vote + sing[i].five_judge) / 6;
		cout << "已经成功录入编号为" << sing[i].number << "的歌手！\a" << endl;
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
void output(singer* sing, int p)//歌手编号，姓名，比赛曲目名称，大众评委的投票数，5个专业评委的打分，总分
{
	for (int i = 0;i < p;i++)
	{
		if (sing[i].number)
		{
			cout << "歌手编号 " << sing[i].number << endl << "歌手姓名 " << sing[i].name << endl << "比赛曲目名称 " << sing[i].music_name
				<< endl << "大众评委的投票数 " << sing[i].public_vote << endl << "5个专业评委的总打分 " << sing[i].five_judge << endl
				<< "总分 " <<  setiosflags(ios::fixed) << setprecision(1)<<sing[i].total_score << endl << endl;
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
			if (copy_sing[j].total_score < copy_sing[j + 1].total_score) //比较总分的大小
			{
				singer temp = copy_sing[j + 1];    //总分大的交换所在的数组元素
				copy_sing[j + 1] = copy_sing[j];
				copy_sing[j] = temp;
			}
		}
	}
	for (int i = 0;i < account;i++)
	{
		if (copy_sing[i].number)
		{
			cout << "第" << i + 1 << "\t" << "编号 " << copy_sing[i].number << "\t" << "歌手姓名 " << sing[i].name << "\t" << "比赛表演曲目 "
				<< copy_sing[i].music_name << "\t总分 " << setiosflags(ios::fixed) << setprecision(1) << copy_sing[i].total_score << endl;
		}
		else
			i--;
	}
	system("pause");
	system("cls");
}
void ADD(singer* sing)
{
	cout << "请注意，您即将录入编号为" << account + 1 << "的歌手的信息..." << endl;
	Sleep(3000);
	system("cls");
	cout << "请输入选手" << account + 1 << "的姓名\n";
	cin >> sing[account].name;
	cout << "请输入比赛的曲目名称\n";
	cin >> sing[account].music_name;
	cout << "请输入大众评委的投票数\n";
	cin >> sing[account].public_vote;
	cout << "请输入专业评委1的打分\n";
	cin >> sing[account].five_judge1;
	cout << "请输入专业评委2的打分\n";
	cin >> sing[account].five_judge2;
	cout << "请输入专业评委3的打分\n";
	cin >> sing[account].five_judge3;
	cout << "请输入专业评委4的打分\n";
	cin >> sing[account].five_judge4;
	cout << "请输入专业评委5的打分\n";
	cin >> sing[account].five_judge5;
	sing[account].five_judge = sing[account].five_judge1 + sing[account].five_judge2 + sing[account].five_judge3 + sing[account].five_judge4 + sing[account].five_judge5;
	sing[account].total_score = ((double)sing[account].public_vote + sing[account].five_judge) / 6;
	sing[account].number = account + 1;
	cout << "已经成功录入编号为" << sing[account].number << "的歌手！\a" << endl;
	account++;
	Sleep(1500);
	system("cls");
}
void search()
{
	int i = 0;
	while (1)
	{
		cout << "你想查询的歌手的编号是...\n";
		cin >> i;
		printf("正在查询中...\n");
		Sleep(1000);
		if (i > 0)
		{
			if (sing[i - 1].number)
			{
				if (i <= account)
				{
					cout << "歌手编号 " << i << endl << "歌手姓名 " << sing[i - 1].name << endl << "比赛曲目名称 " << sing[i - 1].music_name
						<< endl << "大众评委的投票数 " << sing[i - 1].public_vote << endl << "5个专业评委的总打分 " << sing[i - 1].five_judge << endl
						<< "总分 " << setiosflags(ios::fixed) << setprecision(1) << sing[i - 1].total_score << endl;
					break;
				}
				else
				{
					cout << "查无此人，请重新输入\n";
					continue;
				}
			}
			else
			{
				cout << "查无此人，请重新输入\n";
				continue;
			}
		}
		else
		{
			cout << "输入非法，请重新输入\n";
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
			cout << "请问你想删除编号为多少的歌手的信息" << endl;
			cin >> p;
			if (p)
			{
				p--;
				break;
			}
			else
				cout << "输入值出错，请重新输入！\n";
		}
		sing[p].number = 0;
		cout << "已经删除编号为" << ++p << "的歌手的信息！\a" << endl;
		Sleep(1500);
		system("cls");
		bool flag = true;
		while (flag)
		{
			cout << "是否继续输入?(Y/N)" << endl;
			cin >> arr;
			if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0 ||
				strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
			{
				flag = false;
				system("cls");
			}
			else
				cout << "输入错误，请重新输入\n";
		}
		if (strcmp(arr, arrN) == 0 || strcmp(arr, arrn) == 0)
		{
			return;
		}
	}

}
void help()
{
	printf("①输入1，启动输入歌手信息模式，按照提示词依次输入歌手编号，姓名，比赛曲目名称，大众评委的投票数，5个专业评委的打分。\n(大众评委总共100票，专业评委每人100票,程序会自动算出总分），当跳出已经成功录入编号为X的歌手时，表明输入成功，\n随后系统将询问是否继续输入，请按意愿输入Y / N选择是否结束输入。\n\
②输入2，程序将自行打印已经录入的所以的歌手信息。\n\
③输入3，程序将按照总分降序的方式进行打印歌手信息。\n\
④输入4，程序将提供一次录入歌手信息的机会，使用方法和输入1类似，不再赘述。\n\
⑤输入5，将按照输入的编号，打印相应编号的歌手信息。\n\
⑥输入6，删去输入编号的歌手的相关信息，使之无法被查询。\n\
⑦输入0，程序退出，打印制作人信息。\n");
	system("pause");
	system("cls");
}
int main()
{
	char i[10]="0";
	int count = 0;
	puts("\twelcome to use \"我是歌手打分系统\"\n\a");
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
				case 1://输入歌手信息
				{
					count = input(sing, account);
					account = count;
					break;
				}
				case 2://输出歌手信息
				{
					output(sing, account);
					break;
				}
				case 3://歌手成绩排序
				{
					singer copy_sing[N];
					for (int i = 0;i < account;i++)
					{
						memcpy(&copy_sing[i], &sing[i], sizeof(singer));
					}
					struct_bubble_sort(copy_sing);
					break;
				}
				case 4://添加歌手信息
				{
					ADD(sing);
					break;
				}
				case 5://查询歌手信息
				{
					search();
					break;
				}
				case 6://删除歌手信息
				{
					_delete(sing);
					break;
				}
				case 7://帮助
				{
					help();
					break;
				}
				case 0://退出
					cout << "我是歌手打分系统\n";
					Sleep(1000);
					system("cls");
					system("pause");
					return 0;
				default:
				{
					cout << "你输入了一个非法值，请重新输入：\n";
					break;
				}
				}
			}
			else
				cout << "你输入了一个非法值，请重新输入：\n";
		}
		else
			cout << "你输入了一个非法值，请重新输入：\n";
	}
	
}

//Athley all right reserved
