/*

	Evan Bradford
	4/8/2016
	Checkers
	CS2401

*/

#include "colors.h"
#include "checkers.h"
#include "game.h"

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	char ans;
	do
	{
		Checkers mygame;
		mygame.play();
		cout << "Play again?(Y/N)\n";
		cin >> ans;
	}while(ans == 'y' || ans == 'Y');

	return 0;
}
