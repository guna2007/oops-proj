#ifndef TEMPLATE_UTILS_H
#define TEMPLATE_UTILS_H

#ifndef D2_MODE

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include "task.h"

using namespace std;

// ===== OOP Concept: TEMPLATES (Generic Programming) =====
// Generic utility classes and functions that work with any data type
// NOTE: Only available in Final Submission mode (not in D2_MODE)

// Template Class 1: Generic Container with statistics
template <typename T>
class Container
{
private:
    vector<T> items;

public:
    // Add item to container
    void add(const T &item)
    {
        items.push_back(item);
    }

    // Get all items
    const vector<T> &getItems() const
    {
        return items;
    }

    // Get size
    size_t size() const
    {
        return items.size();
    }

    // Check if empty
    bool isEmpty() const
    {
        return items.empty();
    }

    // Clear all items
    void clear()
    {
        items.clear();
    }

    // Display all items (requires operator<< for T)
    void display() const
    {
        cout << "\n[Container Contents - " << items.size() << " items]\n";
        for (size_t i = 0; i < items.size(); i++)
        {
            cout << "  [" << i << "] " << items[i] << endl;
        }
    }

    // Get item at index
    T &operator[](size_t index)
    {
        return items[index];
    }

    const T &operator[](size_t index) const
    {
        return items[index];
    }
};

// Template Class 2: Generic Comparator with Exception Handling
template <typename T>
class Comparator
{
public:
    // Find maximum element - throws exception if empty
    static T findMax(const vector<T> &items)
    {
        if (items.empty())
        {
            throw runtime_error("Cannot find max of empty collection");
        }
        return *max_element(items.begin(), items.end());
    }

    // Find minimum element - throws exception if empty
    static T findMin(const vector<T> &items)
    {
        if (items.empty())
        {
            throw runtime_error("Cannot find min of empty collection");
        }
        return *min_element(items.begin(), items.end());
    }

    // Sort items in ascending order
    static vector<T> sortAscending(vector<T> items)
    {
        sort(items.begin(), items.end());
        return items;
    }

    // Sort items in descending order
    static vector<T> sortDescending(vector<T> items)
    {
        // Using functor instead of lambda
        sort(items.begin(), items.end(), greater<T>());
        return items;
    }

    // Count elements greater than threshold
    static int countGreaterThan(const vector<T> &items, const T &threshold)
    {
        int count = 0;
        for (const T &item : items)
        {
            if (item > threshold)
                count++;
        }
        return count;
    }

    // Count elements less than threshold
    static int countLessThan(const vector<T> &items, const T &threshold)
    {
        int count = 0;
        for (const T &item : items)
        {
            if (item < threshold)
                count++;
        }
        return count;
    }
};

// Template Class 3: Statistics Calculator (for numeric types)
template <typename T>
class Statistics
{
public:
    // Calculate average
    static double average(const vector<T> &values)
    {
        if (values.empty())
            return 0.0;
        T sum = accumulate(values.begin(), values.end(), T(0));
        return static_cast<double>(sum) / values.size();
    }

    // Calculate sum
    static T sum(const vector<T> &values)
    {
        return accumulate(values.begin(), values.end(), T(0));
    }

    // Find median
    static double median(vector<T> values)
    {
        if (values.empty())
            return 0.0;

        sort(values.begin(), values.end());
        size_t n = values.size();

        if (n % 2 == 0)
        {
            return (values[n / 2 - 1] + values[n / 2]) / 2.0;
        }
        else
        {
            return values[n / 2];
        }
    }

    // Calculate range (max - min)
    static T range(const vector<T> &values)
    {
        if (values.empty())
            return T(0);
        T maxVal = *max_element(values.begin(), values.end());
        T minVal = *min_element(values.begin(), values.end());
        return maxVal - minVal;
    }
};

// Template Function: Generic Pair class for holding two related values
template <typename T1, typename T2>
class Pair
{
private:
    T1 first;
    T2 second;

public:
    Pair(const T1 &f, const T2 &s) : first(f), second(s) {}

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

    void setFirst(const T1 &f) { first = f; }
    void setSecond(const T2 &s) { second = s; }

    // Display pair
    void display() const
    {
        cout << "(" << first << ", " << second << ")";
    }

    // Operator overloading for Pair
    friend ostream &operator<<(ostream &os, const Pair &p)
    {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
};

// Template Function: Generic swap
template <typename T>
void genericSwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// Template Function: Generic print array
template <typename T>
void printArray(const T arr[], int size, const string &label = "Array")
{
    cout << "\n"
         << label << ": [";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i < size - 1)
            cout << ", ";
    }
    cout << "]\n";
}

// Template Function: Generic find element
template <typename T>
int findElement(const vector<T> &items, const T &target)
{
    auto it = find(items.begin(), items.end(), target);
    if (it != items.end())
    {
        return distance(items.begin(), it);
    }
    return -1; // Not found
}

#endif // D2_MODE
#endif // TEMPLATE_UTILS_H
