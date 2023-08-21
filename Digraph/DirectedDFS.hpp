#pragma once

#include "DiGraph.hpp"
#include <memory>
#include <stack>
#include <iostream>

class DirectedDFS
{
public:
    DirectedDFS(const DiGraph &graph);
    ~DirectedDFS() = default;
    // Returns true if the vertex is visited
    bool visited(int vertex) const { return _marked[vertex]; }
    // Returns the path from the start vertex to the given vertex
    std::stack<int> pathTo(int vertex) const;
    void print(void) const;
    void dfs(const DiGraph &graph, int vertex);

private:
    void clear(void);

private:
    int _size;
    std::unique_ptr<bool[]> _marked;
    std::unique_ptr<int[]> _prv;
};

DirectedDFS::DirectedDFS(const DiGraph &graph)
    : _size(graph.getNumVertices()), _marked(std::make_unique<bool[]>(_size)), _prv(std::make_unique<int[]>(_size))
{
    clear();
    for (int i = 0; i < _size; ++i)
        if (!_marked[i])
            dfs(graph, i);
}

void DirectedDFS::print(void) const
{
    for (int i = 0; i < _size; i++)
    {
        std::cout << i << ": ";

        int current_vertex = i;
        do
        {
            std::cout << current_vertex << ' ';
            current_vertex = _prv[current_vertex];
        } while (current_vertex != _prv[current_vertex]);
        std::cout << std::endl;
    }
}

void DirectedDFS::clear(void)
{
    for (int i = 0; i < _size; i++)
    {
        _marked[i] = false;
        _prv[i] = i;
    }
}

std::stack<int> DirectedDFS::pathTo(int vertex) const
{
    std::stack<int> path;
    int currentVertex = vertex;

    do
    {
        path.push(currentVertex);
        currentVertex = _prv[currentVertex];
    } while (currentVertex != _prv[currentVertex]);

    return path;
}

void DirectedDFS::dfs(const DiGraph &graph, int vertex)
{
    _marked[vertex] = true;

    std::list<int> linked_vertice = graph.getLink(vertex);
    for (int current_vertex : linked_vertice)
    {
        if (_marked[current_vertex])
            continue;

        _prv[current_vertex] = vertex;
        dfs(graph, current_vertex);
    }
}
