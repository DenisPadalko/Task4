#pragma once
#include <iostream>

using namespace std;
class Graph 
{
private:
	string Name;
	int Data;
	size_t NumberOfConnections;
	size_t Capacity;
	Graph** Connections = nullptr;
	void ReAlloc();
public:
	Graph();
	Graph(const string& NewName, const int NewData, const size_t NewNumberOfConnections, const Graph** NewConnections, const bool IsStart);
	Graph(const Graph& AnotherGraph);
	Graph(Graph&& AnotherGraph);
	~Graph();

	const string& GetName() const;
	void SetName(const string NewName);
	const int GetData() const;
	void SetData(const int NewData);
	const size_t GetNumberOfConnections() const;
	const Graph** GetConnections() const;

	const Graph& operator=(const Graph& SomeGraph);
	const Graph& operator=(Graph&& SomeGraph);

	void CreateConnection(Graph& SomeGraph);
	void DeleteConnection(Graph& SomeGraph);
	void DeleteAllConnections(Graph& G);
	void PrintGraph();
};