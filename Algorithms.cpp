// by Yehuda Avraham 325550069
#include "Algorithms.hpp"

namespace ariel
{

    vector<vector<int>> Algorithms::adj;
    vector<int> Algorithms::color;
    vector<int> Algorithms::parent;
    vector<bool> Algorithms::visited;
    vector<bool> Algorithms::recStack;
    vector<int> Algorithms::dist;
    queue<int> Algorithms::q;

    string Algorithms::isBipartite(const ariel::Graph &g)
    {
        set<int> A;
        set<int> B;
        q = queue<int>();
        adj = g.getAdjacencyMatrix();
        color = vector<int>(g.get_size(), -1);

        color.at(0) = 0;
        A.insert(0);
        q.push(0);

        while (!q.empty() || A.size() + B.size() < g.get_size())
        {
            if (q.empty())
            {
                for (size_t i = 0; i < g.get_size(); i++)
                {
                    if (color.at(i) == -1)
                    {
                        color.at(i) = 0;
                        A.insert(i);
                        q.push(i);
                        break;
                    }
                }
            }
            size_t u = (size_t)q.front();
            q.pop();

            for (size_t i = 0; i < g.get_size(); i++)
            {
                if (adj.at(u).at(i) != 0)
                {
                    if (color.at(i) == -1)
                    {
                        color.at(i) = 1 - color.at(u);
                        if (color.at(i) == 0)
                        {
                            A.insert(i);
                        }
                        else
                        {
                            B.insert(i);
                        }
                        q.push(i);
                    }

                    else if (color.at(i) == color.at(u))
                    {
                        return "0";
                    }
                }
            }
        }
        string setA = "A={";
        string setB = "B={";

        for (auto it = A.begin(); it != A.end(); ++it)
        {
            setA += to_string(*it);
            if (next(it) != A.end())
            {
                setA += ", ";
            }
        }

        setA += "}";

        for (auto it = B.begin(); it != B.end(); ++it)
        {
            setB += to_string(*it);
            if (next(it) != B.end())
            {
                setB += ", ";
            }
        }

        setB += "}";

        return "The graph is bipartite: " + setA + ", " + setB;
    }

    bool Algorithms::isConnected(const ariel::Graph &g)
    {
        if (g.get_size() == 1)
        {
            return true;
        }
        adj = g.getAdjacencyMatrix();

        if (g.isDirected())
        {
            visited = vector<bool>(g.get_size(), false);
            stack<int> s;
            s.push(0);
            visited.at(0) = true;

            // print_adj_mat(adj_mat);

            while (!s.empty())
            {
                size_t u = (size_t)s.top();
                s.pop();

                for (size_t i = 0; i < g.get_size(); i++)
                {
                    if (adj.at(u).at(i) != 0 && !visited.at(i))
                    {
                        visited.at(i) = true;
                        s.push(i);
                    }
                }
            }

            if (find(visited.begin(), visited.end(), false) != visited.end())
            {
                return false;
            }

            // reverse the graph edges.

            vector<vector<int>> reverse_adj_mat = vector<vector<int>>(g.get_size(), vector<int>(g.get_size(), 0));

            for (size_t i = 0; i < g.get_size(); i++)
            {
                for (size_t j = 0; j < g.get_size(); j++)
                {
                    reverse_adj_mat.at(i).at(j) = adj.at(j).at(i);
                }
            }

            // print_adj_mat(reverse_adj_mat);

            visited = vector<bool>(g.get_size(), false);
            s.push(0);
            visited.at(0) = true;

            while (!s.empty())
            {
                size_t u = (size_t)s.top();
                s.pop();

                for (size_t i = 0; i < g.get_size(); i++)
                {
                    if (reverse_adj_mat.at(u).at(i) != 0 && !visited.at(i))
                    {
                        visited.at(i) = true;
                        s.push(i);
                    }
                }
            }

            return find(visited.begin(), visited.end(), false) == visited.end();
        }

        // Undirected graph
        visited = vector<bool>(g.get_size(), false);
        adj = g.getAdjacencyMatrix();
        q = queue<int>();

        q.push(0);
        visited.at(0) = true;

        while (!q.empty())
        {
            size_t u = (size_t)q.front();
            q.pop();

            for (size_t i = 0; i < g.get_size(); i++)
            {
                if (adj.at(u).at(i) != 0 && !visited.at(i))
                {
                    visited.at(i) = true;
                    q.push(i);
                }
            }
        }

        return find(visited.begin(), visited.end(), false) == visited.end();
    }
    string Algorithms::shortestPath(const ariel::Graph &g, int src, int dest)
    {
        string path;

        if (src < 0 || src >= g.get_size() || dest < 0 || dest >= g.get_size())
        {
            throw invalid_argument("Invalid source or destination vertex.");
        }

        if (src == dest)
        {
            return to_string(src);
        }

        adj = g.getAdjacencyMatrix();

        if (!g.isWeighted())
        {
            path = shortestPathUnweighted(src, dest);
        }

        else if (!g.isNegative())
        {
            path = dijkstra(src, dest);
        }

        else
        {
            path = bellmanFord(src, dest, 0);
        }

        return path;
    }
    string Algorithms::isContainsCycle(const ariel::Graph &g)
    {
        string cycle = "-1";
        adj = g.getAdjacencyMatrix();
        // check for loops in the graph (self loops).
        // A loop is a cycle of length 1 where a vertex is connected to itself.
        for (size_t i = 0; i < g.get_size(); i++)
        {
            if (g.getAdjacencyMatrix().at(i).at(i) != 0)
            {
                cycle = ("The cycle is: " + to_string(i) + " -> " + to_string(i));
                return cycle;
            }
        }

        if (g.isDirected())
        {
            cycle = checkDirectedCycle();
        }

        else
        {
            cycle = checkUndirectedCycle();
        }

        return cycle;
    }

    string Algorithms::shortestPathUnweighted(int source, int destination)
    {
        parent = vector<int>(adj.size(), -1);
        vector<int> dist(adj.size(), INF);
        queue<int> q;
        size_t src = (size_t)source;
        size_t dest = (size_t)destination;
        q.push(src);
        dist.at(src) = 0;

        while (!q.empty())
        {
            size_t u = (size_t)q.front();
            q.pop();

            for (size_t i = 0; i < adj.size(); i++)
            {
                if (adj.at(u).at(i) != 0 && dist.at(i) == INF)
                {
                    dist.at(i) = dist.at(u) + 1;
                    parent.at(i) = u;
                    q.push(i);
                }
            }
        }

        if (dist.at(dest) == INF)
        {
            return "-1";
        }

        size_t u = dest;
        string path;
        while (u != -1)
        {
            path = to_string(u).append(path);
            u = (size_t)parent.at(u);
            if (u != -1)
            {
                path.insert(0, "->");
            }
        }

        return path;
    }

    void Algorithms::print_adj_mat(const vector<vector<int>> &adj)
    {
        for (size_t i = 0; i < adj.size(); i++)
        {
            for (size_t j = 0; j < adj.size(); j++)
            {
                cout << adj.at(i).at(j) << " ";
            }
            cout << endl;
        }
    }

    string Algorithms::dijkstra(int source, int destination)
    {
        size_t graph_size = adj.size();
        vector<int> dist(graph_size, INF);
        parent = vector<int>(graph_size, -1);
        set<pair<int, int>> s;
        size_t src = (size_t)source;
        size_t dest = (size_t)destination;
        dist.at(src) = 0;
        s.insert({0, src});

        while (!s.empty())
        {
            auto it = s.begin();
            size_t u = (size_t)it->second;
            s.erase(it);

            for (size_t i = 0; i < graph_size; i++)
            {
                if (adj.at(u).at(i) != 0 && dist.at(i) > dist.at(u) + adj.at(u).at(i))
                {
                    if (dist.at(i) != INF)
                    {
                        s.erase(s.find({dist.at(i), i}));
                    }

                    dist.at(i) = dist.at(u) + adj.at(u).at(i);
                    parent.at(i) = u;
                    s.insert({dist.at(i), i});
                }
            }
        }

        if (dist.at(dest) == INF)
        {
            return "-1";
        }

        size_t u = dest;
        string path;
        while (u != -1)
        {
            path = to_string(u).append(path);
            u = (size_t)parent.at(u);
            if (u != -1)
            {
                path.insert(0, "->");
            }
        }

        return path;
    }

    string Algorithms::bellmanFord(int source, int destination, int type = 0)
    {
        size_t graph_size = adj.size();
        dist = vector<int>(graph_size, INF);
        parent = vector<int>(graph_size, -1);
        dist.at((size_t)source) = 0;
        bool negative = false;

        // relax edges

        for (size_t i = 0; i < graph_size - 1; i++)
        {
            for (size_t u = 0; u < graph_size; u++)
            {
                for (size_t v = 0; v < graph_size; v++)
                {
                    if (adj.at(u).at(v) != 0 && dist.at(u) != INF && dist.at(u) + adj.at(u).at(v) < dist.at(v))
                    {
                        dist.at(v) = dist.at(u) + adj.at(u).at(v);
                        parent.at(v) = u;
                    }
                }
            }
        }

        if (dist.at((size_t)destination) == INF) // if the dest vertex is not updated then there is no path.
        {
            return "-1";
        }

        // check for negative cycles
        // relax one more time and check if destination vertex is updated.
        int distance = dist.at((size_t)destination);
        for (size_t u = 0; u < graph_size; u++)
        {
            for (size_t v = 0; v < graph_size; v++)
            {
                if (adj.at(u).at(v) != 0 && dist.at(u) != INF && dist.at(u) + adj.at(u).at(v) < dist.at(v))
                {
                    dist.at(v) = dist.at(u) + adj.at(u).at(v);
                    parent.at(v) = u;
                    negative = true;
                }
            }
        }

        if (negative && type == 1)
        {
            return "Negative cycle detected";
        }

        if (distance != dist.at((size_t)destination)) // if the dest vertex is updated then there is a negative cycle.
        {
            return "Negative cycle detected. There is no shortest path to this vertex.";
        }

        size_t u = (size_t)destination; // construct the path.
        string path;
        while (u != -1)
        {
            path = to_string(u).append(path);
            u = (size_t)parent.at(u);
            if (u != -1)
            {
                path.insert(0, "->");
            }
        }

        return path;
    }

    string Algorithms::checkDirectedCycle()
    {
        size_t graph_size = adj.size();
        visited = vector<bool>(graph_size, false);
        recStack = vector<bool>(graph_size, false);
        parent = vector<int>(graph_size, -1);

        int cycle_start = -1;
        int cycle_end = -1;

        for (int i = 0; i < graph_size; ++i)
        {
            if (!visited.at((size_t)i) && checkDirectedCycleUtil(i))
            {
                cycle_start = i;
                cycle_end = parent.at((size_t)i);
                return constructCyclePath(cycle_start, cycle_end, 1);
            }
        }

        return "-1";
    }

    bool Algorithms::checkDirectedCycleUtil(int v)
    {
        visited.at((size_t)v) = true;
        recStack.at((size_t)v) = true;

        for (int i = 0; i < adj.at((size_t(v))).size(); ++i)
        {
            if (adj.at((size_t)v).at((size_t)i) != 0)
            {
                if (recStack.at((size_t)i))
                {
                    parent.at((size_t)i) = v;
                    return true;
                }
                if (!visited.at((size_t)i) && checkDirectedCycleUtil(i))
                {
                    parent.at((size_t)i) = v;
                    return true;
                }
            }
        }

        recStack.at((size_t)v) = false;
        return false;
    }

    string Algorithms::checkUndirectedCycle()
    {
        size_t graph_size = adj.size();
        visited = vector<bool>(graph_size, false);
        parent = vector<int>(graph_size, -1);

        for (size_t v = 0; v < graph_size; ++v)
        {
            if (!visited.at(v) && checkUndirectedCycleUtil(v, -1))
            {
                // cout << "Vertex " << v << " is the start of the cycle." << endl;
                // cout << "Parent of " << v << " is " << parent.at(v) << endl;
                // Cycle detected
                int cycle_start = v;
                // Find the end of the cycle
                int cycle_end = parent.at(v);

                return constructCyclePath(cycle_start, cycle_end, 0);
            }
        }

        return "-1";
    }

    bool Algorithms::checkUndirectedCycleUtil(size_t v, int parent_of_v)
    {
        visited.at(v) = true;
        parent.at(v) = parent_of_v;

        for (size_t i = 0; i < adj.at(v).size(); ++i)
        {
            if (adj.at(v).at(i) != 0)
            {
                if (!visited.at(i))
                {
                    if (checkUndirectedCycleUtil(i, v))
                    {
                        return true;
                    }
                }
                else if (i != (size_t)parent_of_v)
                {
                    parent.at(i) = v;
                    return true; // Cycle detected
                }
            }
        }

        return false;
    }

    string Algorithms::constructCyclePath(int cycle_start, int cycle_end, int type = 0)
    {
        // return the minimum cycle path.
        string path = to_string(cycle_start);
        size_t v = (size_t)cycle_start;
        size_t u = (size_t)cycle_end;

        while (u != cycle_start)
        {
            // if there is an edge between current vertex and cycle start vertex then this is the minimum cycle path.
            if (adj.at(v).at(u) != 0 && type != 0)
            {
                path.insert(0, "->").insert(0, to_string(u));
                break;
            }
            // else add the vertex to the path. update the current vertex to its parent.
            {
                path.insert(0, "->").insert(0, to_string(u));
                u = (size_t)parent.at(u);
            }
        }

        path.insert(0, "->").insert(0, to_string(cycle_start)).insert(0, "The cycle is: ");
        return path;
    }

    bool Algorithms::negativeCycle(const ariel::Graph &g)
    {
        if (!g.isNegative())
        {
            return false;
        }

        adj = g.getAdjacencyMatrix();

        return (bellmanFord(0, 0, 1).compare("Negative cycle detected")) == 0;
    }
} // namespace ariel