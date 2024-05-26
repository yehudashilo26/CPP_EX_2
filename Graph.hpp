#pragma once
#include <set>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> adjacency_matrix;
        size_t size;
        int Edges;     // Number of edges.
        bool weighted; // 0 - unweighted, 1 - weighted.
        bool directed; // 0 - undirected, 1 - directed.
        bool negative; // 0 - non-negative, 1 - negative.

    public:
        Graph();
        Graph(vector<vector<int>> graph);
        void loadGraph(std::vector<std::vector<int>> graph);
        string printGraph() const;
        size_t get_size() const;
        int getEdges() const;
        std::vector<int> getNeighbors(size_t vertex) const;
        std::vector<std::vector<int>> getAdjacencyMatrix() const;
        int getWeight(size_t vertex1, size_t vertex2) const;
        bool isDirected() const;
        bool isWeighted() const;
        bool isNegative() const;
        bool contains(const Graph &other) const;

        // Operators.
        Graph operator-(const Graph &other) const;
        Graph &operator-=(const Graph &other);
        Graph operator+(const Graph &other) const;
        Graph &operator+=(const Graph &other);
        Graph operator*(const Graph &other) const;
        Graph &operator*=(int scalar);
        Graph &operator/=(int scalar);
        Graph operator*(int scalar) const;
        friend ostream &operator<<(ostream &os, const Graph &graph);

        // comparison operators
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator>(const Graph &other) const;
        bool operator<=(const Graph &other) const;
        bool operator>=(const Graph &other) const;

        // unary operators
        Graph operator+() const;
        Graph operator-() const;

        // increment and decrement operators
        Graph &operator++(); // pre-increment
        Graph operator++(int); // post-increment
        Graph &operator--();
        Graph operator--(int);

        // matrix order comparison
        static bool compareOrder(const Graph &g1, const Graph &g2);
    };
} // namespace ariel