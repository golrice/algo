#pragma once

#include <vector>
#include <queue>

namespace MinimalSpanningTree
{
    enum class ComparerType
    {
        Minimum,
        Maximum
    };

    template <typename T>
    class MutablePriorityQueue
    {
    public:
        using Value_Type = T;

    public:
        MutablePriorityQueue(void);
        void push(Value_Type value);
        void pop();
        void change(Value_Type pre_value, Value_Type new_value);
        bool contained(Value_Type value) const;
        Value_Type top() const { return _priority_queue[0]; }
        bool empty() const { return _size == 0; }
        int size() const { return _size; }

    private:
        int lchild(int pos) const { return 2 * pos + 1; }
        int rchild(int pos) const { return 2 * pos + 2; }
        int parent(int pos) const { return (pos - 1) / 2; }
        void swim(int pos);
        void sink(int pos);

    private:
        std::vector<Value_Type> _priority_queue;
        ComparerType _comparer_type;
        int _size;
    };
}

template <typename T>
MinimalSpanningTree::MutablePriorityQueue<T>::MutablePriorityQueue(void)
    : _comparer_type(ComparerType::Minimum), _size(0)
{
}

template <typename T>
void MinimalSpanningTree::MutablePriorityQueue<T>::swim(int pos)
{
    int value = _priority_queue[pos];
    while (pos > 0 && _priority_queue[parent(pos)] > value)
    {
        _priority_queue[pos] = _priority_queue[parent(pos)];
        pos = parent(pos);
    }
    _priority_queue[pos] = value;
}

template <typename T>
void MinimalSpanningTree::MutablePriorityQueue<T>::sink(int pos)
{
    int value = _priority_queue[pos];
    while (lchild(pos) < _size)
    {
        if (rchild(pos) < _size && _priority_queue[rchild(pos)] < _priority_queue[pos])
        {
            _priority_queue[pos] = _priority_queue[rchild(pos)];
            pos = rchild(pos);
        }
        else if (_priority_queue[lchild(pos)] < _priority_queue[pos])
        {
            _priority_queue[pos] = _priority_queue[lchild(pos)];
            pos = lchild(pos);
        }
        else
            break;
    }
    _priority_queue[pos] = value;
}

template <typename T>
void MinimalSpanningTree::MutablePriorityQueue<T>::push(Value_Type value)
{
    _priority_queue.push_back(value);
    _size++;
    swim(_size - 1);
}

template <typename T>
void MinimalSpanningTree::MutablePriorityQueue<T>::pop()
{
    _priority_queue[0] = _priority_queue[_size - 1];
    _size--;
    sink(0);
}

template <typename T>
void MinimalSpanningTree::MutablePriorityQueue<T>::change(Value_Type pre_value, Value_Type new_value)
{
    for (int pos = 0; pos < _size; pos++)
    {
        if (_priority_queue[pos] == pre_value)
        {
            _priority_queue[pos] = new_value;
            swim(pos);
            sink(pos);
            break;
        }
    }
}

template <typename T>
bool MinimalSpanningTree::MutablePriorityQueue<T>::contained(Value_Type value) const
{
    for (int pos = 0; pos < _size; pos++)
    {
        if (_priority_queue[pos] == value)
            return true;
    }
    return false;
}