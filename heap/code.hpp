#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

template <typename T>
class MaxBinaryHeap
{
public:
    MaxBinaryHeap(const std::vector<T> &elements);
    void insert(const T &element);
    T &max() const;
    void delMax();
    static void sort(std::vector<T> &elements);

private:
    // 将目标元素进行上浮
    void swim(int target);
    // 将目标元素进行下沉
    void sink(int target);
    // 交换元素
    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = a;
    }

    int index_lchild(int p) { return p * 2; }
    int index_rchild(int p) { return p * 2 + 1; }
    int index_parent(int c) { return c / 2; }
    bool have_lchild(int p) { return index_lchild(p) < _element.size(); }
    bool have_rchild(int p) { return index_rchild(p) < _element.size(); }
    bool have_child(int p) { return have_lchild(p) && have_rchild(p); }
    bool have_parent(int c) { return c > 1; }

private:
    std::vector<T> _element;
};

template <typename T>
void MaxBinaryHeap<T>::swim(int target)
{
    while (have_parent(target) && _element[target] > _element[index_parent(target)])
    {
        swap(_element[target], _element[index_parent(target)]);
        target = index_parent(target);
    }
}

template <typename T>
void MaxBinaryHeap<T>::sink(int target)
{
    while (have_lchild(target))
    {
        int index_exchange = index_lchild(target);
        if (have_rchild(target) && _element[index_rchild(target)] > _element[index_exchange])
            index_exchange = index_rchild(target);

        if (_element[target] >= _element[index_exchange])
            break;

        swap(_element[target], _element[index_exchange]);
        target = index_exchange;
    }
}

template <typename T>
MaxBinaryHeap<T>::MaxBinaryHeap(const std::vector<T> &v) : _element(v)
{
}

template <typename T>
void MaxBinaryHeap<T>::insert(const T &element)
{
    _element.push_back(element);
    swim(_element.size());
}

template <typename T>
T &MaxBinaryHeap<T>::max() const
{
    return _element.at(1);
}

template <typename T>
void MaxBinaryHeap<T>::delMax()
{
    _element.at(1) = _element[_element.size()];
    _element.pop_back();
    sink(1);
}

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T, int N>
void sink(T (&element)[N], int begin, int end, bool (*com)(T &, T &))
{
    int lchild = begin * 2 + 1;
    while ((lchild = begin * 2 + 1) <= end)
    {
        int index_exchange = lchild;
        if (lchild + 1 <= end && com(element[lchild], element[lchild + 1]))
            index_exchange = lchild + 1;
        if (com(element[index_exchange], element[begin]))
            break;
        swap(element[begin], element[index_exchange]);
        begin = index_exchange;
    }
}

template <typename T, int N>
void heapSort(T (&element)[N], bool (*com)(T &, T &))
{
    // 构造堆结构
    for (int i = N / 2; i >= 0; --i)
        sink(element, i, N, com);
    // 每次将目标值放到堆的最后一个元素 然后将其位置从可改变范围去除
    for (int times = N - 1; times >= 1;)
    {
        swap(element[0], element[times--]);
        sink(element, 0, times, com);
    }
    // 每次都是当前最大值或者最小值放到可改变范围的末尾
    for (int i = 0; i < N; ++i)
        std::cout << element[i] << ' ';
    std::cout << '\n';
}

bool compare(int &a, int &b)
{
    return a < b;
}

// 检测是否正确构造一个小根堆
// 传入的数组应该是要求所有位置都要使用
// 也就是arr[0]的位置是根节点
bool isWellConstrucet(int *arr, int N)
{
    int endParentPos = N / 2;
    for (int i = 0; i < endParentPos; ++i)
    {
        if (i * 2 + 2 < N)
        {
            if (arr[i] > arr[i * 2 + 1] || arr[i] > arr[i * 2 + 2])
                return false;
        }
        else if (i * 2 + 1 < N)
        {
            if (arr[i] > arr[i * 2 + 1])
                return false;
        }
    }
    return true;
}

// 减少子节点存在性判断次数 减少元素移动次数
template <typename T, int N>
void sink_improve(T (&arr)[N], int begin, int end, bool (*com)(T &, T &))
{
    auto lchild = [](int parent)
    { return parent * 2 + 1; };
    auto rchild = [&lchild](int parent)
    { return lchild(parent) + 1; };

    // 减少判断次数思路 优先判断是否存在右子节点
    // 若存在 则双节点都存在
    // 若不存在 则可能存在左子节点或者无子节点

    T tmp = arr[begin];
    while (rchild(begin) < end)
    {
        int index_exchange = com(arr[lchild(begin)], arr[rchild(begin)]) ? lchild(begin) : rchild(begin);

        // 优化swap中需要多次使用临时值存储的问题
        if (com(tmp, arr[index_exchange]))
        {
            arr[begin] = tmp;
            return;
        }

        arr[begin] = arr[index_exchange];
        begin = index_exchange;
    }
    if (lchild(begin) < end)
    {
        arr[begin] = arr[lchild(begin)];
        arr[lchild(begin)] = tmp;
    }
    else
    {
        arr[begin] = tmp;
    }
}

// 优化临时变量数量
template <typename T, int N, typename U>
void swim_improve(T (&arr)[N], int end, U com)
{
    auto parentIndex = [](int child)
    { return (child - 1) / 2; };

    T tmp = arr[end];
    while (parentIndex(end) >= 0)
    {
        if (com(arr[parentIndex(end)], tmp))
            break;

        arr[end] = arr[parentIndex(end)];
        end = parentIndex(end);
    }
    arr[end] = tmp;
}

// 构造堆
// 接受一个数组，将数组按照小根堆原则构造
// 数据修改范围[begin, end)
template <typename T, int N>
void construct(T (&arr)[N], bool (*com)(T &, T &))
{
    // 从最后一个元素开始进行sink操作构造
    // 最后一列的元素没有子节点，也就不需要更多的sink
    for (int i = N / 2; i >= 0; --i)
        sink(arr, i, N, com);
}

// 构造索引优先队列的数据结构
// 优点在于 可以使用索引直接绑定元素
// 通过索引可以快速修改元素的值
template <typename T>
class indexPriorityQueue
{
public:
    // 用index与插入元素进行绑定 可以通过index直接访问元素
    void insert(int index, T key);
    // 展示函数 用来检测是否正确
    void show() const;
    // index下标访问
    T operator[](int index) { return _key[index]; }
    // 修改下标为index的元素并且整理排序
    void change(int index, T key);
    // 获得最小值
    T minKey() const {return _key[_priority[0]]};
    // 删除最小值
    void delMinKey();

private:
    void sink(int begin);
    void swim(int end);
    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
    // 传递在priority的位置
    void exchange_priority(int a, int b);

private:
    // 元素数组
    int *_key;
    // 优先级数组
    int *_priority;
    // 逆优先级数组
    int *_opposite;
    // 元素个数
    int _size;
};

template <typename T>
void indexPriorityQueue<T>::sink(int begin)
{
    // 实际上只对priority部分进行堆有序排列
    // priority意义是 被优先级所排列 内部元素是index
    // opposite意义是 记录对应index的优先级
    // 实际上步骤是一样的
    // 通过对key优先级将priority进行排列
    // 不过在排列过程中的exchange过程中
    // 需要同时修改opposite指向的优先级大小
}

template <typename T>
void indexPriorityQueue<T>::swim(int end)
{
    // 参考上文
}

// 所以只需要修改exchange部分即可 重点在此
// 此处传递的是在priority中的位置 这是因为服务于sink与swim的
template <typename T>
void indexPriorityQueue<T>::exchange_priority(int a, int b)
{
    // 元素数组记录的是对应index的元素 所以不需要修改
    // priority数组是需要根据key大小排序的数组 需要exchange
    // opposite是对应priority的大小 需要update

    // 交换这两个元素对应index中指向的原先优先级
    _opposite[_priority[a]] = b;
    _opposite[_priority[b]] = a;
    // 交换这两个元素的优先值
    swap(_priority[a], _priority[b]);
}

template <typename T>
void indexPriorityQueue<T>::insert(int index, T key)
{
    _key[index] = key;
    _priority[_size] = index;
    _opposite[index] = _size;

    swim(_size++);
}

template <typename T>
void indexPriorityQueue<T>::change(int index, T key)
{
    _key[index] = key;
    swim(_opposite[index]);
    sink(_opposite[index]);
}

template <typename T>
void indexPriorityQueue<T>::show() const
{
}

template <typename T>
T indexPriorityQueue<T>::minKey() const
{
    return _key[_priority[0]];
}

template <typename T>
void indexPriorityQueue<T>::delMinKey()
{
    swap(_priority[0], _priority[--_size]);
    // 此处是将对应的key的记录给删除
    // 懒惰删除可以选择直接不管
    // 也可以调用该对象的析构函数
    _key[_priority[_size + 1]].~T();
    _opposite[_priority[_size + 1]] = -1;
    sink(0);
}