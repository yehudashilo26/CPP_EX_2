// by Yehuda Avraham 325550069 , Gmail:yehudav03@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

#define MAX_WEIGHT 10
#define MIN_WEIGHT -5
using namespace std;

ariel::Graph createRandomGraph(size_t n)
{
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            graph[i][j] = rand() % (MAX_WEIGHT + 1) + MIN_WEIGHT;
            graph[j][i] = rand() % (MAX_WEIGHT + 1) + MIN_WEIGHT;
        }
    }

    return ariel::Graph(graph);
}


TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}


TEST_CASE("Test Comprasion operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 > g2);
    CHECK(g1 < g2);
    CHECK(g1 >= g2);
    CHECK(g2 < g1);
    CHECK(g2 <= g1);
    CHECK_EQ(g1 == g2, true);
    CHECK_EQ(g1 != g2, false);
}
TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("Zero + Identity Matrix Case"){

    
    for (size_t i = 1; i < 50; i++)
    {
        ariel::Graph g1 = createRandomGraph(i);
        vector<vector<int>> graph(i, vector<int>(i, 0));

        ariel::Graph g2 = ariel::Graph(graph);

        vector<vector<int>> identity_matrix(i, vector<int>(i, 0));
        for (size_t j = 0; j < i; j++)
        {
            identity_matrix[j][j] = 1;
        }

        ariel::Graph g3 = ariel::Graph(identity_matrix);
        CHECK(g1 + g2 == g1);
        CHECK(g1 * g2 == g2);
        CHECK(g1 - g2 == g1);
        CHECK(g2 - g1 == -g1);
        CHECK(g1 * 0 == g2);
        CHECK(g1 * g3 == g1);
        CHECK(g3 * g1 == g1);
        CHECK(g1 >= g2);
        g1 += g2;


        CHECK((g1 -= g2) == g1);
        CHECK((g2 -= g1) == -g1);
}
}

TEST_CASE("Unary operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {1, 0, 5},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 3, 0},
        {2, 0, 6},
        {0, 2, 0}};
    g2.loadGraph(weightedGraph);

    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}}; // Zero matrix
    CHECK(+g1 == g1);
    CHECK(-g1 == g1 * -1);
    CHECK(++g1 == g2);
    ariel::Graph g3 = g1++;

    CHECK(g3 == --g1);

    g3 = --g1;
    CHECK(g3 == g1);
    CHECK(g3 == g1++);
    CHECK(g3 != g1);

    g3 = ++g1;
    CHECK(g3 == g1);
    CHECK(g3 == g1--);
    CHECK(g3 != g1);

    g3 = g1--;
    CHECK(g3 != g1);
    CHECK(g3 == ++g1);
    CHECK(g3 == g1);

}
