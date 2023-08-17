// 基于归位函数的抽象意义
// 将一个元素放置在正确排列后的位置 左侧都不大于该元素 右侧都小于该元素
// 只需要保证归位后元素所在位置是k-1的位置
// 就可以找到第k大或者第k小的元素
template <typename T>
int reposition(T *arr, int begin, int end)
{
    T tmp = arr[begin];
    while (begin < end)
    {
        while (begin <= end && tmp < arr[end])
            --end;
        arr[begin] = arr[end];
        while (begin <= end && tmp > arr[begin]
            ++begin;
        arr[end] = arr[begin];
    }
    arr[begin] = tmp;
    return begin;
}

template <typename T>
T select(T *arr, int N, int k)
{
    int position = -1;
    int begin = 0, end = N - 1;
    // 将一个元素归位并且查看归位后的索引
    // 若归位后的索引是 k-1 则选择完毕
    // 否则选择适当的区间 重复上面的过程
    do
    {
        position = reposition(arr, begin, end);
        // 往左侧寻找
        if (position > k - 1)
            end = position - 1;
        // 往右侧寻找
        else if (position < k - 1)
            begin = position + 1;
        // 找到了
        else
            return arr[position];
    } while (position != k - 1);
    return arr[position];
}