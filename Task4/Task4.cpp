#include "Graph.h"

int main()
{
	cout << "Creating A" << endl << endl;
	Graph A;
	A.PrintGraph();
	cout << endl << "Creating B = A" << endl << endl;
	Graph B = A;
	B.PrintGraph();
	cout << endl << "Deleting A" << endl << endl;
	A.~Graph();
	cout << endl << "Creating C" << endl << endl;
	Graph C;
	C.PrintGraph();
	cout << endl << "C = B" << endl << endl;
	C = B;
	C.PrintGraph();
	cout << endl << "Creating A and moving C to A" << endl << endl;
	A = CreateGraph();
	A.PrintGraph();
	return 0;
}