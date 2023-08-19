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
    ~Graph();
    void addEdge(int verticeA, int verticeB);
    void removeEdge(int verticeA, int verticeB);
    bool contained(int verticeA, int verticeB);
    const std::list<int> &adj(int sourse) const;
};

Graph::Graph(int N) : _adj(N), _N(N)
{
    char ch;

    for (int i = 0; i < _N; ++i)
    {
        while ((std::cin >> ch) && ch != '\n')
        {
            // 只有当该节点没有被记录过才是合法节点
            if (std::find(_adj[i].begin(), _adj[i].end(), ch - '0') != _adj[i].end())
                _adj[i].emplace_back(ch - '0');
        }
    }
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