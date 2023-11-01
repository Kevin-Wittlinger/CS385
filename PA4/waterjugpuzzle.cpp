/*******************************************************************************
 * Name        : waterjug.cpp
 * Author      : Isabelle Villanueva & Kevin Wittlinger
 * Date        : October 21, 2023
 * Description : Solves the famous water jug puzzle using breadth-first search
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Not correct
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>
#include <set>

using namespace std;

struct State
{
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions, State *_parent) : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} {}

    // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << directions << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

// Checks if the current state is the goal state
bool goal_reached(State current, State goal)
{
    return (current.a == goal.a) && (current.b == goal.b) && (current.c == goal.c);
}

// Printing out states pointer *result coming from previous functions return
// reverses the order
string printoutput(State *result)
{
    stringstream ss;
    while (result != nullptr)
    {
        if (result->parent != nullptr)
        {
            ss << result->directions << "\n";
        }
        else
        {
            ss << result->to_string() << "\n";
        }
        result = result->parent;
    }
    return ss.str();
}

// pouring from one jug to another
State *pourto(State current, int capacityTo, string to, string from)
{
    int pourAmount = min(current.a, capacityTo - current.b);
    if (pourAmount == 0)
        return nullptr;

    State newState(current.a - pourAmount, current.b + pourAmount, current.c, "Pour " + to_string(pourAmount) + " gallons from " + from + " to " + to + ".", &current);
    return new State(newState);
}

// Performs breadth-first search
string bfs(int capacityA, int capacityB, int capacityC, int goalA, int goalB, int goalC)
{
    queue<State *> states;
    State *goal = new State(goalA, goalB, goalC, "Goal", nullptr);
    State *initial = new State(0, 0, capacityC, "Initial state. ", nullptr);
    set<State *> visited;
    states.push(initial);
    string temporary = "";

    while (!states.empty())
    {
        State *current = states.front();
        states.pop();

        if (goal_reached(*current, *goal))
        {
            return printoutput(current);
        }

        if (visited.count(current))
        {
            continue;
        }

        visited.insert(current);

        State *pourCA = pourto(*current, capacityC, "C", "A");
        if (pourCA != nullptr)
        {
            states.push(pourCA);
        }
        delete pourCA;

        State *pourBA = pourto(*current, capacityB, "B", "A");
        if (pourBA != nullptr)
        {
            states.push(pourBA);
        }
        delete pourBA;

        State *pourCB = pourto(*current, capacityC, "C", "B");
        if (pourCB != nullptr)
        {
            states.push(pourCB);
        }
        delete pourCB;

        State *pourAB = pourto(*current, capacityA, "A", "B");
        if (pourAB != nullptr)
        {
            states.push(pourAB);
        }
        delete pourAB;

        State *pourBC = pourto(*current, capacityB, "B", "C");
        if (pourBC != nullptr)
        {
            states.push(pourBC);
        }
        delete pourBC;

        State *pourAC = pourto(*current, capacityA, "A", "C");
        if (pourAC != nullptr)
        {
            states.push(pourAC);
        }
        delete pourAC;
    }

    delete goal;
    delete initial;
    return "No solution.";
}

int main(int argc, char *const argv[])
{
    istringstream iss;
    string str;
    int capA, capB, capC, goalA, goalB, goalC;

    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    iss.str(argv[1]);
    if (!(iss >> capA) || capA <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[1]);
    if (!(iss >> capA) || capA <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[2]);
    if (!(iss >> capB) || capB <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[3]);
    if (!(iss >> capC) || capC <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[4]);
    if (!(iss >> goalA) || goalA < 0)
    {
        cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[5]);
    if (!(iss >> goalB) || goalB < 0)
    {
        cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[6]);
    if (!(iss >> goalC) || goalC < 0)
    {
        cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[1]);
    if (goalA > capA)
    {
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[2]);
    if (goalB > capB)
    {
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[3]);
    if (goalC > capC)
    {
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    iss.clear();

    if (capC != (goalA + goalB + goalC))
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    string result = bfs(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
    cout << result;

    return 0;
}
