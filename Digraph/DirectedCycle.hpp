#pragma once

#include "DiGraph.hpp"
#include <memory>
#include <stack>

class DirectedCycle
{
public:
    DirectedCycle(const DiGraph &G);
    bool hasCycle() const;
    std::stack<int> cycle() const;

private:
    void clear(const DiGraph &G);
    void dfs(const DiGraph &G, int v);

private:
    bool _inCycle;
    int _size;
    std::unique_ptr<bool[]> _marked;
    std::unique_ptr<int[]> _prv;
    std::unique_ptr<bool[]> _in_stack;
    std::stack<int> _cycle;
};

DirectedCycle::DirectedCycle(const DiGraph &G)
    : _inCycle(false), _size(G.getNumVertices()), _marked(std::make_unique<bool[]>(_size)), _prv(std::make_unique<int[]>(_size)), _in_stack(std::make_unique<bool[]>(_size))
{
    clear(G);
    int current_vertex = 0;
}

void DirectedCycle::dfs(const DiGraph &G, int vertex)
{
    _marked[vertex] = true;
    _in_stack[vertex] = true;

    auto &adj = G.getLink(vertex);
    for (int cur_vertex : adj)
    {
        if (_inCycle)
            return;
        else if (!_marked[cur_vertex])
        {
            _prv[cur_vertex] = vertex;
            dfs(G, cur_vertex);
        }
        else if (_in_stack[cur_vertex])
        {
            _inCycle = true;
            int tmp_vertex = vertex;
            do
            {
                _cycle.push(tmp_vertex);
                tmp_vertex = _prv[tmp_vertex];
            } while (tmp_vertex != vertex);
        }
    }
    _in_stack[vertex] = false;
}

void DirectedCycle::clear(const DiGraph &G)
{
    for (int v = 0; v < G.getNumVertices(); v++)
    {
        _marked[v] = false;
        _prv[v] = v;
        _in_stack[v] = false;
    }
}