
//#include <iostream>
//#include <stdlib.h>
//using namespace std;
//class CGobang
//{
//private:
//    char chSort;
//    int nWin;
//    int nLose;
//    static int nDraw;
//    static char achBoard[9][9];
//    static int nSize;
//public:
//    CGobang(char chshort);
//    void PlayTurn(void);
//    int judge();
//    void Win(void);
//    void Lose(void);
//    static void Draw(void);
//    void PrintInfo(void);
//    static void PrintBoard(void);
//    static void GetFull(void);
//    static void InitialBoard(void);
//};
//void PrintBoard();              // game board
//void PrintInfo();               // some info about the rules of the game is printed
//void PrintStats(int, int, int);      // prints the stats of the  match
//void IfError(int&, int&); // When invalid input is entered, prints the error
//void ChoiceOfChar(char&);      // Asks the users if they want to play again
//void PromptTurnO(int&, int&);   // Prompts the first user for data
//void PromptTurnX(int&, int&);   // Second user has to input coordinates
//char board[3][3];               // array definition
//int main()
//{
//    int ROW;          // elements of 2 dimensional array!
//    int COLUMN;
//    int FirstPlayer;      // number of winning games for first player
//    int SecondPlayer;
//    int Draws;         // number of draws in a game
//    FirstPlayer = 0;
//    SecondPlayer = 0;
//    Draws = 0;
//    char choice;
//    choice = 'Y';       // Initial value is Y in order to initialize the main loop
//    PrintInfo();
//    while (choice == 'Y') // In case the players want to play again
//    {                                     		// this is the main loop
//        for (ROW = 0; ROW < 3; ROW++)       		// these forloops are used to process the array
//            for (COLUMN = 0; COLUMN < 3; COLUMN++)  	// by row and column
//                board[ROW][COLUMN] = ' ';                   	// blank characters as initial values
//        int x;            							// (x,y) coordinates entered by the users
//        int y;
//        int SpotsOnBoard; 							// this is the sum of spots available on the game board
//        SpotsOnBoard = 0;
//        while (SpotsOnBoard <= 9) 					// because there is only 9 characters available on the board
//        {
//            if (SpotsOnBoard == 0)
//                PrintBoard();  							// This function draws initialy the blank game board
//                                                         // so it is easier for the user to pick the x and y values
//
//            PromptTurnO(x, y);
//
//            IfError(x, y);     						// If the user's input is invalid, this function prints
//                                                 // the error message and prompts for correction
//            board[x - 1][y - 1] = 'O';         				// actually the array starts from 0, NOT from 1
//            SpotsOnBoard++;             				// (as entered by the user)
//                                                     // so the program have to "fix" the input
//            PrintBoard();						         // If 3 coordintates are O's in one of 8 possible
//                                                 //winning combinations, then O wins
//            if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
//            {
//                cout << " O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++;
//                break;
//            }
//            else if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
//            {
//                cout << "O player wins the game" << endl;
//                FirstPlayer++; 						// counts the number of won games
//                break;   							// break statement is used to make sure that only one possibility
//            }         							// will be processed
//            else if (SpotsOnBoard == 9)
//            {
//                cout << "Draw!" << endl;
//                Draws++;
//                break;  							// Without this brake statement it was not working propertly
//            }
//
//            PromptTurnX(x, y);
//            IfError(x, y);
//            board[x - 1][y - 1] = 'X';
//            SpotsOnBoard++;
//            PrintBoard();
//            if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//            else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
//            {
//                cout << "X player is victorious" << endl;
//                SecondPlayer++;
//            }
//        }
//        ChoiceOfChar(choice);
//    }
//
//    PrintStats(FirstPlayer, SecondPlayer, Draws);
//
//    system("PAUSE");
//    return 0;
//}
//
//void PrintBoard()
//// Post : The Game board is printed to help with choosing the coordintates
////        Either X or O will be printed on the board.
////        Board is updated while the game progresses
//{
//    cout << endl;
//    cout << "  1   2   3 " << endl;
//    cout << "1 " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
//    cout << " ---|---|---" << endl;;
//    cout << "2 " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
//    cout << " ---|---|---" << endl;
//    cout << "3 " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
//    cout << endl;
//    cout << endl;
//}
//
//void PrintInfo()
//// Post : Some info about the rules of the game is printed
//{
//    cout << "First player is represented by O, second by X." << endl;
//    cout << "Enter the coordinates for Rows and Columns" << endl;
//    cout << "Strike enter when Done." << endl;
//    cout << endl;
//}
//
//void PrintStats(int FirstPlayer, int SecondPlayer, int Draws)
//// Pre : Players have to decide to exit the game.
//// Post : Returns the number of won games and draws.
//{
//    cout << "The O player have won " << FirstPlayer << " times" << endl;
//    cout << "The X player have won " << SecondPlayer << " times" << endl;
//    cout << "There was " << Draws << " draws" << endl;
//    cout << "Thanks for using my program" << endl;
//}
//
//void IfError(int& x, int& y)
//// Pre : User entered invalid data, program doesn't kow where to put them
//// Post : Error message is printed, user is prompted to enter the right input
//{
//    while (x > 3 || x < 1 || y > 3 || y < 1 || ('O' == board[x - 1][y - 1]
//        || 'X' == board[x - 1][y - 1]))
//    {
//        cout << "This coordinate is not allowed, try again" << endl;
//        cout << "row: ";
//        cin >> x;
//        cout << "column: ";
//        cin >> y;
//    }
//}
//
//void ChoiceOfChar(char& choice)
//// Pre : Entire program has been executed
//// Post : User is given a chance to play again
//{
//    cout << endl;
//    cout << " Press CAPITAL Y if you want to play again." << endl;
//    cout << " Otherwise, press any other letter key to exit the loop." << endl;
//    cin >> choice;
//}
//
//void PromptTurnO(int& x, int& y)
//// Post : First player enters the coordinates of a spot on a game board
//{
//    cout << "Turn of the first player (O), enter the coordinates" << endl;
//    cout << "Row: ";
//    cin >> x;
//    cout << "Column: ";
//    cin >> y;
//}
//
//void PromptTurnX(int& x, int& y)
//// Post : Second player enters the coordinates of a spot on a game board
//{
//    cout << "Turn of the second player (X), enter the coordinates" << endl;
//    cout << "Row: ";
//    cin >> x;
//    cout << "Column: ";
//    cin >> y;
//}

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string.h>
#include"color.h"
using namespace std;

const int BOARD_SIZE = 15;
const int WIN_COUNT = 5;
int score[3];
char arrY[] = "Y";
char arry[] = "y";
char arrN[] = "N";
char arrn[] = "n";
// 棋盘类
class Board
{

public:
    friend class player;
    Board() // 构造函数，初始化棋盘
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[i][j] = '+';
            }
        }
    }
    bool display()
    {
        char arr[5];
        cout << "是否想再玩一把？(Y/N)" << endl;
        cin >> arr;
        if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0)
            return true;
        else
            return false;
    }
    void clean()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[i][j] = '+';
            }
        }
    }
    // 绘制棋盘
    void draw()
    {
        cout << " ";
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            cout << " " << i + 1;
        }
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            cout << i + 1 << " ";
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    // 判断某个位置是否为空
    bool isEmpty(int x, int y)
    {
        return board[x][y] == '+';
    }

    // 判断某个位置是否为黑子
    bool isBlack(int x, int y)
    {
        return board[x][y] == 'X';
    }

    // 判断某个位置是否为白子
    bool isWhite(int x, int y)
    {
        return board[x][y] == 'O';
    }

    // 下黑子
    void putBlack(int x, int y)
    {
        board[x][y] = 'X';
    }

    // 下白子
    void putWhite(int x, int y)
    {
        board[x][y] = 'O';
    }

    // 判断是否胜利
    bool isWin(int x, int y)
    {
        // 判断水平方向是否有五个连续的同色棋子
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

        // 判断竖直方向是否有五个连续的同色棋子
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

        // 判断左上到右下方向是否有五个连续的同色棋子
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
        // 判断右上到左下方向是否有五个连续的同色棋子
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

        // 判断水平方向是否有五个连续的同色棋子
        count = 1;
        for (int i = y - 1; i >= 0 && isWhite(x, i); i--)
        {
            count++;
        }
        for (int i = y + 1; i < BOARD_SIZE && isWhite(x, i); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断竖直方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 1; i >= 0 && isWhite(i, y); i--)
        {
            count++;
        }
        for (int i = x + 1; i < BOARD_SIZE && isWhite(i, y); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断左上到右下方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0 && isWhite(i, j); i--, j--)
        {
            count++;
        }
        for (int i = x + 1, j = y + 1; i < BOARD_SIZE && j < BOARD_SIZE && isWhite(i, j); i++, j++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断右上到左下方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 1, j = y + 1; i >= 0 && j < BOARD_SIZE && isWhite(i, j); i--, j++)
        {
            count++;
        }
        for (int i = x + 1, j = y - 1; i < BOARD_SIZE && j >= 0 && isWhite(i, j); i++, j--)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        return false;
    }
private:
    char board[BOARD_SIZE][BOARD_SIZE];
};

class player 
{
    public:
        player(char color)
        {
        this->color = color;
        }
        bool isVaild(int x, int y,Board & a)
        {
            if (a.board[x][y] != '+' || x > BOARD_SIZE || x<0 || y>BOARD_SIZE || y < 0)
            {
                cout << "你输入了一个非法值！\n";
                return true;
            }
        else
                if (color == 'X')
                {
                    a.putBlack(x, y);
                    return false;
                }
                

                else
                {
                    a.putWhite(x, y);
                    return false;
                }   
        }

        void display_WIN()
        {
            char name[8];
            if (color == 'X')
            {
                score[0]++;
                strcpy(name, "黑棋");
            }
            else
            {
                score[1]++;
                strcpy(name, "白棋");
            }    
            cout << name << "赢了！" << endl;
        }

    private: 
    char color;
};
class computerplayer
{

};
void menu()
{
    cout << "######################################\n";
    cout << "###########欢迎来到五子棋！###########\n";
    cout << "######################################\n";
    Sleep(1500);
    system("cls");
}
int Choose() 
{
int choose;
    begin:
    cout << "##########################################################\n";
    cout << "########1 人机对抗   2 双人对抗   3 规则    0 退出########\n";
    cout << "##########################################################\n";
    cin >> choose;
if (choose != 1 && choose != 2  && choose !=3 &&  choose!=0)
{
    cout << "请重新输入!\n";
    goto begin;
}
else
{
    if (choose == 1)
    {
        int color;
        Begin:
        cout << "请选择你想要使用的棋子\n0   黑棋 1   白棋\n";
        cin >> color;
        if (color == 0 || color == 1)
        {
            return color;
        }
        else
        {
            cout << "输入错误，请重新输入！\n";
            goto Begin;
        }
    }
    else if (choose == 2)
    {
        return 3;
    }
    else if (choose == 3)
    {
        cout;
    }
    else if (choose == 0)
    {
        exit;
    }
} 
}
int main()
{
    Board table;
    player A('X');
    player B('O');
    menu();
    int a = Choose();
    if (a == 3)
    {
        AGAIN:
        int x, y;
        int i = 0;
        table.draw();
        while (1) {
            bool flag = true;
            bool WIN = false;
            while (flag)
            {
                cout << "请黑棋玩家输入落子位置\n";
                cin >> x >> y;
                flag = A.isVaild(x, y, table);
                table.draw();
            }
            if (table.isWin(x, y))
            {
                A.display_WIN();
                WIN = true;//跳出循环
                flag = false;
            }
            else
                flag = true;
            while(flag)
            {
                cout << "请白棋玩家输入落子位置\n";
                cin >> x >> y;
                flag=B.isVaild(x, y, table);
                table.draw();
                if (table.isWin(x, y))
                {
                    B.display_WIN();
                    WIN = true;
                }   
            }
            if (WIN)
            {
                break;
            }
        }
        if (table.display())
        {
            table.clean();
            goto AGAIN;
        }
        else
        {
            system("cls");
            table.clean();
            Choose();
        }

    }
}
