#include<iostream>
#include<Windows.h>
using namespace std;
#define BOARD_SIZE 4
char arrY[] = "Y";
char arry[] = "y";
char arrN[] = "N";
char arrn[] = "n";
#define WIN_COUNT 3
//●○ 

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
    // 判断某个位置是否为空
    bool isEmpty(int x, int y)
    {
        return board[x - 1][y - 1] == ' ';
    }

    // 判断某个位置是否为黑子
    bool isBlack(int x, int y)
    {
        return board[x - 1][y - 1] == 'X';
    }

    // 判断某个位置是否为白子
    bool isWhite(int x, int y)
    {
        return board[x - 1][y - 1] == 'O';
    }

    // 下黑子
    void putBlack(int x, int y)
    {
        board[x - 1][y - 1] = 'X';
    }

    // 下白子
    void putWhite(int x, int y)
    {
        board[x - 1][y - 1] = 'O';
    }

    // 判断是否胜利
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
            cout << "你输入了一个非法值\n";
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
    void Begin()//欢迎页
    {
        cout << "欢迎来到三子棋！\a\n";
        Sleep(1000);
        system("cls");
    }
    void First_Player()
    {
        
        while (1)
        {
            cout << "请选择黑棋先手还是白棋先手？\n如果是黑棋，请输入1，如果是白棋，请输入0\n";
            cin >> Player_NUM;
            if (Player_NUM == 0|| Player_NUM==1)
            {
                
                break;
            }
            else
            {
                cout << "你输入了一个错误的值，请重新输入！\n";
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
                cout << "请黑棋输入下棋的坐标\n";
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
                cout << "请白棋输入下棋的坐标\n";
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
        cout << "当前，黑棋" << score[0] << "   " << "白棋" << score[1] << endl;
    }
    void WIN()
    {
        if (Player_NUM == 0)
        {
            cout << "黑棋胜利！\n";
        }
        else
        {
            cout << "白棋胜利！\n";
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
        cout << "是否想再玩一把？(Y/N)" << endl;
        cin >> arr;
        if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0)
            flag = true;
        else
            flag = false;
    }

    return 0;
}
