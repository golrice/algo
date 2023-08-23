#pragma once

#include "EdgeWeightedGraph.hpp"
#include "MutablePriorityQueue.hpp"
#include <vector>
#include <optional>

namespace MinimalSpanningTree
{
    using namespace std;
    class PrimSort
    {
    public:
        PrimSort(EdgeWeightedGraph &graph);
        double weight() const;
        vector<Edge> edges() const { return _edges; }

    private:
        void visit(const EdgeWeightedGraph &graph, int vertex);

    private:
        vector<Edge> _edges;
        vector<bool> _marked;
        vector<optional<int>> _current_minmal_weight;
        MutablePriorityQueue<Edge> _waiting_path;
    };
}

double MinimalSpanningTree::PrimSort::weight() const
{
    double total_weight = 0.0;
    for (const auto [either, other, weight] : _edges)
        total_weight += weight;
    return total_weight;
}

MinimalSpanningTree::PrimSort::PrimSort(EdgeWeightedGraph &graph)
    : _marked(graph.V(), false), _current_minmal_weight(graph.V()), _edges(graph.V() - 1)
{
    // reset all the weight to make sure the validation
    for (auto &edge_weight : _current_minmal_weight)
        edge_weight.reset();

    visit(graph, 0);
    while (!_waiting_path.empty())
    {
        const auto choose_edge = _waiting_path.top();
        _waiting_path.pop();
        const auto vertex = _marked[choose_edge._either_vertex] ? choose_edge._other_vertex : choose_edge._either_vertex;
        visit(graph, vertex);
    }
}

void MinimalSpanningTree::PrimSort::visit(const EdgeWeightedGraph &graph, int vertex)
{
    _marked[vertex] = true;

    const auto &edges = graph.edgesFrom(vertex);
    for (const auto &edge : edges)
    {
        const auto other_vertex = edge.other(vertex);
        if (_marked[other_vertex])
            continue;

        if (!_current_minmal_weight[other_vertex].has_value())
            _waiting_path.push(edge);
        else if (_current_minmal_weight[other_vertex].has_value() &&
                 _current_minmal_weight[other_vertex].value() > edge.weight())
            _waiting_path.change(Edge(vertex, other_vertex, edge.weight()), edge);
    }
}