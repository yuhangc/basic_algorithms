#include <iostream>
#include <algorithm>
#include <vector>

int partition(std::vector<int> &arr, const int l, const int r) {
    // use the mid point as pivot
    int piv = l + (r - l) / 2;
    
    // swap pivot point with the first element
    std::swap(arr[l], arr[piv]);
    
    // move two pointers
    int i = l + 1;
    int j = r;
    
    while (i <= j) {
        while (i <= j && arr[i] <= arr[l])
            i++;
        while (i <= j && arr[j] > arr[l])
            j--;
        
        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    // swap back the pivot
    std::swap(arr[i-1], arr[l]);
    
    return i-1;
}

void quick_sort(std::vector<int> &arr, const int l, const int r) {
    // end condition
    if (l >= r)
        return;
    
    // partition the array with partition function
    int mid = partition(arr, l, r);
    
    // recursion
    quick_sort(arr, l, mid-1);
    quick_sort(arr, mid+1, r);
}

int main() {
	// input array
	int a[16] = {10, 4, 100, 34, 56, 78, 23, 38, 19, 60, 48, 75, 49, 19, 59, 95};
	std::vector<int> avec (a, a + sizeof(a) / sizeof(a[0]));
	
	// sort
	quick_sort(avec, 0, avec.size()-1);
	
	// output
	for (int i = 0; i < avec.size(); i++)
	    std::cout << avec[i] << ", ";
	std::cout << std::endl;
	
	return 0;
}
