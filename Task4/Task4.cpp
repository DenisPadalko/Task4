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
	B.PrintGraph();
	cout << endl << "Deleting A" << endl;
	A.~Graph();
	cout << endl << "Creating A and moving C to A" << endl << endl;
	A = CreateGraph(C);
	A.SetName("A");
	B.SetName("B");
	C.SetName("C");
	A.PrintGraph();
	B.PrintGraph();
	C.PrintGraph();
	return 0;
}