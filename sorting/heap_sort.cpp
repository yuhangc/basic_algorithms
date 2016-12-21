#include <iostream>
#include <algorithm>
#include <vector>

void max_heapify(std::vector<int>& arr, const int root, const int sz) {
    // end condition, leaf node
    if (root >= sz / 2)
        return;
    
    // inspect its left and right child
    int left = 2 * root + 1;
    int right = 2 * (root + 1);
    
    int max_id = root;
    
    if (arr[left] > arr[max_id])
        max_id = left;
    
    if (right < sz && arr[right] > arr[max_id])
        max_id = right;
    
    if (max_id != root) {
        std::swap(arr[root], arr[max_id]);
        max_heapify(arr, max_id, sz);
    }
}

void build_heap(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2-1; i >= 0; i--)
        max_heapify(arr, i, n);
}

void heap_sort(std::vector<int>& arr) {
    // build the heap
    build_heap(arr);
	
    // heap sort
    for (int i = arr.size()-1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        max_heapify(arr, 0, i);
    }
}

int main() {
	// input array
	std::vector<int> avec = {10, 4, 100, 34, 56, 78, 23, 38, 19, 60, 48, 75, 49, 19, 59, 95};
	
	// sort
	heap_sort(avec);
	
	// output
	for (int i = 0; i < avec.size(); i++)
	    std::cout << avec[i] << ", ";
	std::cout << std::endl;
	
	return 0;
}
