// Sophia Therese Bondoc, Abby Crowley, & Abigail Kim
// Lab 5, ECE 2161-001
// Menu-driven program that reads numbers from a file, sorts them with six
// different algorithms, and reports the CPU time each sort takes.

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "AbbyC.h"      // selectionSort, quickSort
#include "AbbyK.h"      // bubbleSort, mergeSort
#include "Sophia.h"     // insertionSort, shellSort
using namespace std;

const int MaxSize = 2100000;

// Prints the main menu.
void printMenu()
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
int readData(const string& filename, long data[])
{
    ifstream in(filename.c_str());
    if (!in)
    {
        cout << "Could not open " << filename << endl;
        return 0;
    }
    int count = 0;
    while (count < MaxSize && in >> data[count])
        count++;
    in.close();
    return count;
}

// Writes the first n values of data[] to the output file, one per line.
void writeData(const string& filename, const long data[], int n)
{
    ofstream out(filename.c_str());
    for (int i = 0; i < n; i++)
        out << data[i] << "\n";
    out.close();
}

// Wrapper so quick sort can be called like the others. If your teammate's
// quickSort is declared as quickSort(long[], int n), call it directly instead.
void runQuick(long a[], int n)
{
    quickSort(a, 0, n - 1);
}

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

    writeData(outFile, work, n);
    cout << "Sorted data saved to " << outFile << endl;
}

int main()
{
    // Heap allocation, so no "ulimit -s" change is needed
    long* original = new long[MaxSize];
    long* work = new long[MaxSize];
    int n = 0;                 // number of items loaded
    int choice = -1;

    while (choice != 0)
    {
        printMenu();
        cin >> choice;

        // Sorting options need data loaded first
        if (choice >= 2 && choice <= 7 && n == 0)
        {
            cout << "Please read the data first (option 1).\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            n = readData("lab5_input.txt", original);
            cout << n << " items read.\n";
            break;
        case 2:
            timeSort(insertionSort, "Insertion Sort", "lab5_Insertion_out.txt", original, work, n);
            break;
        case 3:
            timeSort(selectionSort, "Selection Sort", "lab5_Selection_out.txt", original, work, n);
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
