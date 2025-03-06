#pragma once
typedef int ItemType;

class Array {
private:
	ItemType* items;
	ItemType* sorted;
	ItemType size;
	ItemType minimum = 0, maximum = 0;
	double add = 0;
	void searchDivide(int left, int right, int target, int& foundCount);
public:
	Array(int N);
	void display();
	int range();
	int max(int j = 0, int k = -1);
	int min(int j = 0, int k = -1);
	int sum(int j = 0, int k = -1);
	long double product(int j = 0, int k = -1);
	double mean();
	int sort(int left = 0, int right = -1);
	void displaySorted();
	double median();
	double stDev();
	int mode();
	void search(int target);
	
	~Array();
};