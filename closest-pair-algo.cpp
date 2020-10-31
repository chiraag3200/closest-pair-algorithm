// library
#include <bits/stdc++.h>
using namespace std;

// comparator func. to sort vector according to the second value
int compare(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second < b.second;
}

// func. to calculate the distance between 2 points
// using distance formula -> sqrt((y2-y1)^2+(x2-x1)^2)
double dist(const pair<int, int> &a, const pair<int, int> &b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

// func. to find minimum distance pair with pairs at different side of the line
double blockDist(vector<pair<int, int>> block, double d)
{
    int size = block.size();
    double min_dist = d; // minimum value that min_dist can have is d

    // find distance between each pair of points until diff is less the d
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if ((block[j].second - block[i].second) < min_dist)
            {
                if (dist(block[i], block[j]) < min_dist)
                {
                    min_dist = dist(block[i], block[j]);
                }
            }
        }
    }

    return min_dist;
}

// recursive func. to divide the plane in 2 halves and find the min. dist. pair in each half
// using divide and conquer
double closestDist(vector<pair<int, int>> px, vector<pair<int, int>> py, int n)
{
    // base case of the recursion
    if (n <= 4)
    {
        double min_dist = DBL_MAX;

        // find min. dist. by calculating distance between each pair
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (dist(px[i], px[j]) < min_dist)
                    min_dist = dist(px[i], px[j]);
            }
        }
        return min_dist;
    }

    int mid = n / 2; // divide the vector about the mid point
    const pair<int, int> point = px[mid];

    vector<pair<int, int>> pyl;
    vector<pair<int, int>> pyr;

    // divide points in py sorted array about the line.
    for (int i = 0; i < n; i++)
    {
        if (py[i].first <= point.first)
        {
            pyl.push_back({py[i].first, py[i].second});
        }
        else
        {
            pyr.push_back({py[i].first, py[i].second});
        }
    }

    vector<pair<int, int>> pz;
    for (int i = 0; i < n; i++)
    {
        if (i < mid)
            continue;
        pz.push_back({px[i].first, px[i].second});
    }

    // find the min. distance on left and right of the line
    double dl = closestDist(px, pyl, mid);
    double dr = closestDist(pz, pyr, n - mid);

    // vector to find min. dist. between pair with one on left
    // and other on the right of the line
    vector<pair<int, int>> block;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(py[i].first - point.first) < min(dl, dr))
            block.push_back({py[i].first, py[i].second});
    }

    return blockDist(block, min(dl, dr));
}

// func. to generate vector sorting according the x and y coordinate
double distance(int n, vector<pair<int, int>> points)
{
    vector<pair<int, int>> px; // stores elements sorted according to x coordinate
    vector<pair<int, int>> py; // stores elements sorted according to y coordinate
    for (int i = 0; i < n; i++)
    {
        px.push_back({points[i].first, points[i].second});
        py.push_back({points[i].first, points[i].second});
    }

    sort(px.begin(), px.end());
    sort(py.begin(), py.end(), compare);
    return closestDist(px, py, n);
}

// a func. to generate random coordinated
void generatePoints(int n, vector<pair<int, int>> &v)
{
    int N = 1e6;
    for (int i = 0; i < n; i++)
    {
        int x = rand() % N;
        int y = rand() % N;
        v.push_back({x, y});
    }
}

// Main program
int32_t main()
{
    vector<pair<int, int>> points; // to store coordinated
    int n = 100;
    generatePoints(n, points); // generate random coordinates
    cout << "The distance between the closest pairs is " << distance(n, points);
    return 0;
}