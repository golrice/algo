#pragma once

#include "Edge.hpp"
#include "EdgeWeightedGraph.hpp"
#include "MutablePriorityQueue.hpp"

namespace MinimalSpanningTree
{
    using namespace std;
    class KruskalSort
    {
    public:
        KruskalSort(const EdgeWeightedGraph &graph);
        vector<Edge> getMST() const { return _mst; }
        double weight() const;

    private:
        MutablePriorityQueue<Edge> _priority_edges;
        vector<bool> _marked;
        vector<Edge> _mst;
    };
}

MinimalSpanningTree::KruskalSort::KruskalSort(const EdgeWeightedGraph &graph)
    : _marked(graph.V(), false), _mst(graph.V() - 1)
{
    // push all the edge in the queue
    for (int start_vertex = 0; start_vertex < graph.V(); start_vertex++)
    {
        const auto &link_vertex = graph.edgesFrom(start_vertex);
        for (const auto &edge : link_vertex)
            _priority_edges.push(edge);
    }
    // get the minimal edge once a time and mark the vertex
    while (!_priority_edges.empty())
    {
        if (const auto &edge = _priority_edges.top(); !_marked[edge._either_vertex] || !_marked[edge._other_vertex])
        {
            _mst.push_back(edge);
            _marked[edge._either_vertex] = true;
            _marked[edge._other_vertex] = true;
        }
        _priority_edges.pop();
    }
}

double MinimalSpanningTree::KruskalSort::weight() const
{
    double total_weight = 0.0;
    for (const auto [either, other, weight] : _mst)
        total_weight += weight;
    return total_weight;
}