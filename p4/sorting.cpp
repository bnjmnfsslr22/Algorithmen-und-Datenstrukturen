#include "sorting.h"
//Insertion sort für kleinere

namespace sorting 
{
	//************
	// QuickSort *
	//************  
	//Worst Case O(n^2)
	//Best Case O(n*lg n)

	void QuickSort(vector<int> &arr, int left, int right) {
		
		//***************************
		// implement quicksort here *
		//************ **************
		if (left < right)
		{
			int pivot = partition(arr, left, right);
			QuickSort(arr, left, pivot - 1);
			QuickSort(arr, pivot + 1, right);
		}

	}

	int partition(vector<int> &arr, int left, int right)
	{
		int pivot = arr[right];
		int i = left - 1;
		for (int j = left; j <= right - 1; j++)
		{
			if (arr[j] <= pivot)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[right]);
		return i + 1;
	}

	//************
	// MergeSort *
	//************
	// Worst case O(n*lg n)

	//***************************
	// implement mergesort here *
	//***************************
	void Merge(vector<int> &mergeVector, vector<int> &tmpVector, int low, int mid, int high) 
	{
		int tmp_low = low;
		int tmp_index = low;
		int tmp_high = mid + 1;
		int main_index;

		while ((tmp_low <= mid) && (tmp_high <= high))
		{
			if (mergeVector[tmp_low] <= mergeVector[tmp_high])
			{
				tmpVector[tmp_index] = mergeVector[tmp_low];
				tmp_low++;
			}
			else
			{
				// Vergleich der einzelnen Teile des Vektors dann Tauschen
				tmpVector[tmp_index] = mergeVector[tmp_high];
				tmp_high++;
			}
			tmp_index++;
		}

		if (tmp_low > mid)
		{
			// Element an Richtige Stelle setzen für tmp_low > mid
			for (main_index = tmp_high; main_index <= high; main_index++)
			{
				tmpVector[tmp_index] = mergeVector[main_index];
				tmp_index++;
			}
		}
		else
		{
			// Element an Richtige Stelle setzen für tmp_low < mid
			for (main_index = tmp_low; main_index <= mid; main_index++)
			{
				tmpVector[tmp_index] = mergeVector[main_index];
				tmp_index++;
			}
		}

		// Vectoren zusammenfügen
		for (main_index = low; main_index <= high; main_index++)
		{
			mergeVector[main_index] = tmpVector[main_index];
		}
	}

	void MergeSort(vector<int> &sortVector, vector<int> &tmpVector, int low, int high)
	{
		if (low < high)
		{
			// In 2 hälften unterteilen
			int mitte = low + (high - low) / 2;

			// Erste und 2. Hälfte Sortieren
			MergeSort(sortVector,tmpVector, low, mitte);
			MergeSort(sortVector,tmpVector, mitte + 1, high);
			//Listen Zusammenführen
			Merge(sortVector,tmpVector, low, mitte, high);
		}
	}
	//************
	// Heapsort  *
	//************
	// O(n*lg n)
	void HeapSort(vector<int> &arr, int n)
	{
			//***************************
			// implement heapsort here *
			//***************************

		// Heap aufbauen
		for (int i = n / 2 - 1; i >= 0; i--)
		{
			percDown(arr, n, i);
		}

		// Tauschen von 2 Elementen 
		for (int i = n - 1; i > 0; i--)
		{
			// Wurzel ans ende 
			swap(arr[0], arr[i]);

			// Max Heap erstellen für verkleinerten Heap 
			percDown(arr, i, 0);
		}
	}

	void percDown(vector<int> &arr, int n, int i)
	{
		int largest = i; // Rechtes ELement als grösstes 
		int left = 2 * i + 1; // left = 2*i + 1 
		int right = 2 * i + 2; // right = 2*i + 2 

		// Linker Nachfolger ist groesser  
		if (left < n && arr[left] > arr[largest])
		{
			largest = left;
		}

		// Rechter Nachfolger ist groesser 
		if (right < n && arr[right] > arr[largest])
		{
			largest = right;
		}

		// Wenn die Wurzel nicht das groesste Element ist 
		if (largest != i)
		{
			swap(arr[i], arr[largest]);

			// Wieder Max Heap erstellen
			percDown(arr, n, largest);
		}
	}

	//************
	// Shellsort *
	//************
	// Laufzeit =(n^1.25) mit Hibbard Folge

	void ShellSort(vector<int> &a, int n)
	{
		//***************************
		// implement shellsort here *
		//***************************

		for (int abstand = n; abstand > 0; abstand  = ((abstand-1)/2))
		{
			for (int i = abstand; i < n; i++)
			{
				int tmp = a[i];
				int j = i;
				for (; j >= abstand && tmp < a[j - abstand]; j -= abstand)
				{
					a[j] = a[j - abstand];
				}
				a[j] = tmp;
			}
		}

	}
	



  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





