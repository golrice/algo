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

private:
    void dfs(void);

public:
    Graph(int N);
    ~Graph();
    void depthFirstSearch(int sourse);
    void addEdge(int verticeA, int verticeB);
    void removeEdge(int verticeA, int verticeB);
    bool contain(int verticeA, int verticeB);
};

Graph::Graph(int N) : _adj(N), _N(N)
{
    char ch;

    for (int i = 0; i < _N; ++i)
    {
        while ((std::cin >> ch) && ch != '\n')
        {
            if (std::find(_adj[i].begin(), _adj[i].end(), ch - '0') != _adj[i].end())
                _adj[i].emplace_back(ch - '0');
        }
    }
}

void Graph::addEdge(int verticeA, int verticeB)
{
    if (contain(verticeA, verticeB))
        return;

    _adj[verticeA].push_back(verticeB);
    _adj[verticeB].push_back(verticeA);
}

void Graph::removeEdge(int verticeA, int verticeB)
{
    if (!contain(verticeA, verticeB))
        return;

    _adj[verticeA].remove(verticeB);
    _adj[verticeB].remove(verticeA);
}

bool Graph::contain(int verticeA, int verticeB)
{
    if (verticeA < 0 || verticeA > _N)
        return false;
    if (verticeB < 0 || verticeB > _N)
        return false;

    if ((std::find(_adj[verticeA].begin(), _adj[verticeA].end(), verticeB)) == _adj[verticeA].end())
        return false;
    if ((std::find(_adj[verticeB].begin(), _adj[verticeB].end(), verticeA)) == _adj[verticeB].end())
        return false;

    return true;
}

void Graph::depthFirstSearch(int sourse)
{
    auto passed = std::make_unique<bool[]>(_N);
    std::fill(passed.get(), &passed[_N], false);
}