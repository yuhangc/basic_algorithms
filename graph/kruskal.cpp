#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    double value;
    
    Edge(int new_from, int new_to, int new_value) {
        this->from = new_from;
        this->to = new_to;
        this->value = new_value;
    }
};

bool my_comp(Edge edge1, Edge edge2) {
    return edge1.value < edge2.value;
}

int find(std::vector<int>& parent, int node) {
    while (parent[node] != node) {
        parent[node] = parent[parent[node]];
        node = parent[node];
    }
    
    return node;
}

int unite(std::vector<int>& parent, int node1, int node2) {
    node1 = find(parent, node1);
    node2 = find(parent, node2);
    parent[node2] = node1;
}

double kruskal(std::vector<Edge>& edges, std::vector<Edge>& result, int n) {
    // first sort the edges
    std::sort(edges.begin(), edges.end(), my_comp);
    
    int m = edges.size();
    std::vector<int> parent(m);
    
    // initialize parent
    for (int i = 0; i < m; i++)
        parent[i] = i;
    
    // go through edges
    int mt_size = 0;
    for (auto edge : edges) {
        if (find(parent, edge.from) != find(parent, edge.to)) {
            result.push_back(edge);
            unite(parent, edge.from, edge.to);
            mt_size += edge.value;
        }
    }
    
    if (result.size() != n-1)
        return -1;
    else
        return mt_size;
}

int main() {
    int n = 6;
	std::vector<Edge> edges;
	
	edges.push_back(Edge(0, 1, 2));
	edges.push_back(Edge(0, 2, 3));
	edges.push_back(Edge(1, 3, 1));
	edges.push_back(Edge(2, 3, 1));
	edges.push_back(Edge(2, 4, 1));
	edges.push_back(Edge(2, 5, 5));
	edges.push_back(Edge(3, 5, 3));
	edges.push_back(Edge(4, 5, 1));
	
	std::vector<Edge> result;
	int mt_size = kruskal(edges, result, n);
	
	if (mt_size < 0) {
	    std::cout << "Graph is not connected!" << std::endl;
	} else {
	    std::cout << mt_size << std::endl;
	    for (auto edge : result) {
	        std::cout << edge.from << " --- " << edge.to << std::endl;
	    }
	}
	
	return 0;
}
