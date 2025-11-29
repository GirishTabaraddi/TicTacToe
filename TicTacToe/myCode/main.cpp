//! Standard (system) header files
#include <iostream>
#include <cstdlib>
//! Add more standard header files as required

using namespace std;

//! Add your project's header files here
#include "CBoard.h"
#include "CDisplay.h"

int main ()
{
	cout << "TicTacToe started." << endl << endl;

	CBoard C(3,3);

	CDisplay D;

	D.printBoard(C);

	return 0;
}
