/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Kevin Wittlinger
 * Date        : 10/07/2023
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> get_ways(int num_stairs)
{
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    // vector stores combination of ways to climb stairs
    vector<vector<int>> comb_ways;
    // vector stores iterative ways of recursive call
    vector<vector<int>> ways;
    // vector representing a single way you climb stairs
    vector<int> single;

    // base case
    if (num_stairs <= 0)
    {
        comb_ways.push_back(single);
    }
    else
    {
        // Loop through 3 steps
        for (int i = 1; i <= 3; i++)
        {
            // checks if you are able to take a step
            // then will recursivly check for remaining stairs
            if (num_stairs >= i)
            {
                ways = get_ways(num_stairs - i);

                // Iterates through each way in ways
                for (const vector<int> &way : ways)
                {
                    // copy of way vector
                    vector<int> new_way = way;
                    // i is inserted into beggining of new_way
                    new_way.insert(new_way.begin(), i);
                    // adds new_way to the end of comb_ways
                    comb_ways.push_back(new_way);
                }
            }
        }
    }
    // returns the ways to climb the stairs
    return comb_ways;
}

void display_ways(const vector<vector<int>> &ways)
{
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    // total number of ways
    int total_ways = ways.size();
    // length for printing
    int length = 0;

    // figure out the length you need to print the stair
    while (total_ways > 0)
    {
        total_ways /= 10;
        length++;
    }

    // iterate through each way and print it given the cases on the doc
    for (size_t i = 0; i < ways.size(); i++)
    {
        cout << setw(length) << i + 1 << ". [";
        // iterate through each step in way and print matching the cases
        for (size_t j = 0; j < ways[i].size(); j++)
        {
            cout << ways[i][j];
            if (j < ways[i].size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char *const argv[])
{
    // makes stringstream
    istringstream iss;

    // ensures correct arguments are provided returns an error code
    if (argc != 2)
    {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    // sets string strean with command line
    iss.str(argv[1]);
    // var stairs will store # of stairs
    int stairs = 0;

    // check if positive integer has been provided returns error
    if (!(iss >> stairs) || stairs < 1)
    {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    // marks num_ways as the number of ways discussed previously
    vector<vector<int>> num_ways = get_ways(stairs);
    // Prints the number of ways to climb the stairs
    cout << num_ways.size() << " way" << (num_ways.size() == 1 ? "" : "s") << " to climb " << stairs << " stair" << (stairs == 1 ? "" : "s") << "." << endl;
    display_ways(num_ways);

    // returns that everything is good
    return 0;
}