#pragma once
#include<vector>





class GraphNode
{
public:
	struct edge
	{
		//GraphNode* next_node;
		int weighting;
		int parent;
		int other;
	};
	

	GraphNode(int key);
	int get_key();
	void set_key(int value);
	bool get_visited();
	void set_visited(bool value);
	void add_edge(edge value);
	edge* get_edge(int value);
	int get_number_of_edges();
	int get_component();
	void set_component(int value);


private:

	std::vector<edge> edges;
	int key;
	bool visited;
	int component;
};