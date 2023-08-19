#pragma once

#include <algorithm>
#include <stack>
#include <memory>
#include <iostream>
#include "Graph.hpp"

class DepthFirstSearch
{
private:
    std::unique_ptr<int[]> _linkBy;
    std::unique_ptr<bool[]> _marked;
    int _size;
    int _source;

private:
    void depthFirstSearch(const Graph &graph, int source);

public:
    DepthFirstSearch(const Graph &graph, int source);
    bool connected(int ver);
    std::stack<int> pathTo(int dest);
};

DepthFirstSearch::DepthFirstSearch(const Graph &graph, int source)
    : _linkBy(std::make_unique<int[]>(graph.size())), _marked(std::make_unique<bool[]>(graph.size())),
      _size(graph.size()), _source(source)
{
    // init
    for (int i = 0; i < _size; ++i)
        _linkBy[i] = i;
    std::fill(_marked.get(), _marked.get() + _size, false);

    // search
    depthFirstSearch(graph, _source);
}

void DepthFirstSearch::depthFirstSearch(const Graph &graph, int source)
{
    const std::list<int> &edge = graph.adj(source);

    _marked[source] = true;
    for (const int node : edge)
    {
        if (_marked[node])
            continue;

        _linkBy[node] = source;
        depthFirstSearch(graph, node);
    }
}

bool DepthFirstSearch::connected(int ver)
{
    int passNode = _linkBy[ver];
    while (passNode != _linkBy[ver])
        passNode = _linkBy[ver];

    return passNode == _source;
}

std::stack<int> DepthFirstSearch::pathTo(int dest)
{
    std::cout << "show the link:\n";
    for (int i = 0; i < _size; ++i)
        std::cout << _linkBy[i] << ' ';
    std::cout << '\n';

    std::stack<int> path;
    int passNode = dest;

    do
    {
        path.push(passNode);
        passNode = _linkBy[passNode];
    } while (passNode != _linkBy[passNode]);

    return path;
}