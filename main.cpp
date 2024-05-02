#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::swap;
using std::sort;

using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; // clock per milliseconds

const int NUMBERS_SIZE = 50000;

// random number in range -> for test code
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// fill arrays -> for test code
void fillArrays(int arr1[], int arr2[],int arr3[]) {
  for(int i = 0; i < NUMBERS_SIZE; ++i){
    arr1[i] = genRandInt(0,NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

// helper for quicksorts
int QPartition(int numbers[], int low, int high, int pivotIndex) {
  int pivot = numbers[pivotIndex];
  while (true) {  // continuously loops until fin is true
    // until reaches element left of pivot that is greater than pivot value
    while (numbers[low] < pivot) { ++low; }
    // until reaches element right of pivot that is less than pivot value
    while (pivot < numbers[high]) { --high; }
    if (low >= high) break;  // checks if there are unsorted elements
    // if continues, low index is still less than high index
    swap(numbers[low], numbers[high]);
    ++low;
    --high;
  }
  return high;
}

// sorts given array in range using quicksort method, recursive
void Quicksort_midpoint(int numbers[], int low, int high) {
  if (low >= high) return;  // already sorted
  int mid = (high - low) / 2 + low;
  mid = QPartition(numbers, low, high, mid);  // call helper
  Quicksort_midpoint(numbers, low, mid);  // left half recursive call
  Quicksort_midpoint(numbers, mid + 1, high); // right half recursive call
}

// sort given array in range using quicksort method, but chooses pivot by
// choosing middle value of low, middle, and high indexes, recursive
void Quicksort_medianOfThree(int numbers[], int low, int high) {
  if (low >= high) return;  // already sorted
  int mid = (high - low) / 2 + low;
  int pivot = mid;  // element at mid is pivot by default
  // element at lowest index is middle value
  if ((numbers[mid] < numbers[low] && numbers[low] < numbers[high]) ||
      (numbers[high] < numbers[low] && numbers[low] < numbers[mid])) pivot = low;
  // element at highest index is middle value
  if ((numbers[mid] < numbers[high] && numbers[high] < numbers[low]) ||
      (numbers[low] < numbers[high] && numbers[high] < numbers[mid])) pivot = high;
  mid = QPartition(numbers, low, high, pivot);  // call helper
  Quicksort_medianOfThree(numbers, low, mid); // left half recursive call
  Quicksort_medianOfThree(numbers, mid + 1, high);  // right half recursive call
}

// sorts given array using insertion sort method
void InsertionSort(int numbers[], int numbersSize) {
  for (int i = 1; i < numbersSize; ++i) { // sorts every element in array
    int j = i;
    // shifts element left to correct spot
    while (j > 0 && numbers[j] < numbers[j - 1]) {
      swap(numbers[j], numbers[j - 1]);
      --j;
    }
  }
}

// helper, returns true if sorted, else false
static bool is_sorted(int numbers[], int numbersSize) {
  if (numbersSize <= 0) return true;  // will be sorted if empty
  int last = numbers[0];
  for(int i=0; i < numbersSize; ++i) {  // checks all elements
    int curr = numbers[i];
    if (curr < last) return false;  // prev value is greater than curr -> not sorted properly
    last = curr;
  }
  return true;
}

// put vector in array after randomizing in main
static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for(int i=0;i<static_cast<int>(source.size()); ++i) { // iterate through vector
    array[i] = source[i];
  }
}

int main() {
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  // randomize array
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  
  // run tests across different sizes
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for(int i=0; i<4; ++i) {  // loops for four different sizes
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      Quicksort_midpoint(test_array, 0, size - 1);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms" << endl;
      cout << "Quicksort midpoint is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // QUICKSORT MEDIAN OF THREE SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      Quicksort_medianOfThree(test_array, 0, size - 1);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms" << endl;
      cout << "Quicksort median of three is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // INSERTION SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      InsertionSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms" << endl;
      cout << "Insertion sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
  }
 
  return 0;
}