#pragma once
#include "Graph.hpp"
#include <queue>
#include <vector>
#include <stack>

// 实现广度优先搜索的数据结构
class BreadthFirstSearch
{
private:
    int _source;
    std::vector<int> _path;
    std::vector<bool> _visited;

public:
    BreadthFirstSearch(Graph &graph, int source);
    // 返回可迭代对象 用来表示从source到destination的路径
    std::stack<int> pathTo(int destination);
    // 修改 source, 表示对新source的广度优先搜索
    void bfs(const Graph &graph, int source);
};

BreadthFirstSearch::BreadthFirstSearch(Graph &graph, int source) : _source(source), _path(graph.size()), _visited(graph.size(), false)
{
    bfs(graph, source);
}

std::stack<int> BreadthFirstSearch::pathTo(int destination)
{
    std::stack<int> path;
    // 定义一个栈，用于存储路径
    int current_vertice = destination;
    // 将当前顶点设置为目标顶点
    while (current_vertice != _path[current_vertice])
    {
        // 将当前顶点压入栈中
        path.push(current_vertice);
        // 更新当前顶点
        current_vertice = _path[current_vertice];
    }
    // 将当前顶点压入栈中
    path.push(current_vertice);
    // 返回栈中的路径
    return path;
}

void BreadthFirstSearch::bfs(const Graph &graph, int source)
{
    _source = source;
    _path.resize(graph.size());
    _visited.resize(graph.size(), false);
    for (int i = 0; i < _path.size(); i++)
        _path[i] = i;

    // 初始化队列
    std::queue<int> queue;
    queue.push(_source);
    _visited[_source] = true;

    // 循环 将连接的元素push到队列中
    while (!queue.empty())
    {
        int current_vertice = queue.front();
        queue.pop();
        // 遍历当前元素的所有连接元素
        auto &adj_vertices = graph.adj(current_vertice);
        for (auto &vertice : adj_vertices)
        {
            // 如果访问过了 由于这里是无向图 不需要更新
            if (_visited[vertice])
                continue;

            // 否则更新
            _visited[vertice] = true;
            _path[vertice] = current_vertice;
            queue.push(vertice);
        }
    }
}

// 写一个测试函数用来检测广度优先搜索正确性
void test()
{
    Graph graph(8);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 6);
    graph.addEdge(5, 6);
    graph.addEdge(4, 7);
    graph.addEdge(4, 6);

    BreadthFirstSearch bfs(graph, 0);
    std::cout << "广度优先搜索结果" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << i << ": ";
        std::stack<int> path = bfs.pathTo(i);
        std::cout << path.top();
        path.pop();
        while (!path.empty())
        {
            std::cout << "->" << path.top();
            path.pop();
        }
        std::cout << std::endl;
    }
}