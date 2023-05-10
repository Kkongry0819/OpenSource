
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
#include<cstring>
#include <iomanip> 
#include"color.h"
#include<vector>
#include"AI.h"
#include<stdlib.h>
#include<time.h>
using namespace std;

const int BOARD_SIZE = 15;
const int WIN_COUNT = 5;
int score[4];
const char arrY[] = "Y";
const char arry[] = "y";
const char arrN[] = "N";
const char arrn[] = "n";
typedef struct AISET
{
    int x;
    int y;
}ai;
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
    int get_data(int row,int col)
    {
        if (board[row][col] == 'X')//黑棋返回1
            return 1;
        else if (board[row][col] == 'O')
            return -1;
        else
            return 0;
    }
    bool display()
    {
        char arr[5];
        cout << "当前比分" << endl << "黑棋  " << score[0] << "  " << "白棋" << score[1]<<endl;
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
        cout << "  ";
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (i < 9)
                cout << " " << i + 1;
            else
                cout << " "<<(char)(i + 56);
        }
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if(i<9)
            {
                cout << " "<<i + 1 << " ";
            }
            else
            {
                cout << " "<<(char)(i + 56) << " ";
            }
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == 'X')
                {
                    color(4);
                    cout << board[i][j] << " ";
                    color(7);
                }
                else if (board[i][j] == 'O')
                {
                    color(6);
                    cout << board[i][j] << " ";
                    color(7);
                }
                else
                {
                    color(3);
                    cout << board[i][j] << " ";
                    color(7);
                }
            }
            cout << endl;
        }
    }

    // 判断某个位置是否为空
    bool isEmpty(int x, int y)
    {
        return board[x-1][y-1] == '+';
    }

    // 判断某个位置是否为黑子
    bool isBlack(int x, int y)//传进来的都是已经修正过的值
    {
        if (board[x][y] == 'X')
            return true;
        else
            return false;
    }

    // 判断某个位置是否为白子
    bool isWhite(int x, int y)
    {
        if (board[x][y] == 'O')
            return true;
        else
            return false;
    }

    // 下黑子
    void putBlack(int x, int y)
    {
        board[x-1][y-1] = 'X';
    }

    // 下白子
    void putWhite(int x, int y)
    {
        board[x-1][y-1] = 'O';
    }

    // 判断是否胜利
    bool isWin_black(int x, int y)
    {
        // 判断水平方向是否有五个连续的同色棋子
        int count = 1;
        for (int i = y - 2; i >= 0 && isBlack(x - 1, i); i--)
        {
            count++;
        }
        for (int i = y; i < BOARD_SIZE && isBlack(x - 1, i); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断竖直方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 2; i >= 0 && isBlack(i, y - 1); i--)
        {
            count++;
        }
        for (int i = x; i < BOARD_SIZE && isBlack(i, y - 1); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断左上到右下方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 2, j = y - 2; i >= 0 && j >= 0 && isBlack(i, j); i--, j--)
        {
            count++;
        }
        for (int i = x, j = y; i < BOARD_SIZE && j < BOARD_SIZE && isBlack(i, j); i++, j++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }
        // 判断右上到左下方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 2, j = y; i >= 0 && j < BOARD_SIZE && isBlack(i, j); i--, j++)
        {
            count++;
        }
        for (int i = x, j = y - 2; i < BOARD_SIZE && j >= 0 && isBlack(i, j); i++, j--)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }
        return false;

    }
    bool isWin_white(int x, int y)
    {
        // 判断水平方向是否有五个连续的同色棋子
        int count = 1;
        for (int i = y - 2; i >= 0 && isWhite(x-1, i); i--)
        {
            count++;
        }
        for (int i = y ; i < BOARD_SIZE && isWhite(x-1, i); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断竖直方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 2; i >= 0 && isWhite(i, y-1); i--)
        {
            count++;
        }
        for (int i = x ; i < BOARD_SIZE && isWhite(i, y-1); i++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断左上到右下方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 2, j = y - 2; i >= 0 && j >= 0 && isWhite(i, j); i--, j--)
        {
            count++;
        }
        for (int i = x , j = y ; i < BOARD_SIZE && j < BOARD_SIZE && isWhite(i, j); i++, j++)
        {
            count++;
        }
        if (count >= WIN_COUNT)
        {
            return true;
        }

        // 判断右上到左下方向是否有五个连续的同色棋子
        count = 1;
        for (int i = x - 2, j = y ; i >= 0 && j < BOARD_SIZE && isWhite(i, j); i--, j++)
        {
            count++;
        }
        for (int i = x , j = y - 2; i < BOARD_SIZE && j >= 0 && isWhite(i, j); i++, j--)
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
            if (a.board[x-1][y-1] != '+' || x-1 > BOARD_SIZE || x-1<0 || y-1>BOARD_SIZE || y-1 < 0)
            {
                if (a.isWhite(x-1, y-1))
                {
                    cout<<"你下在白棋上了！"<<endl;
                }
                else if (a.isBlack(x-1, y-1))
                {
                    cout << "你下在黑棋上了！" << endl;
                }
                else
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
        void display_AI_WIN()
        {
            score[2]++;
            cout << "玩家获得胜利！" << endl;
        }
    private: 
    char color;
};
class ComputerPlayer
{
public:
    ai AICalculate(Board& a);

};
ai ComputerPlayer::AICalculate(Board& a)
{

    int scoreMap[BOARD_SIZE][BOARD_SIZE];//期望（权重）表
    int playernum = 0;
    int ainum = 0;
    int emptynum = 0;
    for (int i = 0;i < BOARD_SIZE;i++)
    {
        for (int j = 0;j < BOARD_SIZE;j++)
        {
            scoreMap[i][j] = 0;
        }
    }
    for (int row = 0;row < BOARD_SIZE;row++)
    {
        for (int col = 0;col < BOARD_SIZE;col++)
        {

            if (a.get_data(row, col))continue;
            for (int y = -1;y <= 0;y++)
            {
                for (int x = -1;x <= 1;x++)
                {
                    
                    if (y == 0 && x != 1)
                    {
                        continue;
                    }
                    playernum = 0;
                    ainum = 0;
                    emptynum = 0;
                    for (int i = 1;i <= 4;i++)
                    {
                        int currow = row + i * y;//相对横竖坐标
                        int curcol = col + i * x;
                        if (currow >= 0 && currow < BOARD_SIZE && curcol >= 0 && curcol < BOARD_SIZE && a.get_data(currow, curcol) == 1)
                        {
                            playernum++;
                        }
                        else if (currow >= 0 && currow < BOARD_SIZE && curcol >= 0 && curcol < BOARD_SIZE && a.get_data(currow, curcol) == 0)
                        {
                            emptynum++;
                            break;
                        }
                        else
                            break;
                    }
                    for (int i = 1; i <= 4; i++)
                    {
                        int curRow = row - i * y;
                        int curCol = col - i * x;

                        if (curRow >= 0 && curRow < BOARD_SIZE && curCol >= 0 && curCol < BOARD_SIZE && a.get_data(curRow, curCol) == 1)
                        {
                            playernum++;
                        }
                        else if (curRow >= 0 && curRow < BOARD_SIZE && curCol >= 0 && curCol < BOARD_SIZE && a.get_data(curRow, curCol) == 0)
                        {
                            emptynum++;
                            break;
                        }
                        else
                            break;
                    }
                    if (playernum == 1)
                    {
                        scoreMap[row][col] += 10;
                    }
                    else if (playernum == 2)
                    {
                        if (emptynum == 1)
                        {
                            scoreMap[row][col] += 30;
                        }
                        else if (emptynum == 2)
                        {
                            scoreMap[row][col] += 40;
                        }
                    }
                    else if (playernum == 3)
                    {
                        if (emptynum == 1)
                        {
                            scoreMap[row][col] += 60;
                        }
                        else if (emptynum == 2) {
                            scoreMap[row][col] += 5000;
                        }
                    }
                    else if (playernum == 4) {
                        scoreMap[row][col] += 20000;
                    }
                    emptynum = 0;
                    for (int i = 1; i <= 4; i++)
                    {
                        int curRow = row + i * y;
                        int curCol = col + i * x;

                        if (curRow >= 0 && curRow < BOARD_SIZE && curCol >= 0 && curCol < BOARD_SIZE && a.get_data(curRow, curCol) == -1)
                        {
                            ainum++;
                        }
                        else if (curRow >= 0 && curRow < BOARD_SIZE && curCol >= 0 && curCol < BOARD_SIZE && a.get_data(curRow, curCol) == 0)
                        {
                            emptynum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }

                    for (int i = 1; i <= 4; i++) 
                    {
                        int curRow = row - i * y;
                        int curCol = col - i * x;

                        if (curRow >= 0 && curRow < BOARD_SIZE && curCol >= 0 && curCol < BOARD_SIZE && a.get_data(curRow, curCol) == -1)
                        {
                            ainum++;
                        }

                        else if (curRow >= 0 && curRow < BOARD_SIZE && curCol >= 0 && curCol < BOARD_SIZE && a.get_data(curRow, curCol) == 0)
                        {
                            emptynum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }

                    if (ainum == 0)
                    {
                        scoreMap[row][col] += 5;
                    }
                    else if (ainum == 1)
                    {
                        scoreMap[row][col] += 10;
                    }
                    else if (ainum == 2)
                    {
                        if (emptynum == 1)
                        {
                            scoreMap[row][col] += 25;
                        }
                        else if (emptynum == 2)
                        {
                            scoreMap[row][col] += 50;
                        }
                    }
                    else if (ainum == 3)
                    {
                        if (emptynum == 1)
                        {
                            scoreMap[row][col] += 55;
                        }
                        else if (emptynum == 2)
                        {
                            scoreMap[row][col] += 10000;
                        }
                    }
                    else if (ainum >= 4)
                    {
                        scoreMap[row][col] += 30000;
                    }
                }
            }
        }
    }
    int MAX = 0;
    vector<ai> maxPoints;
    int ROW = 0, COL = 0;
    ai AK47;
    AK47.x = 0;
    AK47.y = 0;
    for (ROW = 0;ROW < BOARD_SIZE;ROW++)
    {
        for (COL = 0;COL < BOARD_SIZE;COL++)
        {
            if (a.get_data(ROW, COL) == 0)
            {
                if (scoreMap[ROW][COL] > MAX)
                {
                    MAX = scoreMap[ROW][COL];
                    maxPoints.clear();
                    AK47.x = ROW;
                    AK47.y = COL;
                    maxPoints.push_back(AK47);
                }
                else if (scoreMap[ROW][COL] == MAX)
                {
                    AK47.x = ROW;
                    AK47.y = COL;
                    maxPoints.push_back(AK47);
                }
            }
        }
    }
    int index = rand() % maxPoints.size();
    return maxPoints[index];
}
class Game
{
public:
    void rule()
    {
        cout <<"1 人机对抗，玩家默认为黑棋先手\n";
        cout << "2 双人对抗，在下棋前可选择黑白棋谁先先手。\n";
        cout << "A对应10,B对应11，以此类推。\n";
        cout << "游戏规则：本游戏无禁手规则，黑白双方依次落子，由黑先下，当棋盘上有三个子时(两黑一白),\n"
             <<"如果此时白方觉得开的局不利于自已可以提出交换, 黑方无条件接受!也可以不交换, 主动权在白方!\n"
             <<"然后继续下棋, 任一方先在棋盘上形成横向、竖向、斜向的连续的相同颜色的五个(含五个以上)棋子的一方为胜。\n";
        system("pause");
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
        if (choose != 1 && choose != 2 && choose != 3 && choose != 0)
        {
            cout << "请重新输入!\n";
            goto begin;
        }
        else
        {
            if (choose == 1)
            {
                return 1;
            }
            else if (choose == 2)
            {
                return 3;
            }
            else if (choose == 3)
            {
                rule();
                goto begin;
            }
            else if (choose == 0)
            {
                color(0x0C);
                cout << "制作人：";
                color(0x0E);
                cout << "陈瑞泽\n\a";
                color(7);
                Sleep(1500);
                exit;
            }
        }
    }
    void menu2(Game& game,Board table,player &A,player& B,ComputerPlayer&AI)
    {
        begin:
        int a = game.Choose();
        if (a == 3)
        {
        AGAIN:
            int x, y;
            char temp1;
            char temp2;
            int i = 0;
            table.draw();
            while (1) {
                bool flag = true;
                bool WIN = false;
                while (flag)
                {
                    cout << "请黑棋玩家输入落子位置\n";
                    cin >> temp1 >> temp2;
                    fflush(stdin);
                    if (temp1 >= 49 && temp1 <= 57 || temp1 >= 65 && temp1 <= 70)
                    {
                        if (temp1 >= 49 && temp1 <= 57)
                            x = (int)temp1 - 48;
                        if (temp1 >= 65 && temp1 <= 70)
                            x = (int)temp1 - 55;
                    }
                    else
                        x = (int)temp1;
                    if (temp2 >= 49 && temp2 <= 57 || temp2 >= 65 && temp2 <= 70)
                    {
                        if (temp2 >= 49 && temp2 <= 57)
                            y = (int)temp2 - 48;
                        if (temp2 >= 65 && temp2 <= 70)
                            y = (int)temp2 - 55;
                    }
                    else
                        y = (int)temp2;
                    flag = A.isVaild(x, y, table);
                    table.draw();
                }
                if (table.isWin_black(x, y))
                {
                    A.display_WIN();
                    WIN = true;
                    flag = false;
                }
                else
                    flag = true;
                while (flag)
                {
                    cout << "请白棋玩家输入落子位置\n";
                    
                    cin >> temp1 >> temp2;
                    fflush(stdin);
                    if (temp1 >= 49 && temp1 <= 57 || temp1 >= 65 && temp1 <= 70)
                    {
                        if (temp1 >= 49 && temp1 <= 57)
                            x = (int)temp1 - 48;
                        if (temp1 >= 65 && temp1 <= 70)
                            x = (int)temp1 - 55;
                    }
                    else
                        x = (int)temp1;
                    if (temp2 >= 49 && temp2 <= 57 || temp2 >= 65 && temp2 <= 70)
                    {
                        if (temp2 >= 49 && temp2 <= 57)
                            y = (int)temp2 - 48;
                        if (temp2 >= 65 && temp2 <= 70)
                            y = (int)temp2 - 55;
                    }
                    else
                        y = (int)temp2;
                    flag = B.isVaild(x, y, table);
                    table.draw();
                    if (table.isWin_white(x, y))
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
                score[0] = 0;
                score[1] = 0;
                goto begin;
            }
        }
        else if (a == 1)
        {
            while (1)
            {

                char arr[5];
                ai data;
                char temp1;
                char temp2;
                int x, y, X, Y;
                table.draw();
                while (1)
                {
                    while (1)
                    {
                        cout << "请玩家落子!\n" << endl;
                        cin >> temp1 >> temp2;
                        fflush(stdin);
                        if (temp1 >= 49 && temp1 <= 57 || temp1 >= 65 && temp1 <= 70)
                        {
                            if (temp1 >= 49 && temp1 <= 57)
                                x = (int)temp1 - 48;
                            if (temp1 >= 65 && temp1 <= 70)
                                x = (int)temp1 - 55;
                        }
                        else
                            x = (int)temp1;
                        if (temp2 >= 49 && temp2 <= 57 || temp2 >= 65 && temp2 <= 70)
                        {
                            if (temp2 >= 49 && temp2 <= 57)
                                y = (int)temp2 - 48;
                            if (temp2 >= 65 && temp2 <= 70)
                                y = (int)temp2 - 55;
                        }
                        else
                            y = (int)temp2;
                        
                        if (A.isVaild(x, y, table))
                        {
                            ;
                        }
                        else break;
                    }
                    if (table.isWin_black(x, y))
                    {
                        A.display_AI_WIN();
                        break;
                    }
                    table.draw();
                    data = AI.AICalculate(table);
                    X = data.x + 1;
                    Y = data.y + 1;
                    puts("电脑正在思考......\n");
                    Sleep(rand() % 2500);
                    table.putWhite(X, Y);
                    table.draw();
                    if (table.isWin_white(X, Y))
                    {
                        score[3]++;
                        cout << "电脑获得胜利!\n\a";
                        break;
                    }
                }
                cout << "当前比分：玩家" << score[2] << "  " << "电脑" << score[3] << endl;
                cout << "是否想再玩一把？(Y/N)" << endl;
                cin >> arr;
                if (strcmp(arr, arrY) == 0 || strcmp(arr, arry) == 0)
                {
                    table.clean();
                    system("cls");
                }
                    
                else
                {
                    table.clean();
                    system("cls");
                    score[3] = 0;
                    score[2] = 0;
                    goto begin;
                }
                    

            }
        }
    }
};
void menu()
{
    cout << "######################################\n";
    cout << "###########欢迎来到五子棋！###########\n";
    cout << "######################################\n\a";
    Sleep(1500);
    system("cls");
}

int main()
{
    srand(time(NULL));
    Board table;
    player A('X');
    player B('O');
    ComputerPlayer AI;
    Game game;
    menu();
    game.menu2(game, table, A, B,AI);
}









