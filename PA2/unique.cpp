/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Kevin Wittlinger
 * Date        : 9/30/2023
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s)
{
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    // Checks if given is empty
    if (s.empty())
    {
        return true;
    }
    // loops through each character in the given
    for (size_t i = 0; i < s.length(); i++)
    {
        // Checks if the list doesn't contain regular english alphabet
        if (!isalpha(s[i]))
        {
            return false;
        }
        // Checks if the char is uppercase
        if (isupper(s[i]))
        {
            return false;
        }
    }
    // returns true when all lower case
    return true;
}

bool all_unique_letters(const string &s)
{
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    // checks if the list is empty
    if (s.empty())
    {
        return true;
    }
    // keeps track of encountered characters
    int x = 0;

    // loop over every character in the string
    for (size_t i = 0; i < s.length(); i++)
    {
        // Calculate the offset from 'a' gets the bit position
        char character = s[i];
        int offset = character - 'a';

        // checks if the bit is set if not sets the bit
        if ((x & (1 << offset)) == 0)
        {
            x |= (1 << offset);
        }
        else
        {
            // not all are unqiue
            return false;
        }
    }
    // all are unique
    return true;
}

int main(int argc, char *const argv[])
{
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    // number of arguments is not equal to 2
    if (argc != 2)
    {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    // check if given string contains all lowercase letters
    if (!is_all_lowercase(argv[1]))
    {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    // check if given string contains all unique letters
    if (all_unique_letters(argv[1]))
    {
        cout << "All letters are unique." << endl;
    }
    else
    {
        cout << "Duplicate letters found." << endl;
    }

    return 0;
}