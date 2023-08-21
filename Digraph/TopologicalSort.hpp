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
        _topo_order = order.getReverseOrder();
    }
}

void Topological::print() const
{
    std::stack<int> tmp_stack = _topo_order;
    while (!tmp_stack.empty())
    {
        std::cout << tmp_stack.top() << " ";
        tmp_stack.pop();
    }
}