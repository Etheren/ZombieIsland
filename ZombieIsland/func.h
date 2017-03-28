#ifndef INCLUDED_DRAW_ISLAND
#define INCLUDED_DRAW_ISLAND

#include <vector>

using namespace std;

void drawIsland(vector<int> &theIsland);
void checkInput(int&, int&);

class Walkers
{
public:
	int previousLocation = 0;
	int currentLocation = 0;
};

class Human : public Walkers
{

public:
	void setLocation(int, vector<int> &theIsland);
	void moveCharacter(int, int, int, int&, vector<int> &theIsland);
};

class Zombie : public Walkers
{
private:
public:
	int zombieAlive = 1;
	void setLocation(int, vector<int> &theIsland);
	void moveRandomly(int, int, int& ,int&, vector<int> &theIsland);
};

class Hole : public Walkers
{
private:
public:
	void setLocation(int, vector<int> &theIsland);
};


#endif