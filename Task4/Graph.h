#pragma once
#include <iostream>

using namespace std;
class Graph 
{
private:
	string Name;
	int Data;
	int NumberOfConnections;
	Graph** Connections;
public:
	Graph();
	Graph(const string& NewName, const int NewData, const int NewNumberOfConnections, const Graph** NewConnections);
	Graph(const Graph& AnotherGraph);
	Graph(Graph&& AnotherGraph);
};