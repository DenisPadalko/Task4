#include "Graph.h"

Graph* Start;
Graph::Graph() 
{
	Name = "SomeGraph";
	Data = 1234;
	NumberOfConnections = 0;
	Start = this;
}

Graph::Graph(const string& NewName, const int NewData, const int NewNumberOfConnections, const Graph** NewConnections, const bool IsStart)
{
	Name = NewName;
	Data = NewData;
	for (int i = 0; i < NewNumberOfConnections; ++i)
	{
		CreateConnection((Graph&)(*NewConnections[i]));
	}
	if (IsStart) Start = this;
}

Graph::Graph(const Graph& AnotherGraph) 
{
	Name = "New_";
	Name += AnotherGraph.Name;
	Data = AnotherGraph.Data;
	int TempNumber = AnotherGraph.NumberOfConnections;
	for (int i = 0; i < TempNumber; ++i)
	{
		CreateConnection(*AnotherGraph.Connections[i]);
	}
}

Graph::Graph(Graph&& AnotherGraph) 
{
	Name = AnotherGraph.Name;
	Data = AnotherGraph.Data;
	NumberOfConnections = 0;
	int TempNumber = AnotherGraph.NumberOfConnections;
	for (int i = 0; i < TempNumber; ++i)
	{
		CreateConnection(*AnotherGraph.Connections[i]);
	}
	DeleteAllConnections(AnotherGraph);
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		delete AnotherGraph.Connections[i];
	}
	AnotherGraph.Data = 0;
	delete[] AnotherGraph.Connections;
}

Graph::~Graph() 
{
	if ((this == Start) && (Connections != nullptr)) Start = Connections[0];
	if (Connections)
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

const int Graph::GetNumberOfConnections() const
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
	if (Connections) 
	{
		for (int i = 0; i < NumberOfConnections; ++i)
		{
			delete Connections[i];
		}
		delete[] Connections;
	}
	Name = SomeGraph.Name;
	Data = SomeGraph.Data;
	int TempNumber = SomeGraph.NumberOfConnections;
	for (int i = 0; i < TempNumber; ++i)
	{
		CreateConnection(*SomeGraph.Connections[i]);
	}
	CreateConnection((Graph&)SomeGraph);
	return *this;
}

const Graph& Graph::operator=(Graph&& SomeGraph)
{
	if (&SomeGraph == this) return *this;
	if (Connections)
	{
		for (int i = 0; i < NumberOfConnections; ++i)
		{
			delete Connections[i];
			//Connections[i] = nullptr;
		}
		delete[] Connections;
	}
	Name = SomeGraph.Name;
	Data = SomeGraph.Data;
	int TempNumber = SomeGraph.NumberOfConnections;
	for (int i = 0; i < TempNumber; ++i)
	{
		CreateConnection(*SomeGraph.Connections[i]);
	}
	DeleteAllConnections(SomeGraph);
	delete[] SomeGraph.Connections;
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
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		if (Connections[i] == &SomeGraph) 
		{
			cout << "Connection between graph elements \"" << Name << "\" and \"" << SomeGraph.Name << "\" already exists" << endl;
			return; 
		}
	}
	Graph** TempConnections = new Graph* [NumberOfConnections];
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		TempConnections[i] = Connections[i];
		Connections[i] = nullptr;
	}
	delete[] Connections;
	++NumberOfConnections;
	Connections = new Graph* [NumberOfConnections];
	for (int i = 0; i < NumberOfConnections - 1; ++i)
	{
		Connections[i] = TempConnections[i];
		TempConnections[i] = nullptr;
	}
	delete[] TempConnections;
	Connections[NumberOfConnections - 1] = &SomeGraph;
	TempConnections = new Graph* [SomeGraph.NumberOfConnections];
	for (int i = 0; i < SomeGraph.NumberOfConnections; ++i)
	{
		TempConnections[i] = SomeGraph.Connections[i];
		SomeGraph.Connections[i] = nullptr;
	}
	delete[] SomeGraph.Connections;
	++SomeGraph.NumberOfConnections;
	SomeGraph.Connections = new Graph* [SomeGraph.NumberOfConnections];
	for (int i = 0; i < SomeGraph.NumberOfConnections - 1; ++i)
	{
		SomeGraph.Connections[i] = TempConnections[i];
		TempConnections[i] = nullptr;
	}
	delete[] TempConnections;
	SomeGraph.Connections[SomeGraph.NumberOfConnections - 1] = this;
}

void Graph::DeleteConnection(Graph& SomeGraph) 
{
	bool Flag = false;
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		if (Connections[i] == &SomeGraph) Flag = true;
	}
	if (!Flag)
	{
		cout << "There is no connection between graph elements \"" << Name << "\" and \"" << SomeGraph.Name << "\"" << endl;
		return; 
	}
	Graph** TempConnections = new Graph* [NumberOfConnections];
	for (int i = 0; i < NumberOfConnections; ++i)
	{
		TempConnections[i] = Connections[i];
		Connections[i] = nullptr;
	}
	delete[] Connections;
	--NumberOfConnections;
	Connections = new Graph* [NumberOfConnections];
	int j = 0;
	for (int i = 0; i <= NumberOfConnections; ++i)
	{
		if (TempConnections[i] != &SomeGraph) 
		{
			Connections[j] = TempConnections[i];
			++j;
		}
		TempConnections[i] = nullptr;
	}
	delete[] TempConnections;

	TempConnections = new Graph * [SomeGraph.NumberOfConnections];
	for (int i = 0; i < SomeGraph.NumberOfConnections; ++i)
	{
		TempConnections[i] = SomeGraph.Connections[i];
		SomeGraph.Connections[i] = nullptr;
	}
	delete[] SomeGraph.Connections;
	--SomeGraph.NumberOfConnections;
	SomeGraph.Connections = new Graph * [SomeGraph.NumberOfConnections];
	j = 0;
	for (int i = 0; i <= SomeGraph.NumberOfConnections; ++i)
	{
		if (TempConnections[i] != this)
		{
			SomeGraph.Connections[j] = TempConnections[i];
			++j;
		}
		TempConnections[i] = nullptr;
	}
	delete[] TempConnections;
}


void Graph::DeleteAllConnections(Graph& G)
{
	if (G.NumberOfConnections == 0) return;
	Graph* Temp;
	while (G.NumberOfConnections > 0)
	{
		Temp = G.Connections[0];
		G.DeleteConnection(*Temp);
	}
}

void Graph::PrintGraph() 
{
	cout << "Element adress: " << this << endl;
	cout << "Name: " << Name << endl;
	cout << "Data: " << Data << endl;
	cout << "Number of connections: " << NumberOfConnections << endl;
}