#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

#include "Array.h"

using namespace std;

Array::Array(int N) {
	size = N;
	items = new ItemType[size];
	sorted = new ItemType[size];

	if (!items || !sorted) {
		cerr << "\nMemory Allocation Failed!\n";
		exit(1);
	}
	else {
		cout << "\n|-------Generating Array of " << N << " Elements....-------|";
		for (int i = 0; i < size; i++) {
			items[i] = rand() % 301;	//Numbers Range <= 301
			sorted[i] = items[i];
		}
	}
	
}

void Array::display() {
	cout << "\nItems: \n";
	for (int i = 0; i < size; i++) {
		cout << setw(5) << items[i];
	}
	cout << "\n";
}

Array::~Array() {
	delete[] items;
	delete[] sorted;
}

int Array::max(int j, int k) {
	if (k == -1) {
		k = size - 1;
	}
	// Base case: if the segment has only one element, return it.
	if (j == k)
		return items[j];

	// Divide the array segment into two halves.
	int mid = (j + k) / 2;
	int leftMax = max(j, mid);
	int rightMax = max(mid + 1, k);

	// Return the larger of the two halves.
	return (leftMax > rightMax) ? maximum = leftMax : maximum = rightMax;
}

int Array::min(int j, int k) {
	if (k == -1) {
		k = size - 1;
	}
	// Base case: if the segment has only one element, return it.
	if (j == k)
		return items[j];

	// Divide the array segment into two halves.
	int mid = (j + k) / 2;
	int leftMin = min(j, mid);
	int rightMin = min(mid + 1, k);

	// Return the larger of the two halves.
	return (leftMin < rightMin) ? minimum = leftMin : minimum = rightMin;
}

int Array::range() {
	return (maximum - minimum);
}

int Array::sum(int j, int k) {
	if (k == -1) {
		k = size - 1;
	}
	// Base case: when the segment has a single element, return that element.
	if (j == k)
		return items[j];

	// Divide the segment into two halves.
	int mid = (j + k) / 2;
	int leftSum = sum(j, mid);
	int rightSum = sum(mid + 1, k);

	// Return the sum of both halves.
	return add = leftSum + rightSum;
}

long double Array::product(int j, int k) {
	if (k == -1) {
		k = size - 1;
	}
	// Base case: segment has one element.
	if (j == k)
		return items[j];

	int mid = (j + k) / 2;
	long double leftProduct = product(j, mid);
	long double rightProduct = product(mid + 1, k);

	if (minimum == 0) { return 0; }
	else
	return leftProduct * rightProduct;
}

double Array::mean() {
	return (add / size);
}

void Array::displaySorted() {
	cout << "\nSorted Items: ";
	for (int i = 0; i < size; i++) {
		cout << setw(5) << sorted[i];
	}
	cout << "\n";
}

int Array::sort(int left, int right) {
	// If right is default (-1), initialize it to size - 1.
	if (right == -1)
		right = size - 1;

	// Base case: if the subarray has 0 or 1 element, it's already sorted.
	if (left >= right)
		return 1;

	int mid = (left + right) / 2;

	// Recursively sort the left and right halves.
	sort(left, mid);
	sort(mid + 1, right);

	// Merge the two sorted halves.
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temporary arrays.
	int* L = new int[n1];
	int* R = new int[n2];

	// Copy data to temp arrays.
	for (int i = 0; i < n1; i++) {
		L[i] = sorted[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = sorted[mid + 1 + j];
	}

	// Merge the temp arrays back into sorted[left...right]
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			sorted[k++] = L[i++];
		}
		else {
			sorted[k++] = R[j++];
		}
	}
	// Copy any remaining elements of L[].
	while (i < n1) {
		sorted[k++] = L[i++];
	}
	// Copy any remaining elements of R[].
	while (j < n2) {
		sorted[k++] = R[j++];
	}
	
	// Free the temporary arrays.
	delete[] L;
	delete[] R;
}

double Array::median() {
	if (size == 0) {
		cerr << "Array is empty.\n";
		exit(1);
	}
	// We assume that sorted[] is already sorted.
	if (size % 2 == 0) {
		// Even number of elements: average the two middle values.
		return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
	}
	else {
		// Odd number of elements: return the middle element.
		return sorted[size / 2];
	}
}

struct Stats {
	long long sum;
	long double sumSq;
	int count;
};

Stats computeStats(ItemType arr[], int l, int r) {
	if (l == r)
		return { arr[l], (long double)arr[l] * arr[l], 1 };
	int m = (l + r) / 2;
	Stats s1 = computeStats(arr, l, m);
	Stats s2 = computeStats(arr, m + 1, r);
	return { s1.sum + s2.sum, s1.sumSq + s2.sumSq, s1.count + s2.count };
}

double Array::stDev() {
	if (size == 0) { cerr << "Empty array!\n"; exit(1); }
	Stats s = computeStats(items, 0, size - 1);
	double mean = s.sum / (double)s.count;
	return sqrt((s.sumSq / s.count) - mean * mean);
}

// ----- Divide and Conquer Mode -----
struct ModeData {
	int mode, freq, leftVal, leftFreq, rightVal, rightFreq, total;
};

ModeData computeMode(int arr[], int left, int right) {
	// Base case: if the segment consists of a single element, that element is the mode, and all counts are 1.
	if (left == right) {
		return { arr[left], 1,   // leftmost value and its frequency
				 arr[left], 1,   // rightmost value and its frequency
				 arr[left], 1,   // mode value and its frequency
				 1 };            // total count in this segment
	}

	// Divide: split the segment into two halves.
	int mid = (left + right) / 2;
	ModeData leftStats = computeMode(arr, left, mid);
	ModeData rightStats = computeMode(arr, mid + 1, right);

	// Prepare a result structure to combine the two halves.
	ModeData result;
	result.total = leftStats.total + rightStats.total;

	// Combine the left boundary:
	result.leftVal = leftStats.leftVal;
	// If the entire left segment is uniform and matches the start of the right segment,
	// then the left boundary frequency extends into the right half.
	if (leftStats.total == leftStats.leftFreq && leftStats.leftVal == rightStats.leftVal)
		result.leftFreq = leftStats.leftFreq + rightStats.leftFreq;
	else
		result.leftFreq = leftStats.leftFreq;

	// Combine the right boundary:
	result.rightVal = rightStats.rightVal;
	// Similarly, if the entire right segment is uniform and matches the end of the left segment,
	// then the right boundary frequency extends into the left half.
	if (rightStats.total == rightStats.rightFreq && rightStats.rightVal == leftStats.rightVal)
		result.rightFreq = rightStats.rightFreq + leftStats.rightFreq;
	else
		result.rightFreq = rightStats.rightFreq;

	// Determine the mode from the two halves:
	if (leftStats.freq >= rightStats.freq) {
		result.mode = leftStats.mode;
		result.freq = leftStats.freq;
	}
	else {
		result.mode = rightStats.mode;
		result.freq = rightStats.freq;
	}

	// Check if a candidate spanning the boundary beats the current mode.
	int crossFreq = 0;
	if (leftStats.rightVal == rightStats.leftVal)
		crossFreq = leftStats.rightFreq + rightStats.leftFreq;

	if (crossFreq > result.freq) {
		result.mode = leftStats.rightVal; // same as rightStats.leftVal
		result.freq = crossFreq;
	}

	return result;
}

int Array::mode() {
	if (size == 0) { cerr << "Empty array!\n"; exit(1); }
	ModeData md = computeMode(sorted, 0, size - 1);
	return md.mode;
}

void Array::searchDivide(int left, int right, int target, int& foundCount) {
	// Base case: invalid range.
	if (left > right)
		return;

	// If the range is a single element, check it.
	if (left == right) {
		if (items[left] == target) {
			cout << "\nFound " << target << " at index " << left;
			foundCount++;
		}
		return;
	}

	// Divide the range into two halves.
	int mid = (left + right) / 2;
	searchDivide(left, mid, target, foundCount);
	searchDivide(mid + 1, right, target, foundCount);
}

// Public search function: initiates the divide and conquer search.
void Array::search(int target) {
	int count = 0;
	searchDivide(0, size - 1, target, count);

	if (count == 0)
		cout << "\nNumber " << target << " not found in the array.\n";
}