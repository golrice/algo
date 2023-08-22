#pragma once

#include "DiGraph.hpp"
#include "DirectedOrder.hpp"
#include <stack>
#include <vector>

class Kosaraju
{
public:
    Kosaraju(DiGraph &graph);
    int numSCC() const { return num; }
    bool connected(int vertexA, int vertexB) const { return _id[vertexA] == _id[vertexB]; }

private:
    void dfs(DiGraph &graph, int v);
    int id(int vertex) { return _id[vertex]; }

private:
    std::vector<bool> _marked;
    std::vector<int> _id;
    int num;
};

// mark in order
Kosaraju::Kosaraju(DiGraph &graph) : _marked(graph.getNumVertices(), false), _id(graph.getNumVertices(), -1), num(0)
{
    DirectedOrder order(graph.reverse());
    std::stack<int> order_vertice = order.getReverseOrder();

    while (!order_vertice.empty())
    {
        int vertex = order_vertice.top();
        order_vertice.pop();
        if (!_marked[vertex])
        {
            dfs(graph, vertex);
            num++;
        }
    }
}

void Kosaraju::dfs(DiGraph &graph, int v)
{
    _marked[v] = true;
    _id[v] = num;

    const std::list<int> &link_vertice = graph.getLink(v);
    for (int vertex : link_vertice)
    {
        if (!_marked[vertex])
            dfs(graph, vertex);
    }
}