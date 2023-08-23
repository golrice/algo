#pragma once

#include "EdgeWeightedGraph.hpp"
#include <queue>

namespace MinimalSpanningTree
{
    class LazyPrimSort
    {
    public:
        using type = EdgeWeightedGraph::EdgeType;

    public:
        LazyPrimSort(const EdgeWeightedGraph &graph);
        ~LazyPrimSort() = default;
        vector<type> getMST() const { return _mst; }
        double getTotalWeight() const { return _total_weight; }

    private:
        void visit(const EdgeWeightedGraph &graph, int vertex);

    private:
        priority_queue<type, vector<type>, greater<type>> _pq;
        vector<bool> _marked;
        vector<type> _mst;
        int _total_weight;
    };
}

MinimalSpanningTree::LazyPrimSort::LazyPrimSort(const EdgeWeightedGraph &graph)
    : _marked(graph.V(), false), _mst(graph.V() - 1), _total_weight(0)
{
    visit(graph, 0);

    while (!_pq.empty())
    {
        const auto [either, other, weight] = _pq.top();

        if (_marked[either] && _marked[other])
            continue;

        _total_weight += weight;
        _mst.emplace_back(either, other, weight);

        if (!_marked[either])
            visit(graph, either);
        else if (!_marked[other])
            visit(graph, other);

        _pq.pop();
    }
}

void MinimalSpanningTree::LazyPrimSort::visit(const EdgeWeightedGraph &graph, int vertex)
{
    _marked[vertex] = true;

    for (const auto &edge : graph.edgesFrom(vertex))
    {
        if (!_marked[edge.other(vertex)])
            _pq.push(edge);
    }
}