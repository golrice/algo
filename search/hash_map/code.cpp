#include <list>
#include <vector>
#include <array>
#include <stdexcept>
#include <optional>
#include <algorithm>
#include <iostream>

template <typename K, typename V>
class SignTable
{
public:
    using KeyType = K;
    using ValueType = V;

public:
    SignTable() {}
    virtual ~SignTable() {}

    // 插入一个键值对
    virtual void put(KeyType key, ValueType value) = 0;

    // 通过键来获得值 若不存在则会抛出异常
    virtual ValueType get(KeyType key) = 0;

    // 通过键来删除对应键值对
    virtual void erase(KeyType key) = 0;

    // 查询是否存在一组键值对
    virtual bool contained(KeyType key, ValueType value) = 0;
    // 查询是否为空表
    virtual bool isEmpty(void) = 0;
    // 获取当前表的大小 即键值对数量
    virtual int size(void) = 0;
};

template <typename K, typename V>
class SeparateChainingHashMap : public SignTable<K, V>
{
public:
    using typename SignTable<K, V>::KeyType;
    using typename SignTable<K, V>::ValueType;

private:
    struct Node
    {
        KeyType _key;
        ValueType _value;
        Node(void) : _key(0), _value(0) {}
        Node(KeyType key, ValueType value) : _key(key), _value(value) {}
    };

private:
    static std::array<int, 10> _sizeOfVector;
    std::vector<std::list<Node>> _table;
    int _size;
    int _N;

private:
    void resize(int new_size);
    int hashCode(KeyType key);

public:
    SeparateChainingHashMap(void) : _table(_sizeOfVector[0]), _size(0), _N(0)
    {
    }
    SeparateChainingHashMap(int N);
    void put(KeyType key, ValueType value) override;
    ValueType get(KeyType key) override;
    void erase(KeyType key) override;
    bool contained(KeyType key, ValueType value) override;
    bool isEmpty(void) override;
    int size(void) override;
};

template <typename K, typename V>
std::array<int, 10> SeparateChainingHashMap<K, V>::_sizeOfVector{13, 23, 47, 103, 199, 409, 829, 1663, 3323, 6653};

template <typename K, typename V>
class LinearProbingHashMap : public SignTable<K, V>
{
public:
    using typename SignTable<K, V>::KeyType;
    using typename SignTable<K, V>::ValueType;

private:
    static std::array<int, 10> _sizeOfVector;
    int _N;
    std::vector<std::optional<KeyType>> _key_table;
    std::vector<std::optional<ValueType>> _value_table;
    int _size;

private:
    void resize(int new_size);
    int hashCode(KeyType key);

public:
    LinearProbingHashMap(void) : _key_table(_sizeOfVector[_N]), _value_table(_sizeOfVector[_N]), _size(0), _N(0) {}
    LinearProbingHashMap(int N) : _N(0), _size(0)
    {
        for (; _N < 10; ++_N)
        {
            while (_sizeOfVector[_N] < N)
                ++_N;

            _key_table.resize(_sizeOfVector[_N]);
            _value_table.resize(_sizeOfVector[_N]);
            break;
        }
    }

public:
    void put(KeyType key, ValueType value) override;
    ValueType get(KeyType key) override;
    void erase(KeyType key) override;
    bool contained(KeyType key, ValueType value) override;
    bool isEmpty(void) override;
    int size(void) override;
};

template <typename K, typename V>
std::array<int, 10> LinearProbingHashMap<K, V>::_sizeOfVector{13, 23, 47, 103, 199, 409, 829, 1663, 3323, 6653};

template <typename K, typename V>
SeparateChainingHashMap<K, V>::SeparateChainingHashMap(int N) : _size(0), _N(0)
{
    for (; _N < 10; ++_N)
    {
        if (_sizeOfVector[_N] < N)
            continue;

        _table.resize(_sizeOfVector[_N]);
        break;
    }

    if (_N >= 10 || _N < 0)
        throw std::bad_alloc();
}

template <typename K, typename V>
void SeparateChainingHashMap<K, V>::put(typename SeparateChainingHashMap<K, V>::KeyType key, typename SeparateChainingHashMap<K, V>::ValueType value)
{
    if (!contained(key, value))
    {
        if (_size > _sizeOfVector[_N])
            resize(_sizeOfVector[++_N]);

        std::list<Node> &tmp = _table[hashCode(key)];
        tmp.emplace_back(key, value);
        ++_size;
    }
}

template <typename K, typename V>
typename SeparateChainingHashMap<K, V>::ValueType SeparateChainingHashMap<K, V>::get(typename SeparateChainingHashMap<K, V>::KeyType key)
{
    std::list<Node> &tmp = _table[hashCode(key)];

    for (Node &i : tmp)
    {
        if (i._key == key)
            return i._value;
    }

    throw std::invalid_argument("no such key");
}

template <typename K, typename V>
void SeparateChainingHashMap<K, V>::erase(typename SeparateChainingHashMap<K, V>::KeyType key)
{
    std::list<Node> &tmp = _table[hashCode(key)];

    for (auto i = tmp.begin(); i != tmp.end(); ++i)
    {
        if (i->_key == key)
        {
            tmp.erase(i);
            _size--;

            if (_size < (_sizeOfVector[_N] >> 2))
                resize(_sizeOfVector[--_N]);

            break;
        }
    }
}

template <typename K, typename V>
bool SeparateChainingHashMap<K, V>::contained(typename SeparateChainingHashMap<K, V>::KeyType key, typename SeparateChainingHashMap<K, V>::ValueType value)
{
    std::list<Node> &tmp = _table[hashCode(key)];

    for (auto &i : tmp)
    {
        if (i._key == key && i._value == value)
            return true;
    }

    return false;
}

template <typename K, typename V>
bool SeparateChainingHashMap<K, V>::isEmpty()
{
    for (std::list<Node> &i : _table)
    {
        if (!i.empty())
            return false;
    }

    return true;
}

template <typename K, typename V>
int SeparateChainingHashMap<K, V>::size()
{
    return _size;
}

template <typename K, typename V>
void SeparateChainingHashMap<K, V>::resize(int new_size)
{
    std::vector<std::list<Node>> tmpVector = _table;

    for (std::list<Node> &i : _table)
        i.clear();

    _table.resize(new_size);
    _size = 0;

    for (std::list<Node> &eachline : tmpVector)
    {
        for (Node &element : eachline)
            put(element._key, element._value);
    }
}

template <typename K, typename V>
int SeparateChainingHashMap<K, V>::hashCode(SeparateChainingHashMap<K, V>::KeyType key)
{
    return (key * (_sizeOfVector.back() % _sizeOfVector[_N])) % _sizeOfVector[_N];
}

template <typename K, typename V>
void LinearProbingHashMap<K, V>::put(typename LinearProbingHashMap<K, V>::KeyType key, typename LinearProbingHashMap<K, V>::ValueType value)
{
    if (_size >= (_sizeOfVector[_N] >> 1))
        resize(_sizeOfVector[++_N]);

    int code = hashCode(key);
    int i = code;
    do
    {
        if (!_key_table[i].has_value())
        {
            _key_table[i].emplace(key);
            _value_table[i].emplace(value);
            ++_size;
            break;
        }

        i = (i + 1) % _sizeOfVector[_N];
    } while (i != code);
}

template <typename K, typename V>
typename LinearProbingHashMap<K, V>::ValueType LinearProbingHashMap<K, V>::get(typename LinearProbingHashMap<K, V>::KeyType key)
{
    int code = hashCode(key);

    for (int i = code; _key_table[i].has_value(); i = (i + 1) % _sizeOfVector[_N])
    {
        if (_key_table[i].value() == key)
            return _value_table[i].value();
    }

    throw std::invalid_argument("no such key");
}

template <typename K, typename V>
void LinearProbingHashMap<K, V>::erase(typename LinearProbingHashMap<K, V>::KeyType key)
{
    if (_size < (_sizeOfVector[_N] >> 2))
        resize(_sizeOfVector[--_N]);

    int code = hashCode(key);
    for (int i = code; _key_table[i].has_value(); i = (i + 1) % _sizeOfVector[_N])
    {
        if (_key_table[i].value() == key)
        {
            _key_table[i].reset();
            _value_table[i].reset();
            --_size;
            break;
        }
    }
}

template <typename K, typename V>
bool LinearProbingHashMap<K, V>::contained(typename LinearProbingHashMap<K, V>::KeyType key, typename LinearProbingHashMap<K, V>::ValueType value)
{
    int code = hashCode(key);
    int i = code;
    do
    {
        if (!_key_table[i].has_value())
            return false;

        if (_key_table[i].value() == key && _value_table[i].value() == value)
            return true;

        i = (i + 1) % _sizeOfVector[_N];
    } while (i != code);

    return false;
}

template <typename K, typename V>
bool LinearProbingHashMap<K, V>::isEmpty()
{
    for (auto &i : _key_table)
    {
        if (i.has_value())
            return false;
    }

    return true;
}

template <typename K, typename V>
int LinearProbingHashMap<K, V>::size()
{
    return _size;
}

template <typename K, typename V>
void LinearProbingHashMap<K, V>::resize(int new_size)
{
    std::vector<std::optional<KeyType>> tmp_key_table = _key_table;
    std::vector<std::optional<ValueType>> tmp_value_table = _value_table;

    for (auto &i : _key_table)
        i.reset();
    for (auto &i : _value_table)
        i.reset();

    _key_table.resize(new_size);
    _value_table.resize(new_size);
    _size = 0;

    for (int i = 0; i < tmp_key_table.size(); ++i)
    {
        if (tmp_key_table[i].has_value() && tmp_value_table[i].has_value())
            put(tmp_key_table[i].value(), tmp_value_table[i].value());
    }
}

template <typename K, typename V>
int LinearProbingHashMap<K, V>::hashCode(LinearProbingHashMap<K, V>::KeyType key)
{
    return (key * (_sizeOfVector.back() % _sizeOfVector[_N])) % _sizeOfVector[_N];
}
