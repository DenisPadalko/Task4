#include "Graph.h"

Graph::Graph() 
{
	Name = "SomeGraph";
	Data = 1234;
	NumberOfConnections = 0;
}

Graph::Graph(const string& NewName, const int NewData, const int NewNumberOfConnections, const Graph** NewConnections)
{
	Name = NewName;
	Data = NewData;
	NumberOfConnections = NewNumberOfConnections;
	Connections = new Graph* [NumberOfConnections];
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		Connections[i] = (Graph*)NewConnections[i];
	}
}

Graph::Graph(const Graph& AnotherGraph) 
{
	Name = AnotherGraph.Name;
	Data = AnotherGraph.Data;
	NumberOfConnections = AnotherGraph.NumberOfConnections;
	Connections = new Graph* [NumberOfConnections];
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		Connections[i] = AnotherGraph.Connections[i];
	}
}

Graph::Graph(Graph&& AnotherGraph) 
{
	Name = AnotherGraph.Name;
	Data = AnotherGraph.Data;
	NumberOfConnections = AnotherGraph.NumberOfConnections;
	Connections = AnotherGraph.Connections;

	for (int i = 0; i < NumberOfConnections; ++i)
	{
		AnotherGraph.Connections[i] = nullptr;
		delete AnotherGraph.Connections[i];
	}
	AnotherGraph.Connections = nullptr;
	delete[] AnotherGraph.Connections;
}