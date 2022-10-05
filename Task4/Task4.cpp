#include "Graph.h"

int main()
{
	cout << "Creating A" << endl << endl;
	Graph A;
	A.SetName("A");
	A.PrintGraph();
	cout << endl << "Creating B = A" << endl << endl;
	Graph B = A;
	B.SetName("B");
	B.PrintGraph();
	cout << endl << "Creating C" << endl << endl;
	Graph C;
	C.SetName("C");
	C.PrintGraph();
	cout << endl << "C = B" << endl << endl;
	C = B;
	C.SetName("C");
	C.PrintGraph();
	cout << endl << "Deleting A" << endl << endl;
	A.~Graph();
	cout << endl << "Creating A and moving C to A" << endl << endl;
	A = move(C);
	A.SetName("A");
	A.PrintGraph();
	return 0;
}