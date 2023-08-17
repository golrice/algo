#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Union_find
{
public:
    // 检查一个整数对是否连接
    bool isConnected(const int a, const int b);
    // 添加整数对之间的连接
    void add_union(const int a, const int b);
    // 统计连接数量
    int count();
    // 展示连接的数字
    void show();
    // 构造函数
    Union_find() = delete;
    Union_find(int min, int max)
        : _offset(max - min), _element(_offset), _size(_offset), _numberOfConnection(_offset)
    {
        for (int i = 0; i < _offset; ++i)
        {
            _element[i] = i;
            _size[i] = 1;
        }
    }

private:
    int find(const int a, const int ofs);

private:
    // 最小值与最大值的差值作为偏移量
    int _offset;
    // 存储连通信号
    std::vector<int> _element;
    // 记录连接树的大小
    std::vector<int> _size;
    // 记录当前连通的数量
    int _numberOfConnection;
};

// 主要需要压缩寻找路径 降低树的高度
int Union_find::find(const int a, const int ofs)
{
    // 查找树的根结点
    int end = a - ofs;
    // 每一次提高该路径上叶子节点的高度
    for (; _element[end] != end; end = _element[end])
    {
        _element[end] = _element[_element[end]];
    }
    return end;
}

bool Union_find::isConnected(const int a, const int b)
{
    return find(a, _offset) == find(b, _offset);
}

void Union_find::add_union(const int a, const int b)
{
    int rootA = find(a, _offset);
    int rootB = find(b, _offset);

    if (rootA == rootB)
        return;

    if (_size[rootA] < _size[rootB])
    {
        _element[rootA] = rootB;
        _size[rootB] += _size[rootA];
    }
    else
    {
        _element[rootB] = rootA;
        _size[rootA] += _size[rootB];
    }

    _numberOfConnection--;
}

int Union_find::count()
{
    return _numberOfConnection;
}

void Union_find::show()
{
    std::vector<bool> isShowed(_offset, false);

    for (int i = 0; i < _offset; ++i)
    {
        if (isShowed[i])
            continue;

        int end = find(i, 0);
        std::cout << i + _offset << ' ';
        isShowed[i] = true;

        for (int j = i + 1; j < _offset; ++j)
        {
            if (end == find(j, 0))
            {
                std::cout << j + _offset << ' ';
                isShowed[j] = true;
            }
        }
        std::cout << '\n';
    }
}

constexpr int min = 0;
constexpr int max = 100;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    Union_find object(min, max);

    for (int i = 0; i < 10; ++i)
    {
        object.add_union(rand() % (max - min) + min, rand() % (max - min) + min);
    }

    object.show();

    int a, b;
    std::cout << "a pair of number to test: " << std::endl;
    while (!(std::cin >> a >> b))
    {
        std::cout << "Enter again! \n";
        while (std::cin.get() != '\n')
            continue;
    }

    std::cout << object.isConnected(a, b);

    return 0;
}