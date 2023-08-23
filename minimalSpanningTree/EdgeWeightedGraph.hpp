#pragma once

#include "Edge.hpp"
#include <tuple>
#include <vector>
#include <list>

namespace MinimalSpanningTree
{
    using namespace std;

    class EdgeWeightedGraph
    {
    public:
        using EdgeType = Edge;

    public:
        EdgeWeightedGraph(int numVertices = 0);
        ~EdgeWeightedGraph() = default;
        int V() const { return _num_vertices; }
        int E() const { return _num_edges; }
        void addEdge(int v, int w, double weight);
        void addEdge(const EdgeType &edge);
        const list<EdgeType> &edgesFrom(int from_vertex) const { return _adj[from_vertex]; }

    private:
        int _num_vertices;
        int _num_edges;
        vector<list<EdgeType>> _adj;
    };
}

MinimalSpanningTree::EdgeWeightedGraph::EdgeWeightedGraph(int numVertices)
    : _num_vertices(numVertices), _num_edges(0), _adj(numVertices)
{
}

void MinimalSpanningTree::EdgeWeightedGraph::addEdge(int v, int w, double weight)
{
    _adj[v].push_back(EdgeType(v, w, weight));
    _adj[w].push_back(EdgeType(w, v, weight));
    _num_edges++;
}

void MinimalSpanningTree::EdgeWeightedGraph::addEdge(const EdgeType &edge)
{
    auto [either, other, weight] = edge;
    addEdge(either, other, weight);
}