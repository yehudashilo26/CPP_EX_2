// by Yehuda Avraham 325550069

#include "Graph.hpp"
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <list>
#include <iterator>
using namespace std;

namespace ariel
{
    const int INF = std::numeric_limits<int>::max(); // Represents infinity
    class Algorithms
    {
        static vector<vector<int>> adj;
        static vector<int> color;
        static vector<int> parent;
        static vector<bool> visited;
        static vector<bool> recStack;
        static vector<int> dist;
        static queue<int> q;

        static string shortestPathUnweighted(int source, int destination);
        static string dijkstra(int source, int destination); // Dijkstra's algorithm for shortest path using dfs
        static string bellmanFord(int source, int destination , int type); // Bellman-Ford algorithm for shortest path using ralaxation
        static string isCyclicUtil(int v, int parent); // Util function for checking if the graph contains a cycle using DFS
        static string checkDirectedCycle(); // Check if the graph contains a cycle using DFS and back edges
        static string checkUndirectedCycle(); // Check if the graph contains a cycle using DFS and back edges for undirected graph
        static bool checkDirectedCycleUtil(int v); // Util function for checking if the graph contains a cycle using DFS
        static bool checkUndirectedCycleUtil(size_t v, int parent_of_v); // Util function for checking if the graph contains a cycle using DFS
        static string constructCyclePath(int cycle_start, int cycle_end, int type); // Construct the cycle path
        // static void DFS(int u, vector<vector <int>> &adj )
        static void print_adj_mat(const vector<vector<int>> &adj);

    public:
        static bool isConnected(const ariel::Graph &g); // Check if the graph is connected
        static string shortestPath(const ariel::Graph &g, int src, int dest); // Find the shortest path between two vertices
        static string isContainsCycle(const ariel::Graph &g); // Check if the graph contains a cycle
        static string isBipartite(const ariel::Graph &g); // Check if the graph is bipartite
        static bool negativeCycle(const ariel::Graph &g); // Check if the graph contains a negative cycle
    };
} // namespace ariel