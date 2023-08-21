#pragma once

#include "DiGraph.hpp"
#include <stack>
#include <queue>
#include <memory>

class DirectedOrder
{
public:
    DirectedOrder(const DiGraph &graph);
    ~DirectedOrder() = default;
    std::queue<int> getFrontOrder(void) { return _front_order; }
    std::queue<int> getRearOrder(void) { return _rear_order; }
    std::stack<int> getReverseOrder(void) { return _reverse_order; }

private:
    void dfs(const DiGraph &graph, int v);

private:
    std::unique_ptr<bool[]> _marked;
    std::queue<int> _front_order;
    std::queue<int> _rear_order;
    std::stack<int> _reverse_order;
};

DirectedOrder::DirectedOrder(const DiGraph &graph) : _marked(std::make_unique<bool[]>(graph.getNumVertices()))
{
    for (int i = 0; i < graph.getNumVertices(); ++i)
        _marked[i] = false;
    for (int i = 0; i < graph.getNumVertices(); ++i)
        if (!_marked[i])
            dfs(graph, i);
}

void DirectedOrder::dfs(const DiGraph &graph, int v)
{
    _marked[v] = true;
    _front_order.push(v);

    auto &link_vertice = graph.getLink(v);
    for (int current_vertex : link_vertice)
    {
        if (_marked[current_vertex])
            continue;
        dfs(graph, current_vertex);
    }
    _rear_order.push(v);
    _reverse_order.push(v);
}