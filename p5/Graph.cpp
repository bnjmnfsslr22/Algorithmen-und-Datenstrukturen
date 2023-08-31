#include"GraphNode.h"
#include"Graph.h"
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<stack>
#include<queue>
using namespace std;

Graph::Graph()
{
	number_of_nodes = 0;
	gewichtet = true;
	gerichtet = false;
}

Graph::~Graph()
{
	for (int index = 0; index < number_of_nodes; index++)
	{
		delete nodes[index];
	}
}

bool Graph::init(std::string filename)
{
	ifstream file;
	file.open(filename, ios_base::in);

	if (!file)
	{
		cout << "Cannot open file" << endl;
	}
	else
	{
		gerichtet = false;
		gewichtet = true;
		int number_nodes;
		string line;
		getline(file, line);
		number_nodes = stoi(line);
		number_of_nodes = number_nodes;


		for (int index = 0; index < number_nodes; index++)
		{
			GraphNode* to_save = new GraphNode(index);
			nodes.push_back(to_save);
		}
		while (getline(file, line))
		{
			string weight;
			string next;
			string start;

			istringstream iss(line);
			iss >> start;
			iss >> next;
			iss >> weight;

			GraphNode::edge new_edge;
			GraphNode::edge new_reverse;
			new_edge.parent = stoi(start);
			new_reverse.parent = stoi(next);
			new_edge.weighting = stoi(weight);
			new_reverse.weighting = stoi(weight);
			new_edge.other = stoi(next);
			new_reverse.other = stoi(start);
			nodes[stoi(next)]->add_edge(new_reverse);
			nodes[stoi(start)]->add_edge(new_edge);
		}
		return true;
	}
	return false;
}

bool Graph::print_all()
{
	for (int index = 0; index < number_of_nodes; index++)
	{
		GraphNode* to_print_node = nodes[index];
		cout << "Konten :" << to_print_node->get_key();
		for (int index2 = 0; index2 < to_print_node->get_number_of_edges(); index2++)
		{
			cout << " -> " << to_print_node->get_edge(index2)->other << " [" << to_print_node->get_edge(index2)->weighting << "] ";
		}
		cout << endl;
	}
	cout << endl;
	return true;
}

bool Graph::depthSearchRek(int start_key)
{
	nodes[start_key]->set_visited(true);

	for (int index = 0; index < nodes[start_key]->get_number_of_edges(); index++)
	{
		if (nodes[nodes[start_key]->get_edge(index)->other]->get_visited() == false)
		{
			depth_of_search++;
			depthSearchRek(nodes[start_key]->get_edge(index)->other);
			depth_of_search--;
		}
	}

	if (depth_of_search == 0)
	{
		if (check_visited() == true)
		{
			set_all_unvisited();
			return true;
		}
		else
		{
			set_all_unvisited();
			return false;
		}
	}
	else
	{
		return false;
	}

}
bool Graph::iterdepth(int start_key)
{
	stack<GraphNode::edge*> st;
	vector<int>edgeto(number_of_nodes);
	
	for (int index = 0; index < nodes[start_key]->get_number_of_edges(); index++)
	{
		st.push(nodes[start_key]->get_edge(index));
		edgeto[nodes[start_key]->get_edge(index)->other] = start_key;
	}
	vector<int>marked(number_of_nodes);
	marked[start_key] = 1;
	int count = 1;

	while (!st.empty())
	{
		GraphNode::edge* tmp = st.top();
		st.pop();
		if (marked[tmp->parent] == 0)
		{
			count++;
			marked[tmp->parent] = count;
		}
		for (int index = 0; index < nodes[tmp->parent]->get_number_of_edges(); index++)
		{
			if (marked[nodes[tmp->parent]->get_edge(index)->other] == 0)
			{
				st.push(nodes[tmp->parent]->get_edge(index));
				edgeto[nodes[tmp->parent]->get_edge(index)->other] = tmp->parent;
			}
		}

	}
}

bool Graph::breadthSearchIter(int start_key)
{
	queue<int> q;

	q.push(start_key);

	int v;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		nodes[v]->set_visited(true);
		for (int index = 0; index < nodes[v]->get_number_of_edges(); index++)
		{
			if (nodes[nodes[v]->get_edge(index)->other]->get_visited() == false)
			{
				q.push(nodes[v]->get_edge(index)->other);
			}
		}
	}

	if (check_visited() == true)
	{
		set_all_unvisited();
		return true;
	}
	else
	{
		set_all_unvisited();
		return false;
	}
}

void Graph::sort_edges_weight(vector<GraphNode::edge*>& pq)
{
	int n = pq.size();
	//sortieren mit Shellsort cuz Shellsort is love Shellsort is life 
	int start = pow(2, int(log(n) / log(2))) - 1;
	for (int abstand = start; abstand > 0; abstand = (abstand - 1) / 2)
	{
		for (int index = abstand; index < n; index++)
		{
			GraphNode::edge* tmp = pq[index];
			int j = index;
			for (; j >= abstand && tmp->weighting <= pq[j - abstand]->weighting; j -= abstand)
			{
				pq[j] = pq[j - abstand];
			}
			pq[j] = tmp;
		}
	}
}

double Graph::prim(int start_key)
{
	vector<GraphNode::edge*> pq;

	int cost_of_mst = 0;

	for (int index = 0; index < nodes[start_key]->get_number_of_edges(); index++)
	{
		pq.push_back(nodes[start_key]->get_edge(index));
	}

	sort_edges_weight(pq);

	GraphNode::edge* _edge2 = pq.front();
	nodes[_edge2->parent]->set_visited(true);


	while (!pq.empty())
	{
		GraphNode::edge* _edge = pq.front();
		pq.erase(pq.begin());

		if (nodes[_edge->other]->get_visited() == false)
		{

			cost_of_mst += _edge->weighting;
			nodes[_edge->other]->set_visited(true);

			for (int index = 0; index < nodes[_edge->other]->get_number_of_edges(); index++)
			{
				pq.push_back(nodes[_edge->other]->get_edge(index));
			}
			sort_edges_weight(pq);
		}

	}
	set_all_unvisited();
	return cost_of_mst;
}



double Graph::kruskal()
{
	vector<GraphNode::edge*> pq = get_all_edges();
	vector<GraphNode::edge*> mst;
	int cost_of_mst = 0;
	sort_edges_weight(pq);

	for (int index = 0; index < number_of_nodes; index++)
	{
		nodes[index]->set_component(index);
	}

	while (!pq.empty())
	{
		GraphNode::edge* e = pq.front();
		pq.erase(pq.begin());


		int v = e->parent;
		int v2 = nodes[v]->get_component();
		int w = e->other;
		int w2 = nodes[w]->get_component();


		if (nodes[v]->get_component() != nodes[w]->get_component())
		{
			mst.push_back(e);
			cost_of_mst += e->weighting;
			for (int index = 0; index < number_of_nodes; index++)
			{
				if (nodes[index]->get_component() == w2)
				{
					nodes[index]->set_component(v2);
				}
			}
		}
		if (mst.size() == number_of_nodes - 1)
		{
			break;
		}

	}
	set_all_unvisited();
	return cost_of_mst;
}




vector<GraphNode::edge*> Graph::get_all_edges()
{
	vector<GraphNode::edge*> all_edges;
	for (int index = 0; index < number_of_nodes; index++)
	{
		for (int index2 = 0; index2 < nodes[index]->get_number_of_edges(); index2++)
		{
			all_edges.push_back(nodes[index]->get_edge(index2));
		}
	}
	return all_edges;
}

int Graph::getAnzKnoten()
{
	return number_of_nodes;
}

GraphNode* Graph::get_node_by_key(int key)
{
	return nodes[key];
}

void Graph::set_all_unvisited()
{
	for (int index = 0; index < number_of_nodes; index++)
	{
		nodes[index]->set_visited(false);
	}
}

bool Graph::check_visited()
{
	for (int index = 0; index < number_of_nodes; index++)
	{
		if (nodes[index]->get_visited() == false)
		{
			return false;
		}
	}

	return true;
}

void Graph::dijkstra(int start_node)
{

	vector<int>dist_to(number_of_nodes);

	vector<GraphNode::edge*> pq;

	for (int index = 0; index < nodes[start_node]->get_number_of_edges(); index++)
	{
		pq.push_back(nodes[start_node]->get_edge(index));
	}

	sort_edges_weight(pq);

	for (int index = 0; index < number_of_nodes; index++)
	{
		dist_to[index] = 1000;
	}
	dist_to[start_node] = 0.0;



	while (!pq.empty())
	{
		GraphNode::edge* _edge = pq.front();
		pq.erase(pq.begin());
		int v = _edge->parent;

		//Int V hier festlegen für aufruf

		//Funktionsaufruf Hier mit int v
		vector<GraphNode::edge*> e;
		for (int index = 0; index < nodes[v]->get_number_of_edges(); index++)
		{
			e.push_back(nodes[v]->get_edge(index));
		}

		for (int index = 0; index < e.size(); index++)
		{
			int w = e[index]->other;
			if (dist_to[w] > dist_to[v] + e[index]->weighting)
			{
				dist_to[w] = dist_to[v] + e[index]->weighting;
				nodes[w]->set_visited(true);
			}

		}
		//Funktions aufruf ende
		for (int index = 0; index < nodes[_edge->other]->get_number_of_edges(); index++)
		{
			if (nodes[nodes[_edge->other]->get_edge(index)->other]->get_visited() != true)
			{
				pq.push_back(nodes[_edge->other]->get_edge(index));
			}
		}
		sort_edges_weight(pq);
	}
	cout << "Kosten zu den einzelnen Knoten von Ihrem gewaehlten Startknoten aus:" << endl;
	for (int index = 0; index < dist_to.size(); index++)
	{
		cout << dist_to[index] << " ; ";
	}
	cout << endl << endl;
	set_all_unvisited();
}


void Graph::start_depth_search_recursively(GraphNode* node)
{
	depthSearchRek(node->get_key());
}

bool Graph::test_child_component(GraphNode* node)
{
	//for what
	return true;
}





