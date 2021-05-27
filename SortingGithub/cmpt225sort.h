#pragma once

//*******************
//INSERTION-SORT
//*******************
//source: class notes(Simple sorting presentation: slide 16)

/*
 * template function that takes in a template array and it's size,
 * sorts the array using insertion sort algorithm, returns the
 * barometer count
 */
template<class T>
int insertionsort(T arr[], int size){
    int barometerCount = 0;
    for(int i = 0; i < size; i++){
        T temp = arr[i];
        int position = i;
        while(position > 0 && arr[position - 1] > temp){
            arr[position] = arr[position - 1];
            position--;
            barometerCount++;
        }
        arr[position] = temp;
    }
    return barometerCount;
}



//*******************
//QUICK-SORT
//*******************
// source: class notes (Quicksort presentation: slide 19)


//takes in a template array as parameter, swaps the values at the positions parameters
template<class T>
void swap(T arr[], int pos1, int pos2){
    T temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

/*
 * template function that partitions an array, compares indices
 * and swaps the value at low index if value is greater than partition index value.
 * Searches for a high index whose value is less than partition index value. Swaps low
 * with high value. When low index = high index, the partition index value swaps with low
 */
template<class T>
int partition(T arr[], int low, int high, int& barometerCount){
    int pivot = high;                        //sets pivot point index
    while(low != high){
        barometerCount++;
        if(arr[low] > arr[pivot]){          //if low index value > pivot value, need to do a swap
            if(arr[pivot] > arr[high]){     //checks high index, if high index is greater than pivot, swap
                swap(arr, low, high);
                low++;
            }else{
                high--;        //decrements high and iterates to next version of loop until high < pivot index found
            }
        }else{
            low++;
        }
    }
    swap(arr, low, pivot);
    pivot = low;
    return pivot;
}

/*
 * template function that uses recursion to split array parameter into
 * smaller sub-arrays until array is sorted
 */
template<class T>
void quicksortAid(T arr[], int low, int high, int& barometerCount){
    if(low < high){
        int pivot = partition(arr, low, high, barometerCount);
        quicksortAid(arr, low, pivot - 1, barometerCount);
        quicksortAid(arr, pivot + 1, high, barometerCount);
    }
}

/*
 * template function that takes in a template array and it's size,
 * runs the quicksort algorithm by calling helper function and returns
 * the barometer count
 */
template<class T>
int quicksort(T arr[], int size){
    int barometerCount = 0;
    quicksortAid(arr, 0, size - 1, barometerCount);
    return barometerCount;
}


//*******************
//MERGE-SORT
//*******************
//source: https://www.geeksforgeeks.org/iterative-merge-sort/

/*
 * template function that controls the portion of the array being sorted.
 * Splits array into sub-arrays and compares values, overwrites original array.
 * Results in a sorted portion of the array.
 */
template<class T>
void merge(T arr[], int beginning, int middle, int end, int& barometerCount){
    //determines size of sub-arrays
    int sizeOfFirstSubArr = middle - beginning + 1;
    int sizeOfSecondSubArr = end - middle;

    //creates the sub-arrays
    T firstSubArr[sizeOfFirstSubArr];
    T secondSubArr[sizeOfSecondSubArr];

    for(int i = 0; i < sizeOfFirstSubArr; i++){         //copies elements to the first sub-array
        firstSubArr[i] = arr[beginning + i];
    }

    for(int i = 0; i < sizeOfSecondSubArr; i++){        //copies elements to the second sub-array
        secondSubArr[i] = arr[(middle + 1) + i];
    }

    //inserts values into the actual array based on comparing the sub-array indices
    int firstSubArrayIndex = 0;
    int secondSubArrayIndex = 0;
    int trueArrayIndex = beginning;

    while((firstSubArrayIndex < sizeOfFirstSubArr) && (secondSubArrayIndex < sizeOfSecondSubArr)){
        barometerCount++;
        if(firstSubArr[firstSubArrayIndex] <= secondSubArr[secondSubArrayIndex]){
            arr[trueArrayIndex] = firstSubArr[firstSubArrayIndex];
            firstSubArrayIndex++;
        }else{
            arr[trueArrayIndex] = secondSubArr[secondSubArrayIndex];
            secondSubArrayIndex++;
        }
        trueArrayIndex++;
    }

    //copies remaining contents over to the main array
    while(firstSubArrayIndex < sizeOfFirstSubArr || secondSubArrayIndex < sizeOfSecondSubArr){
        if(firstSubArrayIndex < sizeOfFirstSubArr){
            arr[trueArrayIndex] = firstSubArr[firstSubArrayIndex];
            firstSubArrayIndex++;
            trueArrayIndex++;
        }
        if(secondSubArrayIndex < sizeOfSecondSubArr){
            arr[trueArrayIndex] = secondSubArr[secondSubArrayIndex];
            secondSubArrayIndex++;
            trueArrayIndex++;
        }
    }
}


//returns the lower number of two parameters
int minimumValue(int value1, int value2){
    if(value1 < value2){
        return value1;
    }else{
        return value2;
    }
}

/*
 * uses indices to control the array portions being sorted, passes index variables
 * into merge function to perform the sorting
 */
template<class T>
void mergesortAid(T arr[], int size, int& barometerCount){
    for(int currentSize = 1; currentSize < size; currentSize *= 2){
        for(int beginning = 0; beginning < (size - 1); beginning += 2 * currentSize){
            int middle = minimumValue(beginning + currentSize - 1, size - 1);
            int end = minimumValue(beginning + (2 * currentSize) - 1, size - 1);
            merge(arr, beginning, middle, end, barometerCount);
        }
    }
}

/*
 * template function that takes in a template array and it's size,
 * performs the mergesort algorithm by calling helper function,
 * returns the barometer count
 */
template<class T>
int mergesort(T arr[], int size){
    int barometerCount = 0;
    mergesortAid(arr, size, barometerCount);
    return barometerCount;
}


//******************
//SHELL-SORT
//******************
//source: https://www.geeksforgeeks.org/shellsort/
//source: https://www.youtube.com/watch?v=ddeLSDsYVp8

/*
 * template function that takes in a template array and it's size,
 * performs the shellsort algorithm and returns its barometer count
 */
template<class T>
int shellsort(T arr[], int size){
    int barometerCount = 0;
    for(int gap = size / 2; gap > 0; gap = gap / 2){    //outer for-loop creates gap and divides the gap in half on each iteration
        for(int i = gap; i < size; i++){
            T temp = arr[i];
            barometerCount++;
            int index = 0;

            /* if value value at beginning of gap > value at end of gap, swaps values,
             * when gap size = 1, regular insertion sort takes place */
            for(index = i; index >= gap && arr[index - gap] > temp; index = index - gap){
                arr[index] = arr[index - gap];
            }
            arr[index] = temp;
        }
    }
    return barometerCount;
}