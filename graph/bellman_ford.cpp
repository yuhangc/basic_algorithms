#include <iostream>
#include <vector>

#define INF 1e20

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

bool bellman_ford(int source, int dest, int n, std::vector<Edge>& edges, 
                    std::vector<int>& pi, std::vector<double>& d) {
    // initialize d
    for (int i = 0; i < n; i++)
        d[i] = INF;
    d[source] = 0;
    
    // bellman-ford
    for (int i = 0; i < n-1; i++) {
        for (auto edge: edges) {
            if (d[edge.from] + edge.value < d[edge.to]) {
                d[edge.to] = d[edge.from] + edge.value;
                pi[edge.to] = edge.from;
            }
        }
    }
    
    // detect negative cicle
    for (auto edge: edges) {
        if (d[edge.from] + edge.value < d[edge.to]) {
            return true;
        }
    }
    
    return false;
}

void print_path(int source, int dest, std::vector<int>& pi) {
    if (dest == source) {
        std::cout << source << "-->";
        return;
    }
    
    print_path(source, pi[dest], pi);
    std::cout << dest << "-->";
}

int main() {
	std::vector<Edge> edges;
	int n = 6;
	
	edges.push_back(Edge(0, 1, 2));
	edges.push_back(Edge(0, 2, 3));
	edges.push_back(Edge(1, 3, -1));
	edges.push_back(Edge(2, 3, 1));
	edges.push_back(Edge(2, 4, 1));
	edges.push_back(Edge(2, 5, 5));
	edges.push_back(Edge(3, 5, 3));
	edges.push_back(Edge(4, 5, 1));
	
	std::vector<int> pi(n);
	std::vector<double> d(n);
	
	bool has_negative_cicle = bellman_ford(0, 5, n, edges, pi, d);
	if (has_negative_cicle) {
	    std::cout << "Have negative cicle!" << std::endl;
	} else {
	    std::cout << "from 0 to 5: " << d[5] << std::endl;
	    print_path(0, 5, pi);
	    std::cout << "end" << std::endl;
	}
	
	return 0;
}
