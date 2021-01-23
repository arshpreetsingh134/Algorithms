// Given a set of 'n' points P = {P1, P2, P3, ....., Pn} in the plane,
// return the shortest Euclidian Distance between the 2 points d(Pi, Pj)
// in O(nlog(n)) time.

#include <iostream>
#include <vector>   // For Vector
#include <algorithm>    // For std::sort()
#include <math.h>   // For std::sqrt()
#include <float.h>  // For FLT_MAX macro
using namespace std;

struct Point
{
    int x;
    int y;
};

// Function that applies Euclidian Distance formula to calculate the distance between 2 pts. p and q
float dist(Point p, Point q)
{
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

// To find the minimum of the 2 values
int min(int x, int y)
{
    return (x < y) ? x : y;
}

// The following functions are the Comparators for std::qsort() in STL
// They are generally used when we have to sort a vector of vectors
// according to a specific column...

// Needed to sort array of points according to X coordinate
bool compareX(const Point &a, const Point &b)
{
    return (a.x < b.x);
}
// Needed to sort array of points according to Y coordinate
bool compareY(const Point &a, const Point &b)
{
    return (a.y < b.y);
}

// A brute-force (O(n^2)) algorithm to calculate the closest points in a plane
float bruteForce(vector<Point> &P, int size)
{
    float min_dist = FLT_MAX;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            float distance = dist(P[i], P[j]);
            if (distance < min_dist)
                min_dist = distance;
        }
    }
    return min_dist;
}

// A utility function to find the distance between the closest points of
// Sy of a given size. All points in Sy[] are sorted according to y
// coordinate. They all have an upper bound on minimum distance as delta.
// Even though this method seems to be a O(n^2) method, it's a O(n)
// method as the inner loop runs at most 7 times.
float ClosestSplitPair(vector<Point> &Sy, int delta)
{
    float best = delta;
    for (int i = 0; i < Sy.size() - 1; i++)
    {
        int j = 1;
        while (j <= min(7, Sy.size() - i))
        {
            if (dist(Sy[i], Sy[i + j]) < best)
                best = dist(Sy[i], Sy[i + j]);
            j++;
        }
    }
    return best;
}

// A recursive function to find the smallest distance. The array Px contains
// all points sorted according to x coordinates and Py contains all points
// sorted according to y coordinates. n is the no. of points
float ClosestPair(vector<Point> &Px, vector<Point> &Py, int n)
{
    // If there are less than 3 points in the plane, use brute-force method
    // to calculate the minimum distance
    if (n <= 3)
        return bruteForce(Px, n);

    // 5 points --> mid = 2
    // 6 points --> mid = 2

    int mid = (n % 2 == 0) ? (n / 2 - 1) : (n / 2);
    Point midPoint = Px[mid]; // Since we are drawing a vertical line (x=c),
                              // we'll use the mid of points sorted by x coordinates, not y

    // To store left-half of P and right-half of P respectively
    vector<Point> Q(mid + 1);     // y sorted points on left of vertical line
    vector<Point> R(n - mid - 1); // y sorted points on right of vertical line

    int l = 0, r = 0;
    // Split the array of Points into left-half and right-half with the vertical line in the middle
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x && l <= mid)
            Q[l++] = Py[i];
        else
            R[r++] = Py[i];
    }

    // Iterators for slicing
    auto start = Px.begin() + mid + 1;
    auto end = Px.end();

    // To store the sliced vector for passing
    // as parameter to the recursive call
    vector<Point> sliced_X(n - mid - 1);

    // Copy vector using copy function()
    copy(start, end, sliced_X.begin());

    // Calculate the smallest distance dl on left of the middle point and
    // dr on right side
    float dl = ClosestPair(Px, Q, mid);
    float dr = ClosestPair(sliced_X, R, n - mid);

    float delta = min(dl, dr);

    // Assuming if x' is the x-coordinate of mid-point through which our vertical
    // line passes, we will find all the points from the given set of points such
    // that they lie between [x' - delta] and [x' + delta], sorted by y coordinate.
    // So now we build an array Sy[] that contains points close (closer than delta)
    // to the line passing through the middle point.
    vector<Point> Sy;

    for (int i = 0; i < n; i++)
    {
        if (abs(Py[i].x - midPoint.x) < delta)
            Sy.push_back(Py[i]);
    }

    // Return the best of dl, dr, and SplitPair distance
    return ClosestSplitPair(Sy, delta);
}

// The main function that finds the smallest distance,
// integrating all the functions into one
float ClosestDist(vector<Point> &points)
{
    vector<Point> Px;
    vector<Point> Py;

    for (int i = 0; i < points.size(); i++)
    {
        Px.push_back(points[i]);
        Py.push_back(points[i]);
    }

    sort(Px.begin(), Px.end(), compareX);
    sort(Py.begin(), Py.end(), compareY);

    return ClosestPair(Px, Py, Px.size());
}

int main()
{
    vector<Point> points{{36, 69}, {68, 50}, {-50, -2}, {22, 18}, {-3, -4}, {58, -23}, {-24, 32}, {-6, 8}};
    cout << "\nThe closest distance is: " << ClosestDist(points);
}