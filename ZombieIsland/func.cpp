#include "func.h"
#include <iostream>
#include <vector>

using namespace std;

void drawIsland(vector<int> &theIsland)					//Function to draw the island
{
	int tempStorage = 0;								//Interger for temp value storage
	int squareOfTemp = 0;								
	int currentLine = 0;								//Interger used to track the current line
	tempStorage = theIsland.size();						//Make temp value equal to the number of elements in the vector
	squareOfTemp = sqrt(tempStorage);					//Square root (value divided by itself) of island size
	for (int count = 0; count < tempStorage; count++)	//Peform a for loop, which repeats equal to the size of the island
	{
		currentLine = currentLine + 1;					//Add 1 to current value
		if (theIsland[count] == 0)						//If the current value in the vector is 0 (Nothing there)
		{
			cout << ".";								//Output a full stop
		}
		else if (theIsland[count] == 1)					//If the current value in the vector is 1 (Human is there)
		{
			cout << "H";								//Output a H
		}
		else if (theIsland[count] == 2)					//If the value is 2 (Zombie is there)
		{
			cout << "Z";								//Ouput a Z
		}
		else if (theIsland[count] == 3)					//If it's 3 (A hole is there)
		{
			cout << "O";								//Output an O. Not zero, the letter O
		}
		if (currentLine == squareOfTemp)				//If the current line is equal to the square root
		{
			cout << endl;								//Start a new line
			currentLine = 0;							//Then make the current line back to 0 again.
		}
	}
}

void checkInput(int &desiredInput, int &userInput)		//Function to ensure the user is inputting a correct direction
{
	if (desiredInput == 2)								//If user inputted 2 (down)
	{
		userInput = 2;									//Make the genuine input 2
	}
	else if (desiredInput == 4)							//If user inputted 4 (left)
	{
		userInput = 4;									//Make the genuine input 4
	}
	else if (desiredInput == 5)							//If user inputted 5(stay still)
	{
		userInput = 5;									//Make the genuine input 5
	}
	else if (desiredInput == 6)							//If user inputted 6(right)			
	{
		userInput = 6;									//Make the genuine input 6
	}
	else if (desiredInput == 8)							//If user inputted 8
	{
		userInput = 8;									//Make the genuine input 8
	}
	else												//Otherwise
	{
		cout << "You cannot move in that direction. Try again." << endl;	//Output an error message to the screen
		desiredInput = 0;								//Reset the desired input back to 0
	}
		
};

void Human::setLocation(int islandSize, vector<int> &theIsland)			//Function to place human randomly on the island
{
	int tempStorage = 0;												//Make a temp storage interger
	tempStorage = rand() % islandSize;									//Create a random value between 0 and the maximum size of the island
	currentLocation = tempStorage;										//Assign that value to currentLocation
	if (theIsland[currentLocation] == 0)								//If there isnt anything there,
	{
		theIsland[currentLocation] = 1;									//Place the human there
	}
	else if (theIsland[currentLocation] == 2 || theIsland[currentLocation] == 3)		//If a zombie or hole is there
	{
		while (theIsland[currentLocation] == 2 || theIsland[currentLocation] == 3)		//Whilst there is a zombie or hole there
		{
			tempStorage = rand() % islandSize;							//Create a random value between 0 and the maximum size of the island
			currentLocation = tempStorage;								//Assign that value to currentLocation
			if (theIsland[currentLocation] == 0)						//If there isnt anything there,
			{
				theIsland[currentLocation] = 1;							//Place the human there
			}
		}
	}
}

void Human::moveCharacter(int userInput, int islandWidth, int islandSize, int &humanAlive, vector<int> &theIsland)	//function to move the player
{
	if (userInput == 2)												//If the direction value is 2 after the verification
	{
		previousLocation = currentLocation;							//Make the previous location equal to the current island
		currentLocation = currentLocation + islandWidth;			//Current location has the island width added, moving the player down
		if (currentLocation > islandSize)							//If the move would place the player below the island
		{
			currentLocation = previousLocation;						//Dont move the player, and place them back where the player was before
		}
		if (theIsland[currentLocation] == 3)						//If the new position has a hole there
		{
			humanAlive = 1;											//Set a flag that the human has falled down a hole
			cout << "The Human has fallen down a hole!" << endl;	//Output a suitable message
		}
		else if (theIsland[currentLocation] == 2)					//If there was a zombie
		{
			humanAlive = 0;											//Set a flag that the human was captured
			cout << "A Zombie has captured the Human!" << endl;		//Output a suitable message
		}
		theIsland[previousLocation] = 0;							//The previous location value is now 0, so a "." is printed
		theIsland[currentLocation] = 1;								//The new location value is now 1, so a "H" is printed
	}
	else if (userInput == 4)										//The same happens if the user inputs a different direction.
	{																//The only changes that will happen is that the array position is updated,
																	//and the check to make sure the human isnt off the island
		{															//so left decreases the value by 1, right increases it by 1, and up decreases
			previousLocation = currentLocation;						//it equal to the island width value.
			currentLocation = currentLocation - 1;					//This applies to all of the directions.
			if (currentLocation < 0)								
			{
				currentLocation = previousLocation;
			}
			if (theIsland[currentLocation] == 3)
			{
				humanAlive = 1;
				cout << "The Human has fallen down a hole!" << endl;
			}
			else if (theIsland[currentLocation] == 2)
			{
				humanAlive = 0;
				cout << "A Zombie has captured the Human!" << endl;
			}
			theIsland[previousLocation] = 0;
			theIsland[currentLocation] = 1;
		}
	}
	else if ( userInput == 6)
	{
		previousLocation = currentLocation;
		currentLocation = currentLocation + 1;
		if (currentLocation > islandSize)
		{
			currentLocation = previousLocation;
		}
		if (theIsland[currentLocation] == 3)
		{
			humanAlive = 1;
			cout << "The Human has fallen down a hole!" << endl;
		}
		else if (theIsland[currentLocation] == 2)
		{
			humanAlive = 0;
			cout << "A Zombie has captured the Human!" << endl;
		}
		theIsland[previousLocation] = 0;
		theIsland[currentLocation] = 1;
	}
	else if (userInput == 8)
	{
		previousLocation = currentLocation;
		currentLocation = currentLocation - islandWidth;
		if (currentLocation < 0)
		{
			currentLocation = previousLocation;
		}
		if (theIsland[currentLocation] == 3)
		{
			humanAlive = 1;
			cout << "The Human has fallen down a hole!" << endl;
		}
		else if (theIsland[currentLocation] == 2)
		{
			humanAlive = 0;
			cout << "A Zombie has captured the Human!" << endl;
		}
		theIsland[previousLocation] = 0;
		theIsland[currentLocation] = 1;
	}

}

void Zombie::setLocation(int islandSize, vector<int> &theIsland)							//Function used to place the zombies
{
	{
		int tempStorage = 0;																//This function functions exactly the same as the human placing function
		tempStorage = rand() % islandSize;													//Stores a random value between 0 and the island size, then attempts to place it
		currentLocation = tempStorage;														//If the Human or a hole is there, and while there is either of them there
		if (theIsland[currentLocation] == 0)												//Reroll the random value, and attempt to place it down
		{																					//Otherwise, keep trying
			theIsland[currentLocation] = 2;
		}
		else if (theIsland[currentLocation] == 1 || theIsland[currentLocation] == 3)
		{
			while (theIsland[currentLocation] == 1 || theIsland[currentLocation] == 3)
			{
				tempStorage = rand() % islandSize;
				currentLocation = tempStorage;
				if (theIsland[currentLocation] == 0)
				{
					theIsland[currentLocation] = 2;
				}
			}
		}
	}
}

void Zombie::moveRandomly(int islandWidth, int islandSize ,int &currentNoOfZombies, int&humanAlive, vector<int> &theIsland) //Function to move the zombie
{
	int tempStorage = 0;												//Create a temp storage value													
	tempStorage = rand() % 100 + 1;										//Generate a random value between 1 and 100
	if (zombieAlive == 1)												//If the zombie alive flag is true, allow it to move
	{
		if (tempStorage <= 25)											//If the random value is 25 or lower
		{
			previousLocation = currentLocation;							//The moving and collision check is equal to that of the human's
			currentLocation = currentLocation + 1;						//it changes the previous and new location values, and make sure the zombie is still on the island
			if (currentLocation > islandSize)							//if it were to move off, set it back to the previous location
			{															//If the new location was to contain a hole or a zombie, output the correct message
				currentLocation =previousLocation;						//Then modify the value in the vector accordingly
			}
			if (theIsland[currentLocation] == 3)
			{
				zombieAlive = 0;
				cout << "A Zombie has fallen down a hole!" << endl;
				currentNoOfZombies = currentNoOfZombies - 1;
			}
			else if (theIsland[currentLocation] == 1)
			{
				humanAlive = 0;
				cout << "A Zombie has captured the Human!" << endl;
			}
			theIsland[previousLocation] = 0;
			theIsland[currentLocation] = 2;
		}
		else if (tempStorage > 25 && tempStorage <= 50)					//Same happens for the other random values
		{																//Here, this moves the zombie down if random is between 26 and 50
			previousLocation = currentLocation;
			currentLocation = currentLocation + islandWidth;
			if (currentLocation > islandSize)
			{
				currentLocation = previousLocation;
			}


			if (theIsland[currentLocation] == 3)
			{
				zombieAlive = 0;
				cout << "A Zombie has fallen down a hole!" << endl;
				currentNoOfZombies = currentNoOfZombies - 1;
			}
			else if (theIsland[currentLocation] == 1)
			{
				humanAlive = 0;
				cout << "A Zombie has captured the Human!" << endl;
			}
			theIsland[previousLocation] = 0;
			theIsland[currentLocation] = 2;
		}
		else if (tempStorage > 51 && tempStorage <= 75)					//Here, the zombie moves left if the random value is between 51 and 75
		{
			previousLocation = currentLocation;
			currentLocation = currentLocation - 1;
			if (currentLocation < 0)
			{
				currentLocation = previousLocation;
			}
			if (theIsland[currentLocation] == 3)
			{
				zombieAlive = 0;
				cout << "A Zombie has fallen down a hole!" << endl;
				currentNoOfZombies = currentNoOfZombies - 1;
			}
			else if (theIsland[currentLocation] == 1)
			{
				humanAlive = 0;
				cout << "A Zombie has captured the Human!" << endl;
			}
			theIsland[previousLocation] = 0;
			theIsland[currentLocation] = 2;
		}
		else if (tempStorage > 76)										//And if random is 76 or higher, the zombie moves up
		{
			previousLocation = currentLocation;
			currentLocation = currentLocation - islandWidth ;
			if (currentLocation < 0)
			{
				currentLocation = previousLocation;
			}
			if (theIsland[currentLocation] == 3)
			{
				zombieAlive = 0;
				cout << "A Zombie has fallen down a hole!" << endl;
				currentNoOfZombies = currentNoOfZombies - 1;
			}
			else if (theIsland[currentLocation] == 1)
			{
				humanAlive = 0;
				cout << "A Zombie has captured the Human!" << endl;
			}
			theIsland[previousLocation] = 0;
			theIsland[currentLocation] = 2;

		}
	}
	else
	{
		cout << "A Zombie Cannot Move!" << endl;

	}

}

void Hole::setLocation(int islandSize, vector<int>& theIsland)	//Function to place the holes
{
	{
		int tempStorage = 0;																//Again, this uses the same code as the zombie and human placement
		tempStorage = rand() % islandSize;													//Only difference is the if and while loop at the end,
		currentLocation = tempStorage;														//where if a zombie or human already exists there, reroll and try again
		if (theIsland[currentLocation] == 0)
		{
			theIsland[currentLocation] = 3;
		}
		else if (theIsland[currentLocation] == 1 || theIsland[currentLocation] == 2)
		{
			while (theIsland[currentLocation] == 1 || theIsland[currentLocation] == 2)
			{
				tempStorage = rand() % islandSize;
				currentLocation = tempStorage;
				if (theIsland[currentLocation] == 0)
				{
					theIsland[currentLocation] = 3;
				}
			}
		}
	}
}
