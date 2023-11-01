/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Kevin Wittlinger
 * Date        : 9/19/2023
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve
{
public:
    PrimesSieve(int limit);

    ~PrimesSieve()
    {
        delete[] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool *const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit}
{
    sieve();
}

void PrimesSieve::display_primes() const
{
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << endl;
    cout << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    // counting max width for the amount of primes

    const int max_prime_width = num_digits(max_prime_);
    int primes_per_row = 80 / (max_prime_width + 1);
    int count = 0;

    // counting for the number of primes being displays and printing primes
    for (int i = 2; i <= limit_; i++)
    {
        if (is_prime_[i])
        {
            cout << setw(max_prime_width) << i;
            count++;

            if (count % primes_per_row == 0)
            {
                cout << endl;
                count = 0;
            }
            if (i != max_prime_ && count % primes_per_row != 0)
            {
                cout << " ";
            }
        }
    }
    // print new line if there are remaining primes
    if (count > 0)
    {
        cout << endl;
    }
}

void PrimesSieve::sieve()
{
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.

    // list all numbers as potential primes
    for (int i = 2; i <= limit_; i++)
    {
        is_prime_[i] = true;
    }
    // non prime
    for (int i = 2; i * i <= limit_; i++)
    {
        if (is_prime_[i])
        {
            for (int j = i * i; j <= limit_; j += i)
            {
                is_prime_[j] = false;
            }
        }
    }
    // count number of primes to find max prime
    num_primes_ = 0;
    for (int i = 2; i <= limit_; i++)
    {
        if (is_prime_[i])
        {
            num_primes_++;
            max_prime_ = i;
        }
    }
}

int PrimesSieve::num_digits(int num)
{
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

int main()
{
    cout << "**************************** "
         << "Sieve of Eratosthenes"
         << " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if (!(iss >> limit))
    {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2)
    {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);
    sieve.display_primes();
    return 0;
}
