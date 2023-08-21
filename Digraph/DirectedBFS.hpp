#pragma once

#include "DiGraph.hpp"
#include <memory>
#include <queue>
#include <stack>

class DirectedBFS
{
public:
    DirectedBFS(const DiGraph &graph);
    std::stack<int> path(int vertex);

private:
    void clear();

private:
    const DiGraph &_graph;
    std::unique_ptr<bool[]> _marked;
    std::unique_ptr<int[]> _path;
    int _number_vertice;
};

DirectedBFS::DirectedBFS(const DiGraph &graph)
    : _graph(graph), _marked(std::make_unique<bool[]>(_graph.getNumVertices())),
      _path(std::make_unique<int[]>(_graph.getNumVertices())), _number_vertice(_graph.getNumVertices())
{
    clear();
    // bfs
    std::queue<int> wait_to_visit;
    wait_to_visit.push(0);

    while (!wait_to_visit.empty())
    {
        // start to visit
        int v = wait_to_visit.front();
        wait_to_visit.pop();

        if (!_marked[v])
        {
            _marked[v] = true;
            auto &neighbors = _graph.getLink(v);

            for (int w : neighbors)
            {
                _path[w] = v;
                wait_to_visit.push(w);
            }
        }
    }
}

void DirectedBFS::clear()
{
    for (int i = 0; i < _number_vertice; ++i)
    {
        _marked[i] = false;
        _path[i] = i;
    }
}

std::stack<int> DirectedBFS::path(int vertex)
{
    int current_vertex = vertex;
    std::stack<int> path;

    while (current_vertex != _path[current_vertex])
    {
        current_vertex = _path[current_vertex];
        path.push(current_vertex);
    }
    path.push(current_vertex);

    return path;
}