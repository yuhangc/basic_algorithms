#include <iostream>
#include <vector>
#include <utility>

#define INF 1e20

typedef std::vector<std::vector<std::pair<int, double> > > adj_map;

double prim(adj_map& adj, std::vector<int>& pi) {
    int n = adj.size();
    double mt_size = 0;
    std::vector<double> d(n, INF);
    std::vector<bool> visited(n);
    
    d[0] = 0;
    for (int i = 0; i < n; i++) {
        // find the minimum unvisited node
        double min_dist = INF;
        int min_node = -1;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && d[i] < min_dist) {
                min_dist = d[i];
                min_node = i;
            }
        }
        
        mt_size += min_dist;
        
        // break if couldn't find such node or find destination
        if (min_node == -1)
            return -1;
            
        // update d and pi
        visited[min_node] = true;
        for (auto link: adj[min_node]) {
            int next = link.first;
            double dist = link.second;
            if (!visited[next] && dist < d[next]) {
                d[next] = dist;
                pi[next] = min_node;
            }
        }
    }
    
    return mt_size;
}

void convert_to_undirected(adj_map& adj) {
    int n = adj.size();
    for (int i = 0; i < n; i++) {
        for (auto link: adj[i]) {
            int next = link.first;
            double dist = link.second;
            adj[next].push_back(std::make_pair(i, dist));
        }
    }
}

int main() {
    // use adjacency map representation
    int n = 6;
	adj_map adj(n);
	
	// manually define the graph
	adj[0].push_back(std::make_pair(1, 2));
	adj[0].push_back(std::make_pair(2, 3));
	adj[1].push_back(std::make_pair(3, 1));
	adj[2].push_back(std::make_pair(3, 1));
	adj[2].push_back(std::make_pair(4, 1));
	adj[2].push_back(std::make_pair(5, 5));
	adj[3].push_back(std::make_pair(5, 3));
	adj[4].push_back(std::make_pair(5, 1));
	
	// convert to undirected graph
	convert_to_undirected(adj);
	
	std::vector<int> pi(n);
	
	int mt_size = prim(adj, pi);
	if (mt_size < 0) {
	    std::cout << "not a connected graph!" << std::endl;
	} else {
	    std::cout << "Minimum spanning tree size: " << mt_size << std::endl;
	    for (int i = 1; i < n; i++) {
	        std::cout << i << " --- " << pi[i] << std::endl;
	    }
	}
	
	return 0;
}
