#pragma once

#include "DiGraph.hpp"
#include <memory>
#include <queue>
#include <stack>

class DirectedBFS
{
public:
    DirectedBFS(const DiGraph &graph);
    void search(int start_vertex);
    std::stack<int> path(int vertex);

private:
    void clear();

private:
    const DiGraph &_graph;
    std::unique_ptr<bool[]> _visited;
    std::unique_ptr<int[]> _path;
    int _start_vertex;
    int _end_vertex;
    int _number_vertice;
};

DirectedBFS::DirectedBFS(const DiGraph &graph)
    : _graph(graph), _visited(std::make_unique<bool[]>(_graph.getNumVertices())), _path(std::make_unique<int[]>(_graph.getNumVertices())), _number_vertice(_graph.getNumVertices()), _start_vertex(-1), _end_vertex(-1)
{
}

void DirectedBFS::clear()
{
    for (int i = 0; i < _number_vertice; ++i)
    {
        _visited[i] = false;
        _path[i] = i;
    }
}

void DirectedBFS::search(int start_vertex)
{
    std::queue<int> queue;
    queue.push(start_vertex);
    _visited[start_vertex] = true;

    _start_vertex = start_vertex;

    while (!queue.empty())
    {
        int current_vertex = queue.front();
        queue.pop();

        auto &adj = _graph.getLink(current_vertex);
        for (auto i : adj)
        {
            if (_visited[i])
                continue;

            queue.push(i);
            _path[i] = current_vertex;
            _visited[i] = true;
        }
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