#ifndef HASH_MAP
#define HASH_MAP

#include "HashNode.h"
#include "KeyHash.h"

template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
public:
    HashMap() {
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        delete [] table;
    }

    bool get(const K &key, V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            entry = new HashNode<K, V>(key, value);
            if (prev == nullptr) {
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(value);
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            return;
        }
        else {
            if (prev == nullptr) {
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

private:
    HashNode<K, V> **table;
    F hashFunc;
};

#endif // !HASH_MAP