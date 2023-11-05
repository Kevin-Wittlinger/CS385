/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Kevin Wittlinger
 * Version     : 1.0
 * Date        : 11/4/2023
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length)
{
    // TODO
    // for slow tests
    long count = 0;
    // loop goes over every part of the arrays length
    for (int i = 0; i < length; i++)
    {
        // compare with all elements after the first
        for (int j = i + 1; j < length; j++)
        {
            // if i is > j then there is an inversion
            if (array[i] > array[j])
            {
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length)
{
    // TODO
    // Hint: Use mergesort!
    // for fast tests
    int *scratch = new int[length]();                      // Makes a temporary storage for the sort
    long count = mergesort(array, scratch, 0, length - 1); // calls mergesort
    delete[] scratch;                                      // deletes to save memory
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high)
{
    // TODO
    long count = 0;
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        count += mergesort(array, scratch, low, mid);      // sort left half
        count += mergesort(array, scratch, mid + 1, high); // sort right half

        int low1 = low;
        int high1 = mid + 1;

        // merge the two sorted halfs
        for (int i = low; i <= high; i++)
        {
            if (low1 <= mid && (high1 > high || array[low1] <= array[high1]))
            {
                scratch[i] = array[low1];
                low1++;
            }
            else
            {
                scratch[i] = array[high1];
                high1++;
                count += (mid - low1 + 1);
            }
        }
        // copy the new array back to the original
        for (int k = low; k <= high; k++)
        {
            array[k] = scratch[k];
        }
    }
    return count; // returns cout (number of inversions)
}

int main(int argc, char *argv[])
{
    // TODO: parse command-line argument
    bool slow = false;

    if (argc != 1 && argc != 2)
    {
        cout << "Usage: ./inversioncounter [slow]" << flush;
        return 1;
    }

    else if (argc == 2)
    {
        string speed = argv[1];
        if (speed == "slow")
        {
            slow = true;
        }
        else
        {
            cout << "Error: Unrecognized option '" << speed << "'." << endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true)
    {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln)
        {
            if (str.length() > 0)
            {
                iss.str(str);
                if (iss >> value)
                {
                    values.push_back(value);
                }
                else
                {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln)
            {
                break;
            }
            str.clear();
        }
        else
        {
            str += c;
        }
    }

    // TODO: produce output
    if (values.empty())
    {
        cout << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    else if (slow)
    {
        cout << "Number of inversions (slow): " << count_inversions_slow(values.data(), values.size()) << endl;
    }
    else
    {
        cout << "Number of inversions (fast): " << count_inversions_fast(values.data(), values.size()) << endl;
    }

    return 0;
}
