#include<iostream>
#include<Windows.h>
using namespace std;
#define BOARD_SIZE 4
char arrY[] = "Y";
char arry[] = "y";
char arrN[] = "N";
char arrn[] = "n";
#define WIN_COUNT 3
//��� 

class Board {
public:
	Board()
	{
		for (int i = 0;i < BOARD_SIZE;i++)
		{
			for (int j = 0; j< BOARD_SIZE;j++)
			{
				board[i][j] = ' ';
			}
		}
	}
	void clean()
	{
		for (int i = 0;i < BOARD_SIZE;i++)
		{
			for (int j = 0;j < BOARD_SIZE;j++)
			{
				board[i][j] = ' ';
			}
		}
	}
    // �ж�ĳ��λ���Ƿ�Ϊ��
    bool isEmpty(int x, int y)
    {
        return board[x - 1][y - 1] == ' ';
    }

    // �ж�ĳ��λ���Ƿ�Ϊ����
    bool isBlack(int x, int y)
    {
        return board[x - 1][y - 1] == 'X';
    }

    // �ж�ĳ��λ���Ƿ�Ϊ����
    bool isWhite(int x, int y)
    {
        return board[x - 1][y - 1] == 'O';
    }

    // �º���
    void putBlack(int x, int y)
    {
        board[x - 1][y - 1] = 'X';
    }

    // �°���
    void putWhite(int x, int y)
    {
        board[x - 1][y - 1] = 'O';
    }

    // �ж��Ƿ�ʤ��
    bool isWin_Black(int x, int y)
    {

        int count = 1;
        for (int i = y - 1; i >= 0 && isBlack(x, i); i--)
        {
            count++;
        }
        for (int i = y + 1; i < BOARD_SIZE && isBlack(x, i); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }


        count = 1;
        for (int i = x - 1; i >= 0 && isBlack(i, y); i--)
        {
            count++;
        }
        for (int i = x + 1; i < BOARD_SIZE && isBlack(i, y); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }


        count = 1;
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0 && isBlack(i, j); i--, j--)
        {
            count++;
        }
        for (int i = x + 1, j = y + 1; i < BOARD_SIZE && j < BOARD_SIZE && isBlack(i, j); i++, j++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        count = 1;
        for (int i = x - 1, j = y + 1; i >= 0 && j < BOARD_SIZE && isBlack(i, j); i--, j++)
        {
            count++;
        }
        for (int i = x + 1, j = y - 1; i < BOARD_SIZE && j >= 0 && isBlack(i, j); i++, j--)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }
        return false;

    }
    bool isWin_White(int x, int y)
    {

        int count = 1;
        for (int i = y - 1; i >= 0 && isWhite(x , i); i--)
        {
            count++;
        }
        for (int i = y+1; i < BOARD_SIZE && isWhite(x, i); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        
        count = 1;
        for (int i = x - 1; i >= 0 && isWhite(i, y); i--)
        {
            count++;
        }
        for (int i = x+1; i < BOARD_SIZE && isWhite(i, y ); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

         
        count = 1;
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0 && isWhite(i, j); i--, j--)
        {
            count++;
        }
        for (int i = x+1, j = y+1; i < BOARD_SIZE && j < BOARD_SIZE && isWhite(i, j); i++, j++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }


        count = 1;
        for (int i = x - 1, j = y+1; i >= 0 && j < BOARD_SIZE && isWhite(i, j); i--, j++)
        {
            count++;
        }
        for (int i = x+1, j = y - 1; i < BOARD_SIZE && j >= 0 && isWhite(i, j); i++, j--)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        return false;
    }
    void PrintBoard()
    {
            cout << endl;
    cout << "  1   2   3   4" << endl;
    cout << "1 " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " | " << board[0][3]<<endl;
    cout << " ---|---|---|---" << endl;;
    cout << "2 " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " | " << board[1][3] << endl;
    cout << " ---|---|---|---" << endl;
    cout << "3 " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " | " << board[2][3] << endl;
    cout << " ---|---|---|---" << endl;
    cout << "4 " << board[3][0] << " | " << board[3][1] << " | " << board[3][2] << " | " << board[3][3] << endl;
    cout << endl;
    cout << endl;
    }
private:
	char board[BOARD_SIZE][BOARD_SIZE];
};
class Player : public Board
{
public:
    Player()
    {
        x = 0;
        y = 0;
    }
    bool isVaild(int x,int y,Board &a) 
    {
        if (a.isBlack(x, y) || a.isWhite(x , y ) || x - 1 < 0 || y - 1 < 0||x-1>3||y-1>3)
        {
            cout << "��������һ���Ƿ�ֵ\n";
            return false;
        }
        else
            return true;
    }

private:
    int x, y;
};
class Game  
{
public:
    Game()
    {
        Player_NUM=0;
        score[0] = 0;
        score[1] = 0;
    }
    void Begin()//��ӭҳ
    {
        cout << "��ӭ���������壡\a\n";
        Sleep(1000);
        system("cls");
    }
    void First_Player()
    {
        
        while (1)
        {
            cout << "��ѡ��������ֻ��ǰ������֣�\n����Ǻ��壬������1������ǰ��壬������0\n";
            cin >> Player_NUM;
            if (Player_NUM == 0|| Player_NUM==1)
            {
                
                break;
            }
            else
            {
                cout << "��������һ�������ֵ�����������룡\n";
            }
        }
    }
    bool Input(Player&A,Player&B,Board&a)
    {
        int x=0, y=0;
        if (Player_NUM == 1)
        {
            while (1)
            {
                cout << "������������������\n";
                Player_NUM -= 1;
                cin >> x >> y;
                if (A.isVaild(x, y, a))
                {
                    a.putBlack(x, y);
                    break;
                }
            }
            if (a.isWin_Black(x, y))
            {
                score[0]++;
                return true;
            }
            else
                return false;
        }
        else
        {
          
            while (1)
            {
                cout << "������������������\n";
                Player_NUM += 1;
                cin >> x >> y;
                if (B.isVaild(x, y, a))
                {
                    a.putWhite(x, y);
                    break;
                }
            }
            if (a.isWin_White(x, y))
              {
                score[1]++;
                return true;
              }
                   
            else
                return false;
        }
    }
    void Score_Table()
    {
        cout << "��ǰ������" << score[0] << "   " << "����" << score[1] << endl;
    }
    void WIN()
    {
        if (Player_NUM == 0)
        {
            cout << "����ʤ����\n";
        }
        else
        {
            cout << "����ʤ����\n";
        }
    }
private:
    int Player_NUM;
    int score[2];
};
int main()
{
    char arr[5];
    bool flag = true;
    Game game;
    Player A, B;
    Board board;
    game.Begin();
    while (flag)
    {
        board.clean();
        game.First_Player();
        while (1)
        {
            board.PrintBoard();
            if (game.Input(A, B, board))
            {
                game.WIN();
                board.PrintBoard();
                break;
            }
        }
        game.Score_Table();
        cout << "�Ƿ�������һ�ѣ�(Y/N)" << endl;
        cin >> arr;
        if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0)
            flag = true;
        else
            flag = false;
    }

    return 0;
}
