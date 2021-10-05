#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <omp.h>
#include <sstream>
#include <string>
#include <vector>

#include <chrono>

using namespace std;

int bfs(int v, vector<vector<int>> digraph)
{
    bool *visited = new bool[digraph.size()];
    int *vertexLevel = new int[digraph.size()];
    for (int i = 0; i < digraph.size(); i++)
    {
        visited[i] = false;
    }

    list<int> queue;
    visited[v] = true;
    queue.push_back(v);
    int level;
    vertexLevel[v] = 0;
    int count = 1;
    while (!queue.empty())
    {
        v = queue.front();
        level = vertexLevel[v];
        queue.pop_front();
        vector<int> adjacent = digraph[v];
        for (int u : adjacent)
        {
            if (!visited[u])
            {
                vertexLevel[u] = (level + 1);
                visited[u] = true;
                queue.push_back(u);
                count++;
            }
        }
    }
    if (count != digraph.size())
    {
        return -1;
    }

    return level;
}

int main()
{
    int digraphSize;
    cin >> digraphSize;

    auto start = chrono::high_resolution_clock::now();
    double omp_start = omp_get_wtime();

    while (digraphSize != 0)
    {
        vector<vector<int>> digraph;
        string emptyLine;
        getline(cin, emptyLine);
        for (int i = 1; i <= digraphSize; i++)
        {
            string neighbors;
            getline(cin, neighbors);
            istringstream is(neighbors);
            digraph.emplace_back(istream_iterator<int>{is}, istream_iterator<int>{});
        }
        int radius = std::numeric_limits<int>::max();
        int stronglyConnected = true;
        int *levels = new int [digraphSize];

        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < digraph.size(); i++)
            {
                levels[i] = bfs(i, digraph);
                if (levels[i] < radius)
                {
                    radius = levels[i];
                }
            }
        }
        if (radius != -1)
        {
            cout << radius << endl;
        }
        else
        {
            cout << "None" << endl;
        }
        cin >> digraphSize;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double omp_end = omp_get_wtime();
    chrono::duration<double> elapsed = end - start;
    cout << endl;
    cout << "Elapsed time: " << elapsed.count() << " s" << endl;
    cout << "OMP recorded Elapsed time: " << omp_start - omp_end << " s" << endl;

    return 0;
}
