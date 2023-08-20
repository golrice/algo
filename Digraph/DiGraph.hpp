#pragma once
#include <memory>
#include <vector>
#include <list>
#include <iostream>

class DiGraph
{
public:
    DiGraph(int n);
    ~DiGraph() = default;

    void addEdge(int from, int to);
    void removeEdge(int from, int to);
    const std::list<int> getLink(int vertex) const
    {
        return adjList[vertex];
    }
    void print() const;

    int getNumVertices() const noexcept { return numVertices; }
    int getNumEdges() const noexcept { return numEdges; }

private:
    int numVertices;
    int numEdges;
    std::vector<std::list<int>> adjList;
};

DiGraph::DiGraph(int n) : numVertices(n), numEdges(0), adjList(n)
{
}

void DiGraph::addEdge(int from, int to)
{
    // add edge from from to to
    adjList[from].push_back(to);
    numEdges++;
}

void DiGraph::removeEdge(int from, int to)
{
    // remove edge from from to to
    adjList[from].remove(to);
    numEdges--;
}

void DiGraph::print() const
{
    for (int i = 0; i < numVertices; i++)
    {
        std::cout << i << ": ";
        std::cout << "size is " << adjList[i].size() << '\n';
        for (auto it = adjList[i].begin(); it != adjList[i].end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}