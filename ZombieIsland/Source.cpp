#include <iostream>						//All Libraries for the code to function
#include <cstdlib>
#include <time.h>
#include "func.h"
#include "console.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>


using namespace std;

int main()
{
	int userHeightAndWidth = 0;						//Interger for user to decide how wide and tall the island to be
	int userIsland = 0;								//Used to say how big the island will be
	int userDirection = 0;							//Input for the human's direction
	int verificationForDirection = 0;				//Input to check whether the human can make a valid move
	const int totalNoOfZombies = 4;					//Constant interger to decide total number of zombies
	const int totalNoOfHoles = 6;					//Constant interget to decide total number of holes
	srand(time(NULL));								//Seeds random
	Human player1;									//Initialises a class for one player
	Zombie zombieAI[totalNoOfZombies];				//Initialises an Array, with a number of elements equal to the number of zombies
	Hole holeAI[totalNoOfHoles];					//Same as the zombie array, but for holes instead.

	Console::setWindowTitle("Zombie Island");		//Sets the window title

	cout << "You are a man, and you are stuck on an island, which is populated with zombies!" << endl;							//Intro to the program
	cout << "On your island, there are multiple holes to help trap these zombies." << endl;
	cout << "Your aim is to try and lure these zombies into these holes. If all the zombies are trapped, you win!" << endl;
	cout << "However, if you fall into a hole, or a zombie manages to catch you, you lose.\n" << endl;
	cout << "Before we start, you can decide how large the island will be, both in terms of height and width." << endl;
	cout << "So, how large do you want to have the island be? Smallest size is 5 units." << endl;

	cin >> userHeightAndWidth;						//User input for the Width and Height for the island.

	while (userHeightAndWidth <= 4)					//Check to make sure the user is inputting a value that is 1 or larger
	{
		cout << "You cannot have an island that is that small. Input a larger number." << endl;
		cin >> userHeightAndWidth;
	}
	userIsland = userHeightAndWidth * userHeightAndWidth;	//Sets the Size of the island

	vector<int> theIsland(userIsland,0);					//Initialises a vector with elements equal to the size of the island, and all start at the value 0
	
	player1.setLocation(userIsland, theIsland);				//Places the player down in a random place on the island.
	for (int count = 0; count < totalNoOfZombies; count++)	//A for loop that goes through every zombie in the array, and places them on the island randomly
	{
		zombieAI[count].setLocation(userIsland, theIsland);
	}
	for (int count = 0; count < totalNoOfHoles; count++)	//Same as the Zombie loop, but for holes
	{
		holeAI[count].setLocation(userIsland, theIsland);
	}
	drawIsland(theIsland);									//Function that is used to draw the island out

	cout << "\n\nThe island has been initialised. Time to play!" << endl;
	system("pause");										//Game is ready to play, waits for user input
	Console::clear();										//Clears the Console
	
	int currentNoOfZombies = totalNoOfZombies;				//An interger used to track how many zombies are "Alive"
	int humanAlive = 2;										//An interger used to track if the player is alive, and how they die.

	while (currentNoOfZombies > 0 && humanAlive == 2)		//Whilst the human is alive and there is at least 1 zombie not in a hole
	{
		drawIsland(theIsland);
		cout << "It is your turn to move. 8 to move up, 6 is right, 4 is left, and 2 is down." << endl;
		cout << "If you want to stay still, use 5." << endl;	//Ask for the user's direction
		cin >> verificationForDirection;						
		checkInput(verificationForDirection, userDirection);	//Function to ensure the input is correct
		while (verificationForDirection == 0)					//If not, try again.
		{
			cin >> verificationForDirection;
			checkInput(verificationForDirection, userDirection);
		}
		player1.moveCharacter(userDirection, userHeightAndWidth, userIsland, humanAlive, theIsland);	//Move the player character accordingly. Also check to see if has come into contact with zombie or hole
		Console::clear();										//clear console
		drawIsland(theIsland);									//Draw the Island again
		system("pause");										//Wait for user input
		Console::clear();										//and clear again
		for (int count = 0; count < totalNoOfZombies; count++)		//For loop to have every zombie do the same action
		{
			cout << "It is Zombie No." << count + 1 << "'s turn to move." << endl;		//Say which zombie is moving
			zombieAI[count].moveRandomly(userHeightAndWidth, userIsland,currentNoOfZombies, humanAlive, theIsland);		//Move each zombie that is in the array.
			drawIsland(theIsland);		//Draw the island
			system("pause");			//Wait for user input
			Console::clear();			//Clear the console
		}	// If all the zombies have fallen into a hole, or the human player has "died", leave the loop. otherwise, go back to the players turn
	}
	if (currentNoOfZombies == 0)
	{
		cout << "Congratulations! All of the zombies have been trapped in holes. YOU WIN!" << endl;	//If the Zombies are all in holes, the player wins.
		system("pause");		//Wait for user input
		return 0;				//End the program
	}

	else if (humanAlive == 0)
	{
		cout << "Unfortunately, a zombie has managed to capture the Human. Try again next time!" << endl;	//If a zombie has captured the human, the player loses.
		system("pause");		//Wait for user input
		return 0;				//End the program
	}
	else if (humanAlive == 1)
	{ 
		cout << "Unfortunately, The Human fell into a hole. Try again next time!" << endl;	//If the human has fallen into a hole, the player loses.
		system("pause");		//Wait for user input
		return 0;				//End the program
	}

} 