#pragma once

#include "DiGraph.hpp"
#include <memory>
#include <stack>
#include <iostream>

class DirectedDFS
{
public:
    DirectedDFS(const DiGraph &graph, int startVertex);
    ~DirectedDFS() = default;
    // Returns true if the vertex is visited
    bool visited(int vertex) const { return _marked[vertex]; }
    // Returns the path from the start vertex to the given vertex
    std::stack<int> pathTo(int vertex) const;
    std::stack<int> pathFromTo(const DiGraph &graph, int start_vertex, int end_vertex);
    void search(const DiGraph &graph, int startVertex);
    void print(void) const;

private:
    void dfs(const DiGraph &graph, int vertex);
    void clear(void);

private:
    int _size;
    int _startVertex;
    std::unique_ptr<bool[]> _marked;
    std::unique_ptr<int[]> _prv;
};

DirectedDFS::DirectedDFS(const DiGraph &graph, int startVertex)
    : _size(graph.getNumVertices()), _startVertex(startVertex), _marked(std::make_unique<bool[]>(_size)), _prv(std::make_unique<int[]>(_size))
{
    search(graph, startVertex);
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

    path.push(currentVertex);

    while (_prv[currentVertex] != currentVertex)
    {
        path.push(_prv[currentVertex]);
        currentVertex = _prv[currentVertex];
    }

    return path;
}

std::stack<int> DirectedDFS::pathFromTo(const DiGraph &graph, int start_vertex, int end_vertex)
{
    _startVertex = start_vertex;
    search(graph, end_vertex);
}

void DirectedDFS::search(const DiGraph &graph, int startVertex)
{
    clear();
    dfs(graph, startVertex);
}

void DirectedDFS::dfs(const DiGraph &graph, int vertex)
{
    _marked[vertex] = true;

    std::list<int> linked_vertice = graph.getLink(vertex);
    for (auto current_vertex : linked_vertice)
    {
        if (_marked[current_vertex])
            continue;

        _prv[current_vertex] = vertex;
        dfs(graph, current_vertex);
    }
}
