#include <iostream>
#include <string>
#include <fstream>
#include "cmpt225sort.h"

using namespace std;

// PARAM: infile = name of the file to be opened
//        n = the size of the result array
// PRE: the file contains values separated by white space
// POST: returns an array containing the contents of infile
template <class T>
T* readFile(string infile, int & n)
{
    T* result;
    T next;
    n = 0;

    ifstream ist(infile.c_str()); // open file
    // Check if file opened correctly
    if (ist.fail()) {
        throw runtime_error(infile + " not found");
    }

    // Find file size
    while (ist >> next) {
        n++;
    }

    // Read file into array
    ist.close();
    ist.open(infile.c_str());
    result = new T[n];
    for (int i = 0; i < n; ++i) {
        ist >> result[i];
    }

    ist.close();
    return result;
}


void profTest(){
    int n = 0;
    int* arr1 = readFile<int>("a3test1.txt", n);
    cout << "insertion sort comparisons = " << insertionsort<int>(arr1, n) << endl;
    float* arr2 = readFile<float>("a3test2.txt", n);
    cout << "quicksort comparisons = " << quicksort<float>(arr2, n) << endl;
    string* arr3 = readFile<string>("a3test3.txt", n);
    cout << "mergesort comparisons = " << mergesort<string>(arr3, n) << endl;
    cout << "shell sort comparisons = " << shellsort(arr3, n) << endl;
}


//test descending order, 10 values
void test1(){
    int test1[] = {10, 9, 8 , 7, 6, 5, 4, 3, 2, 1};
    int test2[] = {10, 9, 8 , 7, 6, 5, 4, 3, 2, 1};
    int test3[] = {10, 9, 8 , 7, 6, 5, 4, 3, 2, 1};
    int test4[] = {10, 9, 8 , 7, 6, 5, 4, 3, 2, 1};

    assert(insertionsort(test1, 10) == 45);
    assert(quicksort(test2, 10) == 45);
    assert(mergesort(test3, 10) == 15);
    assert(shellsort(test4, 10) == 22);

    cout << "... all test1 passed" << endl;
}

//tests ascending order, already sorted
void test2(){
    int test1[] = {1, 2, 3, 4, 5};
    int test2[] = {1, 2, 3, 4, 5};
    int test3[] = {1, 2, 3, 4, 5};
    int test4[] = {1, 2, 3, 4, 5};

    assert(insertionsort(test1, 5) == 0);
    assert(quicksort(test2, 5) == 10);
    assert(mergesort(test3, 5) == 8);
    assert(shellsort(test4, 5) == 7);

    cout << "... all test2 passed" << endl;
}


//tests empty arrays
void test3(){
    int test1[] = {};
    int test2[] = {};
    int test3[] = {};
    int test4[] = {};

    assert(insertionsort(test1, 0) == 0);
    assert(quicksort(test2, 0) == 0);
    assert(mergesort(test3, 0) == 0);
    assert(shellsort(test4, 0) == 0);

    cout << "... all test3 passed" << endl;
}

void test4(){
    int test1[] = {-1, 7, 5, 8, -9, 24, 60, -54, 2, 6};
    int test2[] = {-1, 7, 5, 8, -9, 24, 60, -54, 2, 6};
    int test3[] = {-1, 7, 5, 8, -9, 24, 60, -54, 2, 6};
    int test4[] = {-1, 7, 5, 8, -9, 24, 60, -54, 2, 6};

    assert(insertionsort(test1, 10) == 21);
    assert(quicksort(test2, 10) == 19);
    assert(mergesort(test3, 10) == 23);
    assert(shellsort(test4, 10) == 22);

    cout << "... all test4 passed" << endl;
}


//tests doubles, negatives and positives
void test5(){
    double test1[] = {-1.06, 7.23, -5.4578, 8.342, -9.8754, 2.4, 60.54, -54.0007, 2.32, 6.24};
    double test2[] = {-1.06, 7.23, -5.4578, 8.342, -9.8754, 2.4, 60.54, -54.0007, 2.32, 6.24};
    double test3[] = {-1.06, 7.23, -5.4578, 8.342, -9.8754, 2.4, 60.54, -54.0007, 2.32, 6.24};
    double test4[] = {-1.06, 7.23, -5.4578, 8.342, -9.8754, 2.4, 60.54, -54.0007, 2.32, 6.24};

    assert(insertionsort(test1, 10) == 22);
    assert(quicksort(test2, 10) == 24);
    assert(mergesort(test3, 10) == 25);
    assert(shellsort(test4, 10) == 22);

    cout << "... all test5 passed" << endl;
}

void test6(){
    string test1[] = {"Michael", "Brandon", "Ashley", "Brian", "Chris", "Pam", "Nida", "John"};
    string test2[] = {"Michael", "Brandon", "Ashley", "Brian", "Chris", "Pam", "Nida", "John"};
    string test3[] = {"Michael", "Brandon", "Ashley", "Brian", "Chris", "Pam", "Nida", "John"};
    string test4[] = {"Michael", "Brandon", "Ashley", "Brian", "Chris", "Pam", "Nida", "John"};

    assert(insertionsort(test1, 8) == 9);
    assert(quicksort(test2, 8) == 14);
    assert(mergesort(test3, 8) == 16);
    assert(shellsort(test4, 8) == 17);

    cout << "... all test6 passed" << endl;
}

void test7(){
    int arr[1000];
    for(int i = 0; i < 1000; i++){
        arr[i] = 1000 - i;
    }
    assert(quicksort(arr, 1000) == 499500);
    cout << "... all test7 passed" << endl;
}

void test8(){
    int arr[] = {-10, 8, 23, 4, 7, 77, 44, 213, 321, 8097, 24};
    assert(quicksort(arr, 11) == 23);
    cout << "... all test8 passed" << endl;
}



template<class T>
void printArr(T arr[], int size){
    cout << "{";
    cout << arr[0];
    for(int i = 1; i < size; i++){
        cout << ", " << arr[i];
    }
    cout << "}" << endl;
}


int main() {
    profTest();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();

    return 0;
}
