#include <iostream>
#include <vector>
#include <utility>

#define INF 1e20

typedef std::vector<std::vector<std::pair<int, double> > > adj_map;

double dijkstra(int source, int dest, adj_map& adj, std::vector<int>& pi) {
    int n = adj.size();
    std::vector<double> d(n, INF);
    std::vector<bool> visited(n);
    
    d[source] = 0;
    while (true) {
        // find the minimum unvisited node
        double min_dist = INF;
        int min_node = -1;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && d[i] < min_dist) {
                min_dist = d[i];
                min_node = i;
            }
        }
        
        // break if couldn't find such node or find destination
        if (min_node == -1 || min_node == dest)
            break;
            
        // update d and pi
        visited[min_node] = true;
        for (auto link: adj[min_node]) {
            int next = link.first;
            double dist = link.second;
            if (!visited[next] && d[min_node] + dist < d[next]) {
                d[next] = d[min_node] + dist;
                pi[next] = min_node;
            }
        }
    }
    
    return d[dest];
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
	
	std::vector<int> pi(n);
	
	std::cout << "from 0 to 5: " << dijkstra(0, 5, adj, pi) << std::endl;
	print_path(0, 5, pi);
	std::cout << "end" << std::endl;
	
	std::cout << "from 2 to 5: " << dijkstra(2, 5, adj, pi) << std::endl;
	print_path(2, 5, pi);
	std::cout << "end" << std::endl;
	
	return 0;
}
