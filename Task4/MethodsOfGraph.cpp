#include "Graph.h"

Graph* Start;
Graph::Graph() : Name("Somegraph"), Data(1234), NumberOfConnections(0), Capacity(0)
{
	Start = this;
}

Graph::Graph(const string& NewName, const int NewData, const size_t NewNumberOfConnections, const Graph** NewConnections, const bool IsStart) : Name(NewName), Data(NewData)
{
	for (size_t i = 0; i < NewNumberOfConnections; ++i)
	{
		CreateConnection((Graph&)(*NewConnections[i]));
	}
	if (IsStart) Start = this;
}

Graph::Graph(const Graph& AnotherGraph) : Name("New_" + AnotherGraph.Name), Data(AnotherGraph.Data), NumberOfConnections(0), Capacity(0)
{
	for (size_t i = 0; i < AnotherGraph.NumberOfConnections; ++i)
	{
		CreateConnection(*AnotherGraph.Connections[i]);
	}
}

Graph::Graph(Graph&& AnotherGraph) : Name(AnotherGraph.Name), Data(AnotherGraph.Data), NumberOfConnections(0), Capacity(0)
{
	for (size_t i = 0; i < AnotherGraph.NumberOfConnections; ++i)
	{
		CreateConnection(*AnotherGraph.Connections[i]);
	}
	DeleteAllConnections(AnotherGraph);
	AnotherGraph.~Graph();
}

Graph::~Graph() 
{
	if ((this == Start) && (Connections != nullptr)) Start = Connections[0];
	if (NumberOfConnections)
	{
		DeleteAllConnections(*this);
	}
	Data = 0;
	cout << "Graph element \"" << Name << "\" was successfully deleted" << endl;
}

const string& Graph::GetName() const
{
	return Name;
}

void Graph::SetName(const string NewName) 
{
	Name = NewName;
}

const int Graph::GetData() const
{
	return Data;
}

void Graph::SetData(const int NewData) 
{
	Data = NewData;
}

const size_t Graph::GetNumberOfConnections() const
{
	return NumberOfConnections;
}

const Graph** Graph::GetConnections() const
{
	return (const Graph**)Connections;
}

const Graph& Graph::operator=(const Graph& SomeGraph) 
{
	if (&SomeGraph == this) return *this;
	if (NumberOfConnections) 
	{
		for (size_t i = 0; i < NumberOfConnections; ++i)
		{
			Connections[i] = nullptr;
		}
		delete[] Connections;
	}
	Name = SomeGraph.Name;
	Data = SomeGraph.Data;
	Capacity = 0;
	for (size_t i = 0; i < SomeGraph.NumberOfConnections; ++i)
	{
		CreateConnection(*SomeGraph.Connections[i]);
	}
	return *this;
}

const Graph& Graph::operator=(Graph&& SomeGraph)
{
	if (&SomeGraph == this) return *this;
	if (NumberOfConnections)
	{
		for (size_t i = 0; i < NumberOfConnections; ++i)
		{
			Connections[i] = nullptr;
		}
		delete[] Connections;
	}
	Name = SomeGraph.Name;
	Data = SomeGraph.Data;
	Capacity = 0;
	for (size_t i = 0; i < SomeGraph.NumberOfConnections; ++i)
	{
		CreateConnection(*SomeGraph.Connections[i]);
	}
	DeleteAllConnections(SomeGraph);
	SomeGraph.Data = 0;
	return *this;
}

void Graph::CreateConnection(Graph& SomeGraph) 
{
	if (this == &SomeGraph)
	{
		cout << "Connection between same graph elements cannot be created" << endl;
		return;
	}
	for (size_t i = 0; i < NumberOfConnections; ++i)
	{
		if (Connections[i] == &SomeGraph) 
		{
			cout << "Connection between graph elements \"" << Name << "\" and \"" << SomeGraph.Name << "\" already exists" << endl;
			return; 
		}
	}
	if ((NumberOfConnections + 1 > Capacity) || (Capacity == 0)) this->ReAlloc();
	Connections[NumberOfConnections++] = &SomeGraph;
	if ((SomeGraph.NumberOfConnections + 1 > Capacity) || (SomeGraph.Capacity == 0)) SomeGraph.ReAlloc();
	SomeGraph.Connections[SomeGraph.NumberOfConnections++] = this;
}

void Graph::DeleteConnection(Graph& SomeGraph) 
{
	bool Flag = false;
	for (size_t i = 0; i < NumberOfConnections; ++i)
	{
		if (Connections[i] == &SomeGraph) Flag = true;
	}
	if (!Flag)
	{
		cout << "There is no connection between graph elements \"" << Name << "\" and \"" << SomeGraph.Name << "\"" << endl;
		return; 
	}
	size_t j = 0;
	for (size_t i = 0; i < NumberOfConnections; ++i)
	{
		if (Connections[i] == &SomeGraph) j = i;
	}
	for (size_t i = j; i < NumberOfConnections; ++i)
	{
		if (i + 1 < NumberOfConnections) Connections[i] = Connections[i + 1];
		else Connections[i] = nullptr;
	}
	--NumberOfConnections;
	for (size_t i = 0; i < SomeGraph.NumberOfConnections; ++i)
	{
		if (SomeGraph.Connections[i] == this) j = i;
	}
	for (size_t i = j; i < SomeGraph.NumberOfConnections; ++i)
	{
		if (i + 1 < SomeGraph.NumberOfConnections) SomeGraph.Connections[i] = SomeGraph.Connections[i + 1];
		else SomeGraph.Connections[i] = nullptr;
	}
	--SomeGraph.NumberOfConnections;
	if ((!NumberOfConnections) && (Start != this)) this->~Graph();
	if ((!SomeGraph.NumberOfConnections) && (Start != &SomeGraph)) SomeGraph.~Graph();
}


void Graph::DeleteAllConnections(Graph& G)
{
	if (G.NumberOfConnections == 0) return;
	while (G.NumberOfConnections > 0)
	{
		G.DeleteConnection(*G.Connections[0]);
	}
	G.Capacity = 0;
}

void Graph::PrintGraph() 
{
	cout << "Element adress: " << this << endl;
	cout << "Name: " << Name << endl;
	cout << "Data: " << Data << endl;
	cout << "Number of connections: " << NumberOfConnections << endl;
}

void Graph::ReAlloc()
{
	if (Capacity < 2) ++Capacity;
	else 
	{
	Capacity = Capacity + Capacity / 2;
	}
	Graph** NewConnections = new Graph * [Capacity];
	for (size_t i = 0; i < NumberOfConnections; ++i)
	{
		NewConnections[i] = Connections[i];
		Connections[i] = nullptr;
	}
	delete[] Connections;
	Connections = NewConnections;
}