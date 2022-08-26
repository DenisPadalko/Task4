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
	Graph(const string& NewName, const int NewData, const int NewNumberOfConnections, const Graph** NewConnections, const bool IsStart);
	Graph(const Graph& AnotherGraph);
	Graph(Graph&& AnotherGraph);
	~Graph();

	const Graph& operator=(const Graph& SomeGraph);
	const Graph& operator=(Graph&& SomeGraph);

	void CreateConnection(Graph& SomeGraph);
	void DeleteConnection(Graph& SomeGraph);
	void DeleteAllConnections(Graph& G);
	void PrintGraph();
};

const Graph& CreateGraph();