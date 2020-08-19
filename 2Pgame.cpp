#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

using namespace std;


class Nuker {
	public:
		string Name = "Nuker";
		int HP = 700;
		int MANA = 300;
		vector<string> moves = {"Attack","Lethal Blow","Shield"};
		vector<int> manaCost = {0,150,0};

		void attack(auto &obj){
			obj.HP -= 20;
		}

		void specialMove(auto &obj){
			obj.HP -= 100;
			MANA -= 150;
		}

		void defend(){
			if(HP < 685)
				HP += 15;
			else if(HP > 645 && HP < 700)
				HP = 700;
		}

		void roundStats(){
			if(MANA < 290)
				MANA += 10;
			else if(MANA >= 290 && MANA < 300)
				MANA = 300;
		}	
};

class Mage {
	public:
		string Name = "Mage";
		int HP = 500;
		int MANA = 500;
		vector<string> moves = {"Orbs","Thunder Strike","Heal"};
		vector<int> manaCost = {0,150,50};

		void attack(auto &obj){
			obj.HP -= 30;
		}	

		void specialMove(auto &obj){
			obj.HP -= 120;
			MANA -= 130;
		}

		void defend(){
			if(HP < 470)
				HP += 30;
			else if(HP > 470 && HP < 500)
				HP = 500;
			MANA -= 50;
		}

		void roundStats(){
			if(MANA < 475)
				MANA += 25;
			else if(MANA >= 475 && MANA < 500)
				MANA = 500;
		}		
};

void game(auto Player, auto Computer);

int main() 
{	srand(time(0));
	cout << "Welcome Player" << endl;
	sleep(2);
	cout << "Are you ready for the toss?" << endl;

	int wait = 5;
	while(wait--)
	{
		cout << ".";
		sleep(1);
	}

	int toss = rand()%2;
	
	if(toss == 1)
	{
		cout << "You are Nuker!" << endl;
		Nuker Player;
		Mage Computer;
		game(Player,Computer);
	}
	else
	{
		cout << "You are Mage!" << endl;
		Mage Player;
		Nuker Computer;
		game(Player,Computer);
	}
}

void displayStats(auto &obj)
{
	if(obj.HP >= 0)
		cout << "\n" << obj.Name << "\nHP: " << obj.HP << "\nMANA: " << obj.MANA << endl;
	else
		cout << "\n" << obj.Name << "\nHP: 0"<< "\nMANA: " << obj.MANA << endl;
}

void gameStats(auto &obj1,auto &obj2)
{
	obj1.roundStats();
	obj2.roundStats();
	displayStats(obj1);
	displayStats(obj2);
	cout << "\n\n" << endl;
}

void gameComp(auto &obj, auto &obj2)
{
	int action = 0;
	int counter;
	while(counter != -1)
	{
		action = (rand()%3) + 1;
		counter = 1;
		switch(action) {
			case 1:
			{
				obj.attack(obj2);
				counter = -1;
				break;
			}
			case 2:
			{
				if((obj.MANA - obj.manaCost[(action-1)]) >= 0 && counter != 0)
				{
					obj.specialMove(obj2);
					counter = -1;
					break;
				}
				else if(counter != 0)
				{
					counter = 0;
				}
			}
			case 3:
			{
				if(obj.MANA - obj.manaCost[(action-1)] >= 0 && counter != 0)
				{
					obj.defend();
					counter = -1;
					break;
				}
				else if(counter != 0)
				{
					counter = 0;
				}
			}
		}
	}
	cout << "\n" << obj.Name << " used " << obj.moves[action-1] << "\n" << endl;
}

void game(auto Player, auto Computer)
{
	cout << "\n\nWelcome " << Player.Name << "\nHP: " << Player.HP << "\nMANA: " << Player.MANA << endl;
	while(Player.HP > 0 && Computer.HP > 0)
	{
		for (int i = 0; i < Player.moves.size(); i++)
			cout << i+1 << "> " << Player.moves[i] << endl;
		cout << "Choose an action: " << endl;
		int action = 0;
		int counter = 0;
		while(counter != -1)
		{
			counter = 1;
			cin >> action;
			switch(action) {
				case 1:
				{
					Player.attack(Computer);
					counter = -1;
					break;
				}
				case 2:
				{
					if((Player.MANA - Player.manaCost[(action-1)]) >= 0 && counter != 0)
					{
						Player.specialMove(Computer);
						counter = -1;
						break;
					}
					else if(counter != 0)
					{
						counter = 0;
						cout << "Not enough MANA" << endl;
					}
				}
				case 3:
				{
					if(Player.MANA - Player.manaCost[(action-1)] >= 0 && counter != 0)
					{
						Player.defend();
						counter = -1;
						break;
					}
					else if(counter != 0)
					{
						counter = 0;
						cout << "Not enough MANA" << endl;
					}
				}
				default: 
				{
					cout << "Please choose an action from the menu: " << endl;
				}
			}
		}
		gameComp(Computer,Player);
		gameStats(Player,Computer);
	}
	if(Player.HP < 0)
		cout << "Delegate of Ireland Lost";
	else
		cout << "You win...idk how";
}
