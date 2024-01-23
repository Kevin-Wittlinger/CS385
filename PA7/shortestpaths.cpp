/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Kevin Wittlinger
 * Date        : 12/04/2023
 * Description : solve the all pairs shortest paths problem with Floyd’s algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdio.h>

using namespace std;

const long INF = numeric_limits<long>::max();

// counts digits in a num
int len(long num)
{
    int count = 1;
    while (num >= 10)
    {
        num = num / 10;
        count++;
    }
    return count;
}

// finds the path of two vertices
void path(vector<vector<long>> &matrix, int i, int j)
{
    if (matrix[i][j] == INF)
    {
        cout << char(i + 'A') << " -> " << char(j + 'A');
        return;
    }

    long intermediate = matrix[i][j];

    if (matrix[i][intermediate] == INF && matrix[intermediate][j] == INF)
    {
        cout << char(i + 'A') << " -> " << char(intermediate + 'A') << " -> " << char(j + 'A');
    }
    else
    {
        if (matrix[i][intermediate] == INF)
        {
            cout << char(i + 'A') << " -> ";
            path(matrix, intermediate, j);
        }
        else if (matrix[intermediate][j] == INF)
        {
            path(matrix, i, intermediate);
            cout << " -> " << char(j + 'A');
        }
        else
        {
            path(matrix, i, intermediate);
            cout << " -> ";
            path(matrix, intermediate, j);
        }
    }
}

/**
 * Displays the matrix on the screen formatted as a table.
 */
void display_table(vector<vector<long>> &matrix, const string &label, const bool use_letters = false)
{
    cout << label << endl;
    long max_val = 0;

    for (const auto &row : matrix)
    {
        for (long cell : row)
        {
            if (cell < INF && cell > max_val)
            {
                max_val = cell;
            }
        }
    }

    int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(matrix.size()), max_val));
    cout << ' ';

    for (size_t j = 0; j < matrix.size(); j++)
    {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }

    cout << endl;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        cout << static_cast<char>(i + 'A');
        for (size_t k = 0; k < matrix[0].size(); k++)
        {
            cout << " " << setw(max_cell_width);

            if (matrix[i][k] == INF)
            {
                cout << "-";
            }
            else if (use_letters)
            {
                cout << static_cast<char>(matrix[i][k] + 'A');
            }
            else
            {
                cout << matrix[i][k];
            }
        }
        cout << endl;
    }

    cout << endl;
}

// main function
int main(int argc, const char *argv[])
{

    vector<vector<long>> distance;
    // Make sure the right number of command line arguments exist.
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file)
    {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try
    {
        unsigned int line_number = 1;
        int vertex_count = 0;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line))
        {
            if (line_number == 1)
            {
                try
                {
                    if (stoi(line) < 1 || stoi(line) > 26)
                    {
                        cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                        return 1;
                    }
                    vertex_count = stoi(line);
                }
                catch (exception &err)
                {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return 1;
                }
                distance.resize(vertex_count);
                for (int i = 0; i < vertex_count; i++)
                {
                    distance[i] = vector<long>(vertex_count);
                }
            }
            else
            {
                stringstream ss(line);
                string s;

                int component_count = 0;
                int first;
                int second;
                int weight;

                while (getline(ss, s, ' '))
                {
                    // first
                    try
                    {
                        if (component_count == 0 && (s.length() != 1 || s[0] < 65 || s[0] > 65 + vertex_count - 1))
                        {
                            cerr << "Error: Starting vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count - 1) << "." << endl;
                            return 1;
                        }
                    }
                    catch (exception &err)
                    {
                        cerr << "Error: Starting vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count - 1) << "." << endl;
                        return 1;
                    }
                    // second
                    try
                    {
                        if (component_count == 1 && (s.length() != 1 || s[0] < 65 || s[0] > 65 + vertex_count - 1))
                        {
                            cerr << "Error: Ending vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count - 1) << "." << endl;
                            return 1;
                        }
                    }
                    catch (exception &err)
                    {
                        cerr << "Error: Ending vertex '" << s << "' on line " << line_number << " is not among valid values A-" << (char)(65 + vertex_count - 1) << "." << endl;
                        return 1;
                    }
                    // third
                    try
                    {
                        if (component_count == 2 && stoi(s) < 1)
                        {
                            cerr << "Error: Invalid edge weight '" << s << "' on line " << line_number << "." << endl;
                            return 1;
                        }
                    }
                    catch (exception &err)
                    {
                        cerr << "Error: Invalid edge weight '" << s << "' on line " << line_number << "." << endl;
                        return 1;
                    }
                    if (component_count == 0)
                    {
                        first = int(s[0]);
                    }
                    else if (component_count == 1)
                    {
                        second = int(s[0]);
                    }
                    else if (component_count == 2)
                    {
                        weight = stoi(s);
                    }

                    component_count++;
                }

                if (component_count != 3)
                {
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                int row = first - 65;
                int col = second - 65;
                distance[row][col] = weight;
            }
            line_number++;
        }
        // Don't forget to close the file.
        input_file.close();
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    long vertex_count = distance.size();

    for (int i = 0; i < vertex_count; i++)
    {
        for (int k = 0; k < vertex_count; k++)
        {
            if (i != k && distance[i][k] == 0)
                distance[i][k] = INF;
        }
    }

    for (int i = 0; i < vertex_count; i++)
    {
        for (int k = 0; k < vertex_count; k++)
        {
            if (i != k && distance[i][k] == 0)
            {
                distance[i][k] = INF;
            }
        }
    }

    vector<vector<long>> path_matrix(vertex_count, vector<long>(vertex_count));
    vector<vector<long>> intermediate_matrix(vertex_count, vector<long>(vertex_count, INF));

    for (int i = 0; i < vertex_count; i++)
    {
        for (int k = 0; k < vertex_count; k++)
        {
            path_matrix[i][k] = distance[i][k];
            intermediate_matrix[i][k] = INF;
        }
    }

    for (int i = 0; i < vertex_count; ++i)
    {
        for (int k = 0; k < vertex_count; ++k)
        {
            for (int j = 0; j < vertex_count; ++j)
            {
                if (path_matrix[k][i] != INF && path_matrix[i][j] != INF)
                {
                    long final = path_matrix[k][i] + path_matrix[i][j];

                    if (final < path_matrix[k][j])
                    {
                        path_matrix[k][j] = final;
                        intermediate_matrix[k][j] = i;
                    }
                }
            }
        }
    }

    display_table(distance, "Distance matrix:", false);
    display_table(path_matrix, "Path lengths:", false);
    display_table(intermediate_matrix, "Intermediate vertices:", true);

    for (int i = 0; i < vertex_count; i++)
    {
        for (int k = 0; k < vertex_count; k++)
        {
            long distance = path_matrix[i][k];
            char ver1 = 65 + i;
            char ver2 = 65 + k;

            if (distance != INF)
            {
                cout << ver1 << " -> " << ver2 << ", distance: " << distance << ", path: ";

                if (i == k)
                {
                    cout << ver1 << endl;
                    continue;
                }

                if (intermediate_matrix[i][k] == INF)
                {
                    cout << ver1 << " -> " << ver2 << endl;
                    continue;
                }

                path(intermediate_matrix, i, k);
                cout << endl;
            }
            else
            {
                cout << ver1 << " -> " << ver2 << ", distance: infinity, path: none" << endl;
            }
        }
    }
    return 0;
}
