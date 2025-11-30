//! Standard (system) header files
#include <iostream>
#include <cstdlib>
//! Add more standard header files as required

using namespace std;

//! Add your project's header files here
#include "CBoard.h"
#include "CDisplay.h"
#include <memory>
#include "CHuman.h"

int main ()
{
	cout << "TicTacToe started." << endl << endl;

	unique_ptr<CBoard> C;

	try
	{
		C = make_unique<CBoard>(3,3);
	}
	catch(invalid_argument &i)
	{
		cerr << "Board Creation Failed: " << i.what() << endl;
		return -1;
	}
	catch(...)
	{
		cerr << "Unknown Failure." << endl;
	}


	CDisplay D;

	D.printBoard(*C);

	return 0;
}
