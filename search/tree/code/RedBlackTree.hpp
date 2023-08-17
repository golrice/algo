#include <stdexcept>
#include <iostream>
#include <deque>
#include <cstring>

// 红黑树
template <typename K, typename V>
class RedBlackBST
{
public:
    using KeyType = K;
    using ValueType = V;

private:
    struct Node
    {
    public:
        enum Color
        {
            RED,
            BLACK
        };

    public:
        // 存储需要的键值对
        KeyType _key;
        ValueType _value;
        // 表示以该节点为根节点的树的大小
        int _size;
        // 表示存储的子节点
        Node *_lchild, *_rchild;
        // 节点的颜色
        Color _color;

    public:
        Node(KeyType key = 0, ValueType value = 0, Color color = Color::BLACK, Node *left_child = nullptr, Node *right_child = nullptr, int size = 1)
            : _key(key), _value(value), _size(size), _lchild(left_child), _rchild(right_child), _color(color)
        {
        }
    };

private:
    Node *_root;

private:
    bool isRed(Node *root);
    Node *rotateLeft(Node *root);
    Node *rotateRight(Node *root);
    void flipColorDivide(Node *root);
    void flipColorCombine(Node *root);
    Node *moveRedLeft(Node *root);
    Node *moveRedRight(Node *root);
    Node *balanceLeft(Node *root);
    Node *balanceRight(Node *root);
    Node *split(Node *root);

private:
    // 返回树的大小
    int size(Node *root);
    // 更新树的大小
    int updateSize(Node *root);
    // 插入一个键值对
    Node *put(Node *root, KeyType Key, ValueType value);
    // 通过键来获得值 若不存在则会抛出异常
    ValueType get(Node *root, KeyType key);
    // 获得最大的键
    KeyType maxKey(Node *root);
    // 获得最小的键
    KeyType minKey(Node *root);
    // 最大的节点
    Node *maxNode(Node *root);
    // 最小的节点
    Node *minNode(Node *root);
    // 获得恰好比该键大的键
    Node *ceilingNode(Node *root, KeyType key);
    // 获得恰好比该键小的键
    Node *floorNode(Node *root, KeyType key);
    // 通过键来删除对应键值对
    Node *erase(Node *root, KeyType key);
    // 移除最小的键
    Node *earseMin(Node *root);
    // 移除最大的键
    Node *earseMax(Node *root);
    // 查询当前键的排名 也就是有多少键比它小
    int rank(Node *root, KeyType key);
    // 获取排名为k的键
    KeyType select(Node *root, int k);
    // 展示所有的键值对
    void display_head(Node *root);
    // 删除树
    void clear(Node *root);
    // 显示树的高度
    int height(Node *root);
    // 黑色高度
    int blackHeight(Node *root);
    // 构造正常
    bool isWellConstruct(Node *root);

public:
    RedBlackBST() : _root(nullptr) {}
    ~RedBlackBST()
    {
        clear(_root);
    }

public:
    bool isWellConstruct()
    {
        return isWellConstruct(_root);
    }
    int height(void)
    {
        int h = 0;
        h = height(_root);

        return h;
    }
    Node *put(KeyType key, ValueType value)
    {
        _root = put(_root, key, value);
        // 保证根节点始终都是黑色节点
        _root->_color = Node::BLACK;
        return _root;
    }

    ValueType get(KeyType key)
    {
        try
        {
            return get(_root, key);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return 0;
    }

    KeyType maxKey(void)
    {
        KeyType ans;
        try
        {
            ans = maxKey(_root);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return ans;
    }

    KeyType minKey(void)
    {
        KeyType ans;
        try
        {
            ans = minKey(_root);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return ans;
    }
    Node *ceilingNode(KeyType key)
    {
        try
        {
            return ceilingNode(_root, key);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return nullptr;
    }
    Node *floorNode(KeyType key)
    {
        try
        {
            return floorNode(_root, key);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return nullptr;
    }
    void erase(KeyType key)
    {
        try
        {
            if (!isRed(_root->_lchild) && !isRed(_root->_rchild))
                _root->_color = Node::RED;

            _root = erase(_root, key);

            if (!isEmpty())
                _root->_color = Node::BLACK;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void earseMin(void)
    {
        if (_root == nullptr)
            return;
        try
        {
            if (!isRed(_root->_lchild) && !isRed(_root->_rchild))
                _root->_color = Node::RED;

            _root = earseMin(_root);

            if (!isEmpty())
                _root->_color = Node::BLACK;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void earseMax(void)
    {
        if (_root == nullptr)
            return;
        try
        {
            if (!isRed(_root->_lchild) && !isRed(_root->_rchild))
                _root->_color = Node::RED;

            _root = earseMax(_root);

            if (!isEmpty())
                _root->_color = Node::BLACK;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    // 查询是否存在一组键值对
    bool contain(KeyType key)
    {
        return get(key) != nullptr;
    }
    // 查询是否为空表
    bool isEmpty(void)
    {
        return _root == nullptr;
    }
    // 获取当前表的大小 即键值对数量
    int size(void)
    {
        return size(_root);
    }
    int rank(KeyType key)
    {
        return rank(_root, key);
    }
    KeyType select(int k)
    {
        try
        {
            return select(_root, k);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return 0;
    }
    void display_head()
    {
        if (_root == nullptr)
        {
            std::cout << "empty tree!\n";
            return;
        }
        display_head(_root);
    }
};

template <typename K, typename V>
void RedBlackBST<K, V>::clear(Node *root)
{
    if (root == nullptr)
        return;

    clear(root->_lchild);
    clear(root->_rchild);
    //    std::cout << "rest = " << --(_root->_size) << '\n';
    delete root;
}

template <typename K, typename V>
bool RedBlackBST<K, V>::isRed(Node *root)
{
    if (root == nullptr)
        return false;

    return root->_color == Node::RED;
}

// 返回树的大小
template <typename K, typename V>
int RedBlackBST<K, V>::size(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->_size;
}

template <typename K, typename V>
int RedBlackBST<K, V>::updateSize(Node *root)
{
    return root->_size = size(root->_lchild) + size(root->_rchild) + 1;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::rotateLeft(Node *root)
{
    if (root == nullptr)
        return nullptr;

    Node *tmpNode = root;
    root = root->_rchild;

    tmpNode->_rchild = root->_lchild;
    root->_lchild = tmpNode;

    root->_color = tmpNode->_color;
    tmpNode->_color = Node::RED;

    root->_size = tmpNode->_size;
    updateSize(tmpNode);

    return root;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::rotateRight(Node *root)
{
    if (root == nullptr)
        return nullptr;

    Node *tmpNode = root;
    root = root->_lchild;

    tmpNode->_lchild = root->_rchild;
    root->_rchild = tmpNode;

    root->_color = tmpNode->_color;
    tmpNode->_color = Node::RED;

    root->_size = tmpNode->_size;
    updateSize(tmpNode);

    return root;
}

template <typename K, typename V>
void RedBlackBST<K, V>::flipColorDivide(Node *root)
{
    root->_color = Node::RED;
    root->_lchild->_color = Node::BLACK;
    root->_rchild->_color = Node::BLACK;
}

template <typename K, typename V>
void RedBlackBST<K, V>::flipColorCombine(Node *root)
{
    root->_color = Node::BLACK;
    root->_lchild->_color = Node::RED;
    root->_rchild->_color = Node::RED;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::balanceLeft(Node *root)
{
    if (root == nullptr)
        return nullptr;

    if (isRed(root->_rchild))
        root = rotateLeft(root);

    return split(root);
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::balanceRight(Node *root)
{
    if (root == nullptr)
        return nullptr;

    if (isRed(root->_lchild))
        root = rotateRight(root);

    return split(root);
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::split(Node *root)
{
    if (!isRed(root->_lchild) && isRed(root->_rchild))
        root = rotateLeft(root);
    if (isRed(root->_lchild) && isRed(root->_lchild->_lchild))
        root = rotateRight(root);
    if (isRed(root->_lchild) && isRed(root->_rchild))
        flipColorDivide(root);

    updateSize(root);

    return root;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::moveRedLeft(Node *root)
{
    // root should be red
    flipColorCombine(root);
    if (isRed(root->_rchild->_lchild))
    {
        root->_rchild = rotateRight(root->_rchild);
        root = rotateLeft(root);
    }

    return root;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::moveRedRight(Node *root)
{
    flipColorCombine(root);
    if (isRed(root->_lchild->_lchild))
    {
        root = rotateRight(root);
    }

    return root;
}

/*
函数功能:
提供一个根节点地址 这个根节点对应的树插入一个新节点并且更新信息
函数返回值:
返回已经插入了节点的根节点
*/
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::put(RedBlackBST<K, V>::Node *root, RedBlackBST<K, V>::KeyType key, RedBlackBST<K, V>::ValueType value)
{
    if (root == nullptr)
        return new Node(key, value, Node::RED);

    if (key < root->_key)
        root->_lchild = put(root->_lchild, key, value);
    else if (key > root->_key)
        root->_rchild = put(root->_rchild, key, value);
    else
        root->_value = value;

    // 插入后的解开临时的四节点
    return split(root);
}

/*
函数功能:
提供一个根节点代表的树 查找是否存在一个节点的键是key 若存在则返回该键 若不存在则抛出异常
主要是锻炼能力
函数返回值:
返回键是key的节点
*/
template <typename K, typename V>
typename RedBlackBST<K, V>::ValueType RedBlackBST<K, V>::get(typename RedBlackBST<K, V>::Node *root, RedBlackBST<K, V>::KeyType key)
{
    if (root == nullptr)
        throw std::invalid_argument("no such key in the tree.\n");

    if (root->_key > key)
        return get(root->_lchild, key);
    else if (root->_key < key)
        return get(root->_rchild, key);
    else
        return root->_value;
}

/*
函数功能:
找到最大的key 若树为空树 则会抛出异常 否则返回最大key
函数返回值:
最大的key
*/
template <typename K, typename V>
typename RedBlackBST<K, V>::KeyType RedBlackBST<K, V>::maxKey(typename RedBlackBST<K, V>::Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    if (root->_rchild != nullptr)
        return maxKey(root->_rchild);

    return root->_key;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::KeyType RedBlackBST<K, V>::minKey(typename RedBlackBST<K, V>::Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    if (root->_lchild != nullptr)
        return minKey(root->_lchild);

    return root->_key;
}
// 最大的节点
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::maxNode(Node *root)
{
    if (root == nullptr)
        return nullptr;

    while (root->_rchild != nullptr)
        root = root->_rchild;

    return root;
}

// 最小的节点
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::minNode(Node *root)
{
    if (root == nullptr)
        return nullptr;

    if (root->_lchild != nullptr)
        return minNode(root->_lchild);

    return root;
}

/*
函数功能:
找到一个键 恰好小于目标键
*/
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::floorNode(typename RedBlackBST<K, V>::Node *root, typename RedBlackBST<K, V>::KeyType key)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    Node *tmpNode = root;
    Node *ans = root;
    while (tmpNode != nullptr)
    {
        if (tmpNode->_key < key && tmpNode->_key > ans->_key)
            ans = tmpNode;

        if (key > tmpNode->_key)
        {
            if (tmpNode->_rchild == nullptr)
                break;
            tmpNode = tmpNode->_rchild;
        }
        else
        {
            if (tmpNode->_lchild == nullptr)
                break;
            tmpNode = tmpNode->_lchild;
        }
    }

    if (ans->_key >= key)
        throw std::invalid_argument("no floor");

    return ans;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::ceilingNode(typename RedBlackBST<K, V>::Node *root, typename RedBlackBST<K, V>::KeyType key)
{
    if (root == nullptr)
        throw std::invalid_argument("no such key");

    RedBlackBST<K, V>::Node *tmp = nullptr;
    if (root->_key > key && root->_lchild != nullptr)
        tmp = ceilingNode(root->_lchild, key);
    else if (root->_key <= key)
        return ceilingNode(root->_rchild, key);

    if (tmp != nullptr && tmp->_key > key)
        root = tmp;

    return root;
}

// 通过键来删除对应键值对
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::erase(Node *root, KeyType key)
{
    if (root == nullptr)
        return nullptr;

    if (key < root->_key)
    {
        if (!isRed(root->_lchild) && !isRed(root->_lchild->_lchild))
            root = moveRedLeft(root);
        root->_lchild = erase(root->_lchild, key);
    }
    else if (key > root->_key)
    {
        if (!isRed(root->_rchild) && !isRed(root->_rchild->_lchild))
            root = moveRedRight(root);
        root->_rchild = erase(root->_rchild, key);
    }
    else
    {
        if (root->_lchild != nullptr)
        {
            Node *tmp = maxNode(root->_lchild);
            root->_key = tmp->_key;
            root->_value = tmp->_value;
            root->_lchild = earseMax(root->_lchild);
        }
        else if (root->_rchild != nullptr)
        {
            Node *tmp = minNode(root->_rchild);
            root->_key = tmp->_key;
            root->_value = tmp->_value;
            root->_rchild = earseMin(root->_rchild);
        }
        else
        {
            delete root;
            return nullptr;
        }
    }

    return balanceLeft(root);
}

// 移除最小的键
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::earseMin(Node *root)
{
    if (root == nullptr)
        return nullptr;

    if (root->_lchild == nullptr)
    {
        delete root;
        return nullptr;
    }

    if (!isRed(root->_lchild) && !isRed(root->_lchild->_lchild))
        root = moveRedLeft(root);

    root->_lchild = earseMin(root->_lchild);

    return balanceLeft(root);
}

// 移除最大的键 并且返回该树
template <typename K, typename V>
typename RedBlackBST<K, V>::Node *RedBlackBST<K, V>::earseMax(Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("no such key");

    if (root->_rchild == nullptr)
    {
        Node *tmpNode = root->_lchild;
        delete root;
        if (tmpNode != nullptr)
            tmpNode->_color = Node::BLACK;
        return tmpNode;
    }

    if (!isRed(root->_rchild) && !isRed(root->_rchild->_lchild))
        moveRedRight(root);

    root->_rchild = earseMax(root->_rchild);

    return balanceLeft(root);
}

// 查询当前键的排名 也就是有多少键比它小
template <typename K, typename V>
int RedBlackBST<K, V>::rank(Node *root, KeyType key)
{
    if (root == nullptr)
        return 0;

    int sz = size(root->_lchild);
    if (root->_key < key)
        return sz + 1 + rank(root->_rchild, key);
    else if (root->_key > key)
        return rank(root->_lchild, key);
    else
        return sz + 1;
}

// 获取排名为k的键
template <typename K, typename V>
typename RedBlackBST<K, V>::KeyType RedBlackBST<K, V>::select(Node *root, int k)
{
    if (root == nullptr || root->_size < k)
        throw std::invalid_argument("wrong argument");

    int sz = size(root->_lchild);
    if (sz + 1 < k)
        return select(root->_rchild, k - sz - 1);
    else if (sz + 1 > k)
        return select(root->_lchild, k);
    else
        return root->_key;
}

// 展示所有的键值对
template <typename K, typename V>
void RedBlackBST<K, V>::display_head(Node *root)
{
    if (root == nullptr)
        return;

    std::cout << "key = " << root->_key << ", value = " << root->_value << ", size = " << root->_size << ".\n";
    display_head(root->_lchild);
    display_head(root->_rchild);
}

template <typename K, typename V>
int RedBlackBST<K, V>::height(Node *root)
{
    if (root == nullptr)
        return 0;

    int hl = height(root->_lchild);
    int hr = height(root->_rchild);
    return (hl > hr ? hl : hr) + 1;
}

template <typename K, typename V>
int RedBlackBST<K, V>::blackHeight(Node *root)
{
    if (root == nullptr)
        return 0;

    int add = (root->_color == Node::RED ? 0 : 1);
    if (root->_lchild != nullptr)
        return blackHeight(root->_lchild) + add;
    else
        return blackHeight(root->_rchild) + add;
}

template <typename K, typename V>
bool RedBlackBST<K, V>::isWellConstruct(Node *root)
{
    if (root == nullptr)
        return true;

    return blackHeight(root->_lchild) == blackHeight(root->_rchild);
}