#include <stdexcept>
#include <iostream>
#include <deque>

// 基本二叉树
template <typename K, typename V>
class BinaryTree
{
public:
    using KeyType = K;
    using ValueType = V;

private:
    struct Node
    {
    public:
        // 存储需要的键值对
        KeyType _key;
        ValueType _value;
        // 表示以该节点为根节点的树的大小
        int _size;
        // 表示存储的子节点
        Node *_lchild, *_rchild;

    public:
        Node(KeyType key = 0, ValueType value = 0, int size = 1, Node *left_child = nullptr, Node *right_child = nullptr)
            : _key(key), _value(value), _size(size), _lchild(left_child), _rchild(right_child)
        {
        }
    };

    // 数据存储区域
private:
    Node *_root;

public:
    BinaryTree() : _root(nullptr) {}

private:
    // 返回树的大小
    int size(Node *root);
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

public:
    Node *put(KeyType key, ValueType value)
    {
        return (_root = put(_root, key, value));
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
        try
        {
            return maxKey(_root);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    KeyType minKey(void)
    {
        try
        {
            return minKey(_root);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
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
            _root = erase(_root, key);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void earseMin(void)
    {
        try
        {
            _root = earseMin(_root);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void earseMax(void)
    {
        try
        {
            _root = earseMax(_root);
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

// 返回树的大小
template <typename K, typename V>
int BinaryTree<K, V>::size(Node *root)
{
    if (root == nullptr)
        return 0;
    return root->_size;
}

/*
函数功能:
提供一个根节点地址 这个根节点对应的树插入一个新节点并且更新信息
函数返回值:
返回已经插入了节点的根节点
*/
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::put(typename BinaryTree<K, V>::Node *root, BinaryTree<K, V>::KeyType key, BinaryTree<K, V>::ValueType value)
{
    if (root == nullptr)
        return new Node(key, value);

    Node *tmpNode = root;
    std::deque<Node *> dq;

    while (tmpNode->_key != key)
    {
        dq.push_back(tmpNode);

        if (key < tmpNode->_key)
        {
            if (tmpNode->_lchild == nullptr)
                tmpNode->_lchild = new Node(key, value);

            tmpNode = tmpNode->_lchild;
        }
        else if (key > tmpNode->_key)
        {
            if (tmpNode->_rchild == nullptr)
                tmpNode->_rchild = new Node(key, value);

            tmpNode = tmpNode->_rchild;
        }
    }

    for (auto &i : dq)
        i->_size++;

    return root;
}

/*
函数功能:
提供一个根节点代表的树 查找是否存在一个节点的键是key 若存在则返回该键 若不存在则抛出异常
主要是锻炼能力
函数返回值:
返回键是key的节点
*/
template <typename K, typename V>
typename BinaryTree<K, V>::ValueType BinaryTree<K, V>::get(typename BinaryTree<K, V>::Node *root, BinaryTree<K, V>::KeyType key)
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
typename BinaryTree<K, V>::KeyType BinaryTree<K, V>::maxKey(typename BinaryTree<K, V>::Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    if (root->_rchild != nullptr)
        return maxKey(root->_rchild);

    return root->_key;
}

template <typename K, typename V>
typename BinaryTree<K, V>::KeyType BinaryTree<K, V>::minKey(typename BinaryTree<K, V>::Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    if (root->_lchild != nullptr)
        return maxKey(root->_lchild);

    return root->_key;
}
// 最大的节点
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::maxNode(Node *root)
{
    if (root == nullptr)
        return nullptr;

    while (root->_rchild != nullptr)
        root = root->_rchild;

    return root;
}

// 最小的节点
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::minNode(Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    if (root->_lchild != nullptr)
        return minNode(root->_lchild);

    return root;
}

/*
函数功能:
找到一个键 恰好小于目标键
*/
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::floorNode(typename BinaryTree<K, V>::Node *root, typename BinaryTree<K, V>::KeyType key)
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
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::ceilingNode(typename BinaryTree<K, V>::Node *root, typename BinaryTree<K, V>::KeyType key)
{
    if (root == nullptr)
        throw std::invalid_argument("no such key");

    BinaryTree<K, V>::Node *tmp = nullptr;
    if (root->_key > key && root->_lchild != nullptr)
        tmp = ceilingNode(root->_lchild, key);
    else if (root->_key <= key && root->_rchild != nullptr)
        return ceilingNode(root->_rchild, key);

    if (tmp != nullptr && tmp->_key > key)
        root = tmp;

    if (root->_key < key)
        throw std::invalid_argument("it is the ceiling!");

    return root;
}

// 通过键来删除对应键值对
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::erase(Node *root, KeyType key)
{
    Node *tmpNode = root;
    std::deque<Node *> dq;

    while (tmpNode != nullptr)
    {
        if (key != tmpNode->_key)
        {
            dq.emplace_back(tmpNode);

            if (key < tmpNode->_key)
                tmpNode = tmpNode->_lchild;
            else
                tmpNode = tmpNode->_rchild;
        }
        else
        {
            if (tmpNode->_lchild != nullptr && tmpNode->_rchild != nullptr)
            {
                Node *tmp = tmpNode;
                tmpNode = new Node(*(minNode(tmp->_rchild)));
                tmpNode->_rchild = earseMin(tmp->_rchild);
                tmpNode->_lchild = tmp->_lchild;
                tmpNode->_size = size(tmpNode->_lchild) + size(tmpNode->_rchild) + 1;
                delete tmp;

                if (dq.empty())
                    return tmpNode;

                ((dq.back()->_key > tmpNode->_key) ? dq.back()->_lchild : dq.back()->_rchild) = tmpNode;
            }
            else
                ((dq.back()->_lchild == tmpNode) ? dq.back()->_lchild : dq.back()->_rchild) = ((tmpNode->_lchild != nullptr) ? tmpNode->_lchild : tmpNode->_rchild);

            for (auto &i : dq)
                --(i->_size);

            return root;
        }
    }

    return nullptr;
}

// 移除最小的键
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::earseMin(Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    if (root->_lchild != nullptr)
        root->_lchild = earseMin(root->_lchild);
    else
    {
        Node *tmp = root->_rchild;
        delete root;
        root = tmp;
    }

    if (root == nullptr)
        return nullptr;

    root->_size = size(root->_lchild) + size(root->_rchild) + 1;
    return root;
}

// 移除最大的键 并且返回该树
template <typename K, typename V>
typename BinaryTree<K, V>::Node *BinaryTree<K, V>::earseMax(Node *root)
{
    if (root == nullptr)
        throw std::invalid_argument("empty tree");

    Node *tmpNode = root;
    std::deque<Node *> dq;
    while (tmpNode->_rchild != nullptr)
    {
        dq.emplace_back(tmpNode);
        tmpNode = tmpNode->_rchild;
    }

    dq.back()->_rchild = tmpNode->_lchild;
    for (auto &i : dq)
        --(i->_size);
    delete tmpNode;

    return root;
}

// 查询当前键的排名 也就是有多少键比它小
template <typename K, typename V>
int BinaryTree<K, V>::rank(Node *root, KeyType key)
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
typename BinaryTree<K, V>::KeyType BinaryTree<K, V>::select(Node *root, int k)
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
void BinaryTree<K, V>::display_head(Node *root)
{
    if (root == nullptr)
        return;

    display_head(root->_lchild);
    std::cout << "key = " << root->_key << ", value = " << root->_value << ", size = " << root->_size << ".\n";
    display_head(root->_rchild);
}
