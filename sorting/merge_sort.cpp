#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, const int l, const int r, const int m) {
    int n = r - l;
    
    std::vector<int> merged(n);
    
    int i = l;
    int j = m;
    int k = 0;
    
    while (i < m && j < r) {
        if (arr[i] <= arr[j]) {
            merged[k] = arr[i];
            i++;
        } else {
            merged[k] = arr[j];
            j++;
        }
        k++;
    }
    
    // directly copy the rest of arr
    while (i < m) {
        merged[k] = arr[i];
        i++;
        k++;
    }
    
    while (j < r) {
        merged[k] = arr[j];
        j++;
        k++;
    }
    
    // copy merged to arr
    for (i = 0; i < n; i++) {
        arr[l + i] = merged[i];
    }
}

void merge_sort(std::vector<int>& arr, const int l, const int r) {
    // end condition
    if (l >= r-1)
        return;
        
    // merge sort
    int m = l + (r - l) / 2;
    
    merge_sort(arr, l, m);
    merge_sort(arr, m, r);
    merge(arr, l, r, m);
}

int main() {
	// input array
	// int a[16] = {10, 4, 100, 34, 56, 78, 23, 38, 19, 60, 48, 75, 49, 19, 59, 95};
	// std::vector<int> avec (a, a + sizeof(a) / sizeof(a[0]));
	std::vector<int> avec = {10, 4, 100, 34, 56, 78, 23, 38, 19, 60, 48, 75, 49, 19, 59, 95};
	
	// sort
	merge_sort(avec, 0, avec.size());
	
	// output
	for (int i = 0; i < avec.size(); i++)
	    std::cout << avec[i] << ", ";
	std::cout << std::endl;
	
	return 0;
}
