#pragma once
#include<vector>
#include"GraphNode.h"
#include<string>

class Graph
{
public:
	Graph();
	~Graph();
	bool init(std::string filename);
	bool print_all();
	bool depthSearchRek(int start_key);
	bool breadthSearchIter(int start_key);
	bool iterdepth(int start_key);
	double prim(int start_key);
	double kruskal();
	int getAnzKnoten();
	void dijkstra(int start_node);


private:


	int depth_of_search=0;
	std::vector<GraphNode::edge*> get_all_edges();
	void sort_edges_weight(std::vector<GraphNode::edge*>& vector);

	int number_of_nodes;
	bool gerichtet;
	bool gewichtet;
	std::vector<GraphNode*> nodes;
	GraphNode* get_node_by_key(int key);
	void set_all_unvisited();
	bool check_visited();

	
	void start_depth_search_recursively(GraphNode* node);

	bool test_child_component(GraphNode* node);
};