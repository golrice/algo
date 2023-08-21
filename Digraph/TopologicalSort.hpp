#pragma once

#include "DirectedOrder.hpp"
#include "DirectedCycle.hpp"
#include <stack>

class Topological
{
public:
    Topological(const DiGraph &graph);
    ~Topological() = default;
    void print() const;

private:
    std::stack<int> _topo_order;
};

Topological::Topological(const DiGraph &graph)
{
    DirectedCycle cycle(graph);

    if (!cycle.hasCycle())
    {
        DirectedOrder order(graph);
        _topo_order = order.getRearOrder();
    }
}

void Topological::print() const
{
    while (!_topo_order.empty())
        for (int i : _topo_order)
            std::cout << i << " ";
}