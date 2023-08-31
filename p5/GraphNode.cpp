#include"GraphNode.h"

using namespace std;



GraphNode::GraphNode(int _key)
{
	key = _key;
	visited = false;
	int component = -1;
}


int GraphNode::get_key()
{
	return key;
}

void GraphNode::set_key(int value)
{
	key = value;
}

bool GraphNode::get_visited()
{
	return visited;
}

void GraphNode::set_visited(bool value)
{
	visited = value;
}

void GraphNode::add_edge(edge value)
{
	
	edges.push_back(value);
}

GraphNode::edge* GraphNode::get_edge(int value)
{
	return &edges[value];
}

int GraphNode::get_number_of_edges()
{
	return edges.size();
}

int GraphNode::get_component()
{
	return component;
}

void GraphNode::set_component(int value)
{
	component = value;
}



