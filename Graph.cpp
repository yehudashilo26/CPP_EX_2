// by Yehuda Avraham 325550069 , Gmail:yehudav03@gmail.com
#include "Graph.hpp"

namespace ariel
{
    Graph::Graph()
    {
        this->size = 0;
        this->Edges = 0;
        this->weighted = false;
        this->directed = false;
        this->negative = false;
    }

    Graph::Graph(vector<vector<int>> graph)
    {
        this->size = 0;
        this->Edges = 0;
        this->weighted = false;
        this->directed = false;
        this->negative = false;
        this->loadGraph(std::move(graph));
    }

    void Graph::loadGraph(std::vector<std::vector<int>> graph)
    {
        if (graph.empty())
        {
            throw invalid_argument("The graph is empty.");
        }

        for (size_t i = 0; i < graph.size(); i++)
        {
            if (graph[i].size() != graph.size())
            {
                throw invalid_argument("The graph is not a square matrix.");
            }
        }

        this->Edges = 0;
        // Check if the graph is symmetric.
        for (size_t i = 0; i < graph.size(); i++)
        {
            for (size_t j = 0; j < graph.size(); j++)
            {
                if (graph.at(i).at(j) != graph.at(j).at(i))
                {
                    directed = true;
                }

                if (graph.at(i).at(j) != 0)
                {
                    if (graph.at(i).at(j) != 1)
                    {
                        weighted = true;
                    }

                    if (graph.at(i).at(j) < 0)
                    {
                        negative = true;
                    }

                    this->Edges++;
                }

                // count the number of edges.
            }
        }

        this->size = graph.size();
        this->adjacency_matrix = graph;
    }

    string Graph::printGraph() const
    {
        string graph;

        for (size_t i = 0; i < this->size; i++)
        {
            graph += "[";
            for (size_t j = 0; j < this->size; j++)
            {
                graph += to_string(this->adjacency_matrix.at(i).at(j));
                if (j != this->size - 1)
                {
                    graph += ", ";
                }
            }
            graph += "]";
            if (i != this->size - 1)
            {
                graph += "\n";
            }
        }

        return graph;
    }

    vector<int> Graph::getNeighbors(size_t vertex) const
    {
        if (vertex < 0 || vertex >= this->size)
        {
            throw invalid_argument("The vertex is not exist.");
        }

        vector<int> neighbors;
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->adjacency_matrix.at(vertex).at(i) != 0)
            {
                neighbors.push_back(i);
            }
        }

        return neighbors;
    }

    vector<vector<int>> Graph::getAdjacencyMatrix() const
    {
        return this->adjacency_matrix;
    }

    int Graph::getWeight(size_t vertex1, size_t vertex2) const
    {
        if (vertex1 < 0 || vertex1 >= this->size || vertex2 < 0 || vertex2 >= this->size)
        {
            throw invalid_argument("The vertex is not exist.");
        }

        return this->adjacency_matrix.at(vertex1).at(vertex2);
    }

    bool Graph::isDirected() const
    {
        return this->directed;
    }

    bool Graph::isWeighted() const
    {
        return this->weighted;
    }

    bool Graph::isNegative() const
    {
        return this->negative;
    }

    size_t Graph::get_size() const
    {
        return this->size;
    }

    int Graph::getEdges() const
    {
        return this->Edges;
    }

    bool Graph::compareOrder(const Graph &g1, const Graph &g2)
    {
        return g1.size == g2.size;
    }

    Graph Graph::operator+(const Graph &other) const
    {
        if (!compareOrder(*this, other))
        {
            throw invalid_argument("The graphs are not the same size.");
        }

        vector<vector<int>> newGraph(this->size, vector<int>(this->size, 0));
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                newGraph.at(i).at(j) = this->adjacency_matrix.at(i).at(j) + other.adjacency_matrix.at(i).at(j);
            }
        }

        return Graph(newGraph);
    }

    Graph Graph::operator-(const Graph &other) const
    {
        return *this + (-other);
    }

    Graph Graph::operator+() const
    {
        return *this;
    }

    Graph Graph::operator-() const
    {
        vector<vector<int>> newGraph(this->size, vector<int>(this->size, 0));
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                newGraph.at(i).at(j) = -this->adjacency_matrix.at(i).at(j);
            }
        }

        return Graph(newGraph);
    }

    Graph &Graph::operator++()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                if (this->adjacency_matrix.at(i).at(j) != 0)
                {
                    this->adjacency_matrix.at(i).at(j)++;
                }
            }
        }

        return *this;
    }

    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        ++*this;
        return temp;
    }

    Graph &Graph::operator--()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                if (this->adjacency_matrix.at(i).at(j) != 0)
                {
                    this->adjacency_matrix.at(i).at(j)--;
                }
            }
        }

        return *this;
    }

    Graph Graph::operator--(int)
    {
        Graph temp = *this;
        --*this;
        return temp;
    }

    Graph &Graph::operator+=(const Graph &other)
    {
        *this = *this + other;
        return *this;
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        *this = *this - other;
        return *this;
    }

    Graph Graph::operator*(const Graph &other) const
    {
        if (!compareOrder(*this, other))
        {
            throw invalid_argument("The graphs are not the same size.");
        }

        vector<vector<int>> newGraph(this->size, vector<int>(this->size, 0));
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                for (size_t k = 0; k < this->size; k++)
                {
                    newGraph.at(i).at(j) += this->adjacency_matrix.at(i).at(k) * other.adjacency_matrix.at(k).at(j);
                }
            }
        }

        return Graph(newGraph);
    }

    Graph &Graph::operator*=(int scalar)
    {
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                this->adjacency_matrix.at(i).at(j) *= scalar;
            }
        }

        return *this;
    }

    Graph &Graph::operator/=(int scalar)
    {
        if (scalar == 0)
        {
            throw invalid_argument("Cannot divide by zero.");
        }

        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                this->adjacency_matrix.at(i).at(j) /= scalar;
            }
        }

        return *this;
    }

    Graph Graph::operator*(int scalar) const
    {
        vector<vector<int>> newGraph(this->size, vector<int>(this->size, 0));
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                newGraph.at(i).at(j) = this->adjacency_matrix.at(i).at(j) * scalar;
            }
        }

        return Graph(newGraph);
    }

    bool Graph::operator>(const Graph &other) const
    {
        if (this->contains(other))
        {
            return true;
        }

        if (this->getEdges() > other.getEdges())
        {
            return true;
        }

        if (this->get_size() > other.get_size() && this->getEdges() == other.getEdges())
        {
            return true;
        }

        return false;
    }

    bool Graph::operator<(const Graph &other) const
    {
        return other > *this;
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return !(*this < other) || (*this == other);
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return !(*this > other) || (*this == other);
    }

    bool Graph::operator==(const Graph &other) const
    {
        return this->contains(other) && other.contains(*this);
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    bool Graph::contains(const Graph &other) const
    {
        if (this->get_size() < other.get_size())
        {
            return false;
        }

        for (size_t i = 0; i < other.get_size(); i++)
        {
            for (size_t j = 0; j < other.get_size(); j++)
            {
                if (this->adjacency_matrix.at(i).at(j) != other.adjacency_matrix.at(i).at(j))
                {
                    return false;
                }
            }
        }

        return true;
    }

    ostream &operator<<(ostream &os, const Graph &graph)
    {
        os << graph.printGraph();
        return os;
    }
} // namespace ariel
