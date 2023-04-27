#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>						// used to seed the random number generator
#define e 2.7182818284
using namespace std;
//
//***********************************************************************

void Center_Text(char ShellText[80])
//**********************************************************************
//*Void Center_Text:	Displays text centered on the screen.
//*	
//*	expects:			The text to display.			
//*	Returns:			None.
//*	Side effects:		Outputs Centered text on screen.		
//*
//*******************************************************************
{
	int length;
	int center;
	length = strlen(ShellText);
	center = (80 - length) / 2;
	for (; center != 0; center--)
	{
		_cputs(" ");
	}
	_cputs(ShellText);
}
void Center_Text(const char ShellText[80])
//**********************************************************************
//*Void Center_Text:	Displays text centered on the screen.
//*	
//*	expects:			The text to display.			
//*	Returns:			None.
//*	Side effects:		Outputs Centered text on screen.		
//*
//*******************************************************************
{
	int length;
	int center;
	length = strlen(ShellText);
	center = (80 - length) / 2;
	for (; center != 0; center--)
	{
		_cputs(" ");
	}
	_cputs(ShellText);
}
void Program_Init()
//*************************************************************************
//*	void Program_Init():Shows Title
//*	 
//*	expects			None
//*	returns:			None
//*	Side Effects:		Text is centered on screen
//*
//*	Task(s)			Output program information to screen.
//*
//***********************************************************************
{
	Center_Text("Lab #5");
	cout << endl;
	Center_Text("A Deck Driver");
	cout << endl << "\n";
	Center_Text("By Frank Vokoun");
	cout << endl << "\n";
	Center_Text("(C) 2001, Frank Vokoun");
	cout << endl << "\n";
	Center_Text("Hit the <Return> key to Continue..");
	cin.get();
}

char Get_Key()
//***********************************************************************
//*	char Get_Key():		Uses a input prompt to get a char
//*	 
//*	expects:			None.
//*	Returns:			Input char.
//*	Side effects:		Pauses Program execution (desired effect).
//*	
//*	Task(s):			Gets a char from the user..
//*
//**********************************************************************
{
	char x;
	x = cin.get();
	cout << endl;
	return x;
}



int get_number()
//********************************************************************
//*
//*	int get_number:		Gets an integer from the user.
//*	expects:			None.			
//*	Returns:			Integer.
//*	Side effects:		None.		
//*	Task(s):			Asks the user to enter an integer then returns that integer.
//*							.		
//**********************************************************************
{
	int Input_Integer = 0;
	Center_Text("Please enter an integer between 0 and 51. 52 to quit.");
	cout << endl;
	cin >> Input_Integer;
	return Input_Integer;
}


int getRandInt(int min, int max)
//*********************************************************************
//*int GetRandInt:		Returns a random number between min and max
//*
//* BORROWED FUNCTION:Used with permission from Prof. Steve Samuelson. 
//*	
//*	Expects:			min -- smallest possible number to return
//*					max -- largest possible number to return
//* Returns:			A number between min and max
//* Side Effects:		     None
//*
//* Tasks:				1. set a num = to random number generator.
//*						2. make num = num % (max - min +1); add min.
//*						3. Return the num
//*******************************************************************
{
	int numToReturn;
	numToReturn = rand();
	numToReturn = numToReturn % (max - min + 1) + min;
	return numToReturn;
}

void prog_close()
//*******************************************************************
//*	void prog_close:	Waits for user input to end
//*	Inputs:				None			
//*	Returns:			None
//*	Side effects:		Output text to screen/waits for user input to 		
//*						end program.
//*
//*	task(s)			1. Pauses Program so the last output can be seen
//*			
//***********************************************************************
{
	cout << endl << endl;
	cout << " Hit the <Return> key to Continue.." << endl;
	cout << endl << endl;
	Get_Key();							// Necesary for clear input.		
	cin.get();
}

class Playing_Card    //扑克类
{
private:
	int m_Value;
	char m_Face[3];  //扑克的数字大小
	char m_Suit;    //扑克的花色（黑、红、梅、方）
public:
	Playing_Card()								// CONSTRUCTOR
	{
		int i;
		for (i = 1; i <= 3;)					// inits string variable to blanks
		{
			m_Face[i] = ' ';
			i++;
		}
		m_Suit = ' ';					// inits char variable to blank
		m_Value = 0;
	}
	void showcard()							// Displays an object of class Playing_Card
	{
		cout << "   ";
		cout << m_Face;
		cout.width(1);
		cout << m_Suit;
		cout << " ";

	}
	void Card_Make(int num)
	{

		int i = 0;
		char j;
		if (num == 52) { 
			strcpy(m_Face, " S");
			m_Suit = 32; 
			m_Value = 15; 
			return;
		}

		if (num == 53) { 
			strcpy(m_Face, " B");
			m_Suit = 32; 
			m_Value = 16; 
			return;
		}
		int face_num = num % 13;

		switch (face_num)						// Assigns a Face value for string cards
		{
		case 0: strcpy(m_Face, " A"); break;
		case 9: strcpy(m_Face, "10"); break;
		case 10: strcpy(m_Face, " J"); break;
		case 11: strcpy(m_Face, " Q"); break;
		case 12: strcpy(m_Face, " K"); break;
		default:
			j = char(face_num + 49);			// Fills string with number mod 13

			if (i < 3)
			{
				m_Face[i] = ' '; i++;
				m_Face[i] = j; i++;
				m_Face[i] = NULL;
				break;
			}
		}

		if (num <= 12)m_Suit = 6;				// assigns suit use ascii values for
		if (num > 12 && num <= 25)m_Suit = 3;	//		card symbols
		if (num > 25 && num <= 38)m_Suit = 5;
		if (num > 38 && num <= 51)m_Suit = 4;

		if (face_num <= 13)m_Value = face_num + 1;		// Card value's Ace = 1

	}
	
	
	char get_m_Suit()
	{
		return m_Suit;
	}
	char* get_m_Face()
	{
		return m_Face;
	}
	int get_m_Value()
	{
		return m_Value;
	}
};

class Deck	//一副扑克（52张）										
{
private:
	Playing_Card m_cardarray[54];				// Object array of class Playing_Card
	int m_lastdelt;
public:
	Deck()							// CONSTRUCTOR initializes empty Deck object
	{
		int lastdelt = 0;
		int i;
		for (i = 0; i <= 53; i++)
		{
			m_cardarray[1] = Playing_Card();	     // calls constructor class Playing_Card				
		}								// for every Playing_Card object in 
	}									// the class Deck's array.

	void MakeDeck()					// makes a complete object of class Deck
	{
		m_lastdelt = 53;								// Set Deck to empty
		while (m_lastdelt > -1)							// iterate until deck is full. 
		{
			m_cardarray[m_lastdelt].Card_Make(m_lastdelt);  // call card make for every card object
			m_lastdelt--;							// inside the deck object ie cardarray				 
		}
	}
	void Deal_One()						// Deals a card from top of the deck
	{
		if (m_lastdelt != 53)						// Checks for available cards
		{
			m_lastdelt++;
			cout.width(5);
			cout << "    Card delt";
			m_cardarray[m_lastdelt].showcard();
		}
		else
		{
			cout << "Out of range Error";
			prog_close();
		}
	}
	void ShowDeck()						// Displays a Deck object to the  screen
	{
		int index = m_lastdelt + 1;
		int newline = 0;
		Center_Text("Current Deck of Cards from top to bottom");
		cout << endl;
		while (index <= 53)
		{
			if (newline % 11 == 0) cout << endl;
			m_cardarray[index].showcard();				// calls showcard for every card in 
			newline++;								// the cardarray object
			index++;
		}
		cout << endl;
	}
	void DeckShuff(int times)					// "Shuffles" a Deck object for int times
	{
		int x, split;   //split是分开成两部分的位置，如上部分、下部分
		Center_Text("Shuffling Deck");
		cout << endl;
		for (x = 0; x <= times; x++)							// iterate input number of times
		{
			split = getRandInt(20, 35);					// Get split location
			Deck topdeck;								// Create 2 new unfilled decks
			Deck bottomdeck;
			int i;
			int bottomdeckindex = 1;
			int topdeckindex = 1;
			for (i = 0; i <= split - 1;)
			{
				topdeck.m_cardarray[topdeckindex] = this->m_cardarray[i];
				topdeckindex++;
				i++;
			}
			for (i = (split); i < 54;)					// move remaining cards to bottom deck
			{
				bottomdeck.m_cardarray[bottomdeckindex] = this->m_cardarray[i];
				bottomdeckindex++;
				i++;
			}
			int deckoutindex = 0;				// set deck to fill's index to zero
			int numcardstomovetop;
			int numcardstomovebottom;
			int j;
			int h = 0;
			bottomdeckindex = 54 - split;		// set index to num cards in bottom
			topdeckindex = split;				// set index to num cards in top
			while (deckoutindex <= 53)
			{
				numcardstomovetop = getRandInt(2, 7);
				//从上部分抽取的张数，是2-7之间的随机数
				numcardstomovebottom = getRandInt(2, 7);
				// Move a random number of cards(2-7)  
				for (j = 0; j <= numcardstomovebottom; j++)	//	from bottomdeck to original deck	
				{
					if (bottomdeckindex > 0)				// check for available cards
					{
						this->m_cardarray[deckoutindex] = bottomdeck.m_cardarray[bottomdeckindex];
						deckoutindex++;
						bottomdeckindex--;
					}
					for (h = 0; h <= numcardstomovetop; h++)
						// Move a random number of cards (2 to 7) 
					{			//		from topdeck to original deck.	
						if ((topdeckindex > 0) && (deckoutindex <= 54))
							// check for available cards 
						{			//		and slots	
							this->m_cardarray[deckoutindex] = topdeck.m_cardarray[topdeckindex];
							deckoutindex++;
							topdeckindex--;
						}
					}
				}
			}
		}
		this->m_lastdelt = -1;					// Return a complete shuffled deck
	}
	void Remove_Card() 				// Removes used card from Deck Prevents 
	{
		m_cardarray[m_lastdelt] = Playing_Card();	// reinits used card prevents mistakes		
	}
	void Deck_sort_by_value()
	{
		for (int i = m_lastdelt+1; i < 53; i++)
		{
			for (int j = 53-1; j >=i ; j--)
			{
				if (m_cardarray[j].get_m_Value() > m_cardarray[j + 1].get_m_Value())
				{
					Playing_Card temp = m_cardarray[j];
					m_cardarray[j] = m_cardarray[j + 1];
					m_cardarray[j + 1] = temp;
				}
			}
		}
	}
	void Deck_sort_by_suit()
	{
		for (int i = m_lastdelt + 1; i < 53; i++)
		{
			for (int j = 53 - 1; j >= i; j--)
			{
				if (m_cardarray[j].get_m_Suit() > m_cardarray[j + 1].get_m_Suit())
				{
					Playing_Card temp = m_cardarray[j];
					m_cardarray[j] = m_cardarray[j + 1];
					m_cardarray[j + 1] = temp;
				}
			}
		}
	}
	Playing_Card* get_m_cardarray()
	{
		return m_cardarray;
	}
	int get_m_lastdelt()
	{
		return m_lastdelt;
	}
};										//		mistakenly using a nonexistant card
										//		can bu used to send a card ??


void DeckMakeDriver()
//********************************************************************
//* DeckMakeDriver():	Used to test the various deck functions Deckmake,
//*						Deckshuff, Deckcopy etc.
//*	Expects:			None.
//* Returns:			None.
//* Side effects:		     None 
//*
//* Tasks:			    	1. Call make Deck 
//*					2. Show Deck 
//*					3. Call shuffle 
//*					4. Call show deck 
//*					5. While !Done Call 
//*						a. Deal one 
//*						b. Show card 
//*			
//*Note the dot operator is need to access object because this is not a member of the class
//**********************************************************************
{
	Deck deck_1;
	deck_1.MakeDeck();					// Creates the Deck.
	deck_1.ShowDeck();					// Displays deck to screen.
	Get_Key();							// Pauses Program.
	deck_1.DeckShuff(250);					// Shuffles the deck 250 times
	deck_1.ShowDeck();					// Displays deck to screen.
	cout << endl << endl << endl;
	char y;
	do
	{
		deck_1.Deal_One();
		cout << endl;
		cout << endl << endl << "Y to Deal One more N to quit" << endl;
		cin >> y;
		y = toupper(y);
	} while (y == 'Y');
}
class PlayDeck
{
private:
	Deck deck;
	PerDeck play_arr[4];
public:
	PlayDeck() {};
	PlayDeck(Deck& d)
	{
		deck = d;
		for (int i = 0; i < 4; i++)
		{
			play_arr[i] = PerDeck(i);
		}
	}
	void send_cards()
	{
		for (int i = 0; i < 54; i++)
		{
			play_arr[i % 4].add_card(deck.get_m_cardarray()[i]);
		}
		cout << "OK!" << endl;
	}
	void del_cards()
	{
		for (int i = 0; i < 4; i++)
		{
			play_arr[i].del_last_card();
		}
	}
	void Show_per()
	{
		for (int i = 0; i < 4; i++)
		{
			play_arr[i].Show_deck();
		}
	}
	void del_player_card(int name)
	{
		play_arr[name].del_last_card();
	}
	void sort_by_value()
	{
		for (int i = 0; i < 4; i++)
		{
			play_arr[i].Deck_sort_by_value();
		}
	}
	void sort_by_suit()
	{
		for (int i = 0; i < 4; i++)
		{
			play_arr[i].Deck_sort_by_suit();
		}
	}
	PerDeck* get_player_arr()
	{
		return play_arr;
	}
};
class PerDeck
{
private:
	Playing_Card m_cardarray[14];
	int index;
	int name_n;
public:
	PerDeck() {};
	PerDeck(int name)
	{
		name_n = name;
		index = -1;
	}
	void add_card(Playing_Card& card)
	{
		index++;
		m_cardarray[index] = card;

	}
	void del_last_card()
	{
		index--;
	}
	void Deck_sort_by_value()
	{
		for (int i = 0; i < index; i++)
		{
			for (int j = index - 1; j >= i; j--)
			{
				if (m_cardarray[j].get_m_Value() > m_cardarray[j + 1].get_m_Value())
				{
					Playing_Card temp = m_cardarray[j];
					m_cardarray[j] = m_cardarray[j + 1];
					m_cardarray[j + 1] = temp;
				}
			}
		}
	}
	void Deck_sort_by_suit()
	{
		for (int i = 0; i < index; i++)
		{
			for (int j = index - 1; j >= i; j--)
			{
				if (m_cardarray[j].get_m_Suit() > m_cardarray[j + 1].get_m_Suit())
				{
					Playing_Card temp = m_cardarray[j];
					m_cardarray[j] = m_cardarray[j + 1];
					m_cardarray[j + 1] = temp;
				}
			}
		}
	}
	void Show_deck()
	{
		int ind = 0;
		int newline = 0;
		cout << "player " << name_n + 1 << " cards" << endl;
		while (ind <= index)
		{
			if (newline % 11 == 0) cout << endl;
			get_m_cardarray()[ind].showcard();				// calls showcard for every card in 
			newline++;								// the cardarray object
			ind++;
		}
		cout << endl;
		//cout << endl;
	}
	Playing_Card* get_m_cardarray()
	{
		return m_cardarray;
	}
	int Get_index()
	{
		return index;
	}
	int get_name_n()
	{
		return name_n;
	}
};

void menu()
{
	Deck d1;
	d1.MakeDeck();
	d1.ShowDeck();
	PlayDeck p(d1);
	p.send_cards();
	while (e)
	{
		cout << "请选择一个操作：      " << endl;
		cout << "1. 删除一张     " << endl;
		cout << "2. 删除一轮      " << endl;
		cout << "3. 按点数排序     " << endl;
		cout << "4. 按花色排序    " << endl;
		cout << "5. 显示所有玩家牌    " << endl;
		cout << "6. 退出    " << endl;
		int num = 0;
		cout << "输入选项：" << endl;
		cin >> num;
		switch (num)
		{
		case 1:
		{
			int a = 0;
			cout << "输入玩家编号：" << endl;
			cin >> a;
			p.del_player_card(a - 1);
			cout << "删除成功" << endl;
			break;
		}
		case 2:
		{
			p.del_cards();
			cout << "删除成功全部玩家一张牌" << endl;
			break;
		}
		case 3:
		{
			cout << "按照点数排序：" << endl;
			for (int i = 0; i < 4; i++)
			{
				p.get_player_arr()[i].Deck_sort_by_value();
				p.Show_per();
			}
			break;
		}
		case 4:
		{
			cout << "按照点数排序：" << endl;
			for (int i = 0; i < 4; i++)
			{
				p.get_player_arr()[i].Deck_sort_by_suit();
				p.Show_per();
			}
			break;
		}
		case 5:
		{
			p.Show_per();
			break;
		}
		case 6:
		{
			exit();
		}
		}
	}
	

}

int main(int argc, char** argv)
{
	menu();
}