#pragma once
#include<iostream>

template <typename K, typename V>
class Map
{
public:
    struct Node {
        K key;
        V value;
        int index;
    };

private:
    int size, maxsize;
    Node* data;

public:
    Map();
    ~Map();
    void allocate();
    V& operator [](const K& key);
    void Set(const K& key, const V& value);
    bool Get(const K& key, V& value);
    int Count();
    void Clear();
    bool Delete(const K& key);
    bool Includes(const Map<K, V>& map);
    Node* begin();
    Node* end();
};

template<typename K, typename V>
Map<K, V>::Map() : size(0), maxsize(10), data(new Node[10]) {}

template<typename K, typename V>
Map<K, V>::~Map() {
    delete[] data;
}

template<typename K, typename V>
void Map<K, V>::allocate() {
    int newsize = maxsize * 2;
    Node* newData = new Node[newsize];
    for (int i = 0; i < size; i++)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    maxsize = newsize;
}

template<typename K, typename V>
V& Map<K, V>::operator[](const K& key) {
    for (int i = 0; i < size; i++) {
        if (this->data[i].key == key)
            return this->data[i].value;
    }
    if (size == maxsize) {
        allocate();
    }
    this->data[size].key = key;
    this->data[size].index = size;
    this->data[size].value = V();
    size++;
    return this->data[size - 1].value;
}

template<typename K, typename V>
void Map<K, V>::Set(const K& key, const V& value) {
    (*this)[key] = value;
}

template<typename K, typename V>
bool Map<K, V>::Get(const K& key, V& value) {
    for (int i = 0; i < size; i++) {
        if (data[i].key == key) {
            value = data[i].value;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
int Map<K, V>::Count() {
    return size;
}

template<typename K, typename V>
void Map<K, V>::Clear() {
    size = 0;
    delete[] data;
    data = new Node[maxsize]; 
}

template<typename K, typename V>
bool Map<K, V>::Delete(const K& key) {
    for (int i = 0; i < size; i++) {
        if (data[i].key == key) {
            for (int j = i; j < size - 1; j++) {
                data[j] = data[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool Map<K, V>::Includes(const Map<K, V>& map) {
    for (int i = 0; i < map.size; i++) {
        V value;
        if (!Get(map.data[i].key, value) || !(value == map.data[i].value)) {
            return false;
        }
    }
    return true;
}

template<typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::begin() {
    return data;
}

template<typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::end() {
    return data + size;
}
