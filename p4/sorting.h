#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting 
{

	//************
	// QuickSort *
	//************
	void QuickSort(vector<int> &arr, int left, int right);
	int partition(vector<int> &arr, int left, int right);

	//************
	// MergeSort *
	//************
	void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high);
	void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

	//************
	// Heapsort  *
	//************
	void HeapSort(vector<int> &arr, int n);
	void percDown(vector<int> &arr, int n, int i);
	//************
	// Shellsort *
	//************
	void ShellSort(vector<int> &a, int n);

	//*******************
	// Helper functions *
	//*******************
	void randomizeVector(vector<int> &array, int n);

}
#endif 
