#pragma once

#include <stdexcept>

namespace MinimalSpanningTree
{
    class Edge
    {
    public:
        Edge(int v1, int v2, int w);
        int other(int vertex) const;
        double weight() const { return _weight; }

        bool operator<(const Edge &e) const { return _weight < e._weight; }
        bool operator>(const Edge &e) const { return _weight > e._weight; }
        bool operator==(const Edge &e) const;

    public:
        int _either_vertex;
        int _other_vertex;
        double _weight;
    };
}

MinimalSpanningTree::Edge::Edge(int v1, int v2, int w)
    : _either_vertex(v1), _other_vertex(v2), _weight(w)
{
}

int MinimalSpanningTree::Edge::other(int vertex) const
{
    if (_either_vertex == vertex)
        return _other_vertex;
    else if (_other_vertex == vertex)
        return _either_vertex;
    else
        throw std::invalid_argument("vertex doesn't match edge");
}

bool MinimalSpanningTree::Edge::operator==(const Edge &e) const
{
    if (_either_vertex == e._either_vertex && _other_vertex == e._other_vertex && _weight == e._weight)
        return true;
    return false;
}