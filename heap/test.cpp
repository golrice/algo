#include <iostream>

template <typename T>
void display(T *arr, int N)
{
    for (int i = 0; i < N; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}

int main(void)
{
    constexpr int size = 10;
    int arr[size] = {0};
    for (int i = 0; i < size; ++i)
        arr[i] = 9 - i;
    return 0;
}
