#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

class Graph
{
private:
    std::vector<std::list<int>> _adj;
    int _N;

public:
    Graph(int N);
    ~Graph() = default;
    void addEdge(int verticeA, int verticeB);
    void removeEdge(int verticeA, int verticeB);
    bool contained(int verticeA, int verticeB);
    const std::list<int> &adj(int sourse) const;
    int size(void) const noexcept { return _N; }
    void show(void) const;
    void show(std::ostream &os);
    void show(std::ostream &os, int sourse) const;
    void show(std::ostream &os, int sourse, int dest) const;
};

Graph::Graph(int N) : _adj(N), _N(N)
{
}

void Graph::addEdge(int verticeA, int verticeB)
{
    if (contained(verticeA, verticeB))
        return;

    _adj[verticeA].push_back(verticeB);
    _adj[verticeB].push_back(verticeA);
}

void Graph::removeEdge(int verticeA, int verticeB)
{
    if (!contained(verticeA, verticeB))
        return;

    _adj[verticeA].remove(verticeB);
    _adj[verticeB].remove(verticeA);
}

bool Graph::contained(int verticeA, int verticeB)
{
    if (verticeA < 0 || verticeA > _N || verticeB < 0 || verticeB > _N)
        return false;

    if ((std::find(_adj[verticeA].begin(), _adj[verticeA].end(), verticeB)) == _adj[verticeA].end())
        return false;
    if ((std::find(_adj[verticeB].begin(), _adj[verticeB].end(), verticeA)) == _adj[verticeB].end())
        return false;

    return true;
}

const std::list<int> &Graph::adj(int sourse) const
{
    return _adj[sourse];
}

void Graph::show() const
{
    for (auto &i : _adj)
    {
        for (auto &k : i)
            std::cout << k << ' ';
        std::cout << std::endl;
    }
}

// 展示图里的内容
void Graph::show(std::ostream &os, int sourse, int dest) const
{
    os << sourse << " -> ";
    for (auto &i : _adj[sourse])
    {
        if (i == dest)
            os << i << ' ';
    }
}