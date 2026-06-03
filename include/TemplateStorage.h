#ifndef TEMPLATESTORAGE_H
#define TEMPLATESTORAGE_H

#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class Storage
{
private:
    vector<T> items;

public:
    Storage() {}
    Storage(const Storage &other) : items(other.items) {}
    Storage &operator=(const Storage &other)
    {
        if (this != &other)
        {
            items = other.items;
        }
        return *this;
    }
    ~Storage() {}

    void add(const T &item)
    {
        items.push_back(item);
    }

    bool remove(const T &item)
    {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end())
        {
            items.erase(it);
            return true;
        }
        return false;
    }

    T getAt(int index) const
    {
        if (index >= 0 && index < static_cast<int>(items.size()))
        {
            return items[index];
        }
        return T();
    }

    int count() const
    {
        return static_cast<int>(items.size());
    }

    bool contains(const T &item) const
    {
        return find(items.begin(), items.end(), item) != items.end();
    }

    vector<T> &getAll()
    {
        return items;
    }

    const vector<T> &getAll() const
    {
        return items;
    }
};

#endif // TEMPLATESTORAGE_H

