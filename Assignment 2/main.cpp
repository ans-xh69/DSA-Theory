#include<iostream>
#include "Array.h"

using namespace std;

int main() {
	char yn;
	Array a (50000);

	cout << "Generating Numbers.......\n\nWould you like the random numbers array to be displayed?\t[y / n]: ";
	cin >> yn;
	yn = tolower(yn);

	switch (yn) {
	case 'y':
		a.display();
		break;
	case 'n':
		break;
	default:
		cout << "\nInvalid Choice!";
		break;
	}

	cout << "\nMaximum: " << a.max();
	cout << "\nMinimum: " << a.min();
	cout << "\nRange: " << a.range();
	cout << "\nSum: " << a.sum();
	cout << "\nProduct: " << a.product();
	cout << "\nMean: " << a.mean();

	a.sort();
	cout << "\nMedian: " << a.median();
	cout << "\nStandard Deviation: " << a.stDev();
	cout << "\nMode: " << a.mode();
	
	cout << endl;
	a.search(301);

	cout << "\n\nDo you want to display the sorted array?\t[y / n]: ";
	cin >> yn;
	yn = tolower(yn);

	switch (yn) {
	case 'y':
		a.displaySorted();
		break;
	case 'n':
		break;
	default:
		cout << "\nInvalid Choice!";
		break;
	}

}