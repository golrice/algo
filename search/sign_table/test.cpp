#include <iostream>
#include <cstdlib>
#include <ctime>

// 基本符号表API设计
template <typename K, typename V>
class orderedSignTable
{
public:
    using KeyType = K;
    using ValueType = V;

public:
    // 构造函数采用default形式 重点在于API的设计
    orderedSignTable() = default;
    ~orderedSignTable() = default;

    // 插入一个键值对
    void put(KeyType key, ValueType value);

    // 通过键来获得值 若不存在则会抛出异常
    ValueType get(KeyType key);
    // 获得最大的键
    KeyType maxKey(void);
    // 获得最小的键
    KeyType minKey(void);
    // 获得恰好比该键大的键
    KeyType ceilingKey(KeyType key);
    // 获得恰好比该键小的键
    KeyType floorKey(KeyType key);

    // 通过键来删除对应键值对
    void erase(KeyType key);
    // 删除最小键
    void earseMin(void);
    // 删除最大键
    void earseMax(void);

    // 查询是否存在一组键值对
    bool contain(KeyType key);
    // 查询是否为空表
    bool isEmpty(void);
    // 获取当前表的大小 即键值对数量
    int size(void);
    // 查询当前键的排名 也就是有多少键比它小
    int rank(KeyType key);
    // 获取排名为k的键
    KeyType select(int k);
};

void func(int N)
{
    int a[N];
    std::cout << N << std::endl;
    return;
}

int main(void)
{
    // 随机化种子
    srand(time(nullptr));
    // 希望测试的案例大小
    constexpr int sizeOfData = 10;
    // 构造一个有序符号表
    orderedSignTable<int, int> st;

    int another;
    std::cin >> another;

    func(another);

    return 0;
}