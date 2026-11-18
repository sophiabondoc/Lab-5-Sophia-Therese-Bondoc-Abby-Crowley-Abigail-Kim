// Sophia Therese Bondoc, Abby Crowley, & Abigail Kim
// Lab 5, ECE 2161-001
// Menu-driven program that reads numbers from a file, sorts them with six
// different algorithms, and reports the CPU time each sort takes.

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "AbbyC.h"      // bubbleSort, mergeSort
#include "AbbyK.h"      // selectionSort, quickSort
#include "Sophia.h"     // insertionSort, shellSort
using namespace std;

const int MaxItems = 2100000;

// Prints the main menu.
void showMenu()
{
    cout << "\n(1) Read Data from input file\n";
    cout << "(2) Sort Data using Insertion Sort\n";
    cout << "(3) Sort Data using Selection Sort\n";
    cout << "(4) Sort Data using Bubble Sort\n";
    cout << "(5) Sort Data using Shell Sort\n";
    cout << "(6) Sort Data using Quick Sort\n";
    cout << "(7) Sort Data using Merge Sort\n";
    cout << "(0) Exit\n";
    cout << "Enter choice: ";
}

// Reads numbers from the file into data[]. Returns how many were read.
int loadData(const string& filename, long data[])
{
    ifstream in(filename.c_str());
    if (!in)
    {
        cout << "Could not open " << filename << endl;
        return 0;
    }
    int count = 0;
    while (count < MaxItems && in >> data[count])
        count++;
    in.close();
    return count;
}

// Writes the first n values of data[] to the output file, one per line.
void saveData(const string& filename, const long data[], int n)
{
    ofstream out(filename.c_str());
    for (int i = 0; i < n; i++)
        out << data[i] << "\n";
    out.close();
}

// Returns true if data[0..n-1] is in increasing order.
bool isSorted(const long data[], int n)
{
    for (int i = 1; i < n; i++)
        if (data[i - 1] > data[i])
            return false;
    return true;
}

// Wrappers so every sort has the same form: void sort(long[], int).
void runSelection(long a[], int n) { selectionSort(a, n); }
void runQuick(long a[], int n)     { quickSort(a, 0, n - 1); }

// Copies the original data, times the sort on the copy, reports CPU time
// in seconds, and saves the sorted result to an output file.
void timeSort(void (*sortFunc)(long[], int), const string& name,
              const string& outFile, const long original[], long work[], int n)
{
    for (int i = 0; i < n; i++)
        work[i] = original[i];            // fresh unsorted copy

    double begin_time = clock();
    sortFunc(work, n);
    double end_time = clock();

    double cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
    cout << name << " finished in " << cpu_time_used << " seconds\n";
    cout << (isSorted(work, n) ? "Result verified sorted.\n"
                               : "WARNING: result is NOT sorted!\n");

    saveData(outFile, work, n);
    cout << "Sorted data saved to " << outFile << endl;
}

int main()
{
    // Heap allocation avoids the 8 MB stack limit
    long* original = new long[MaxItems];
    long* work = new long[MaxItems];
    int n = 0;                 // number of items loaded
    int choice = -1;

    while (choice != 0)
    {
        showMenu();
        if (!(cin >> choice))   // stop if input is not a number
            break;

        if (choice >= 2 && choice <= 7 && n == 0)
        {
            cout << "Please read the data first (option 1).\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            n = loadData("lab5_input.txt", original);
            cout << n << " items read.\n";
            break;
        case 2:
            timeSort(insertionSort, "Insertion Sort", "lab5_Insertion_out.txt", original, work, n);
            break;
        case 3:
            timeSort(runSelection, "Selection Sort", "lab5_Selection_out.txt", original, work, n);
            break;
        case 4:
            timeSort(bubbleSort, "Bubble Sort", "lab5_Bubble_out.txt", original, work, n);
            break;
        case 5:
            timeSort(shellSort, "Shell Sort", "lab5_Shell_out.txt", original, work, n);
            break;
        case 6:
            timeSort(runQuick, "Quick Sort", "lab5_Quick_out.txt", original, work, n);
            break;
        case 7:
            timeSort(mergeSort, "Merge Sort", "lab5_Merge_out.txt", original, work, n);
            break;
        case 0:
            cout << "Goodbye.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    delete[] original;
    delete[] work;
    return 0;
}
