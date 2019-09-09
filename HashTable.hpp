//
//  HashTable.hpp
//  SeperateChaining
//
//  Created by Wenjie Bai on 2/6/19.
//  Copyright © 2019 Wenjie Bai. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include "NotImplementedException.hpp"
//throw NotImplementedException whenever you are asked to pop something from an empty container.
#include <list>
#include <vector>
#include <string>
using namespace std;


const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271};

template <typename V>
class Entry {

public:
    Entry(const string& k, const V& v)
    :   _key(k),   _value(v) { }
    const string& getkey() const {return _key;}
    const V& getvalue() const {return _value;}

private:
    string _key;
    V _value;
};

template <typename V>
class HashTable {
private:
    vector<list<Entry<V>>> this_table;   // The array of Lists
    int table_capacity;
    int table_size;
    int entry_size;

public:
    HashTable(int capacity) {
        //complete constructor, might require initializer list

        table_capacity = capacity;
        table_size = 0;
        entry_size = 0;
        this_table.resize(capacity);
    }



    int size() {
        return entry_size;
    }



    int hashCode(const string& s) {
        int value = 0;
        for (int i = 0; i < s.length(); i++) {
            value = value + s[i] ^ s[i] ^ s[i];
        }
        return value;
    }



    int hashValue(const int hashcode) {
        return (hashcode % table_capacity);
    }



    V put(const string& k, const V& v) {
        Entry<V> new_entry(k, v);
        int hash_value = hashValue(hashCode(k));
        V return_value;

        if (this_table[hash_value].empty()) {
            table_size++;
        } else {
            if (this_table[hash_value].size() == 1) {
                if (this_table[hash_value].begin()->getkey() == k) {
                    return_value = this_table[hash_value].begin()->getvalue();
                    *(this_table[hash_value].begin()) = new_entry;
                    if ((table_size / (float) table_capacity) >= 0.5) {
                        rehash();
                    }
                    return return_value;
                }
            } else {
                for (typename list<Entry<V>>::iterator itor = this_table[hash_value].begin(); itor != this_table[hash_value].end(); itor++) {
                    if (itor->getkey() == k) {
                        return_value = itor->getvalue();
                        *itor = new_entry;
                        if ((table_size / (float) table_capacity) >= 0.5) {
                            rehash();
                        }
                        return return_value;
                    }
                }
            }
        }
        entry_size++;
        this_table[hash_value].push_back(new_entry);
        if ((table_size / (float) table_capacity) >= 0.5) {
            rehash();
        }
        throw NotImplementedException("No previous key in the list, new entry is put");



        for(int i = 0; i < table_size; i++) {
            for (typename list<Entry<V>>::iterator itor = this_table[i].begin(); itor != this_table[i].end(); itor++) {
                cout << "Value at " << i << " is: " << itor->getvalue() << endl;
            }
        }




    }



    V get(const string& k) {
        int hash_value = hashValue(hashCode(k));
        V return_value;
        if (this_table[hash_value].empty()) {
            throw NotImplementedException("No previous key in the list, new entry is put");
        } else {
            for (typename list<Entry<V>>::iterator itor = this_table[hash_value].begin(); itor != this_table[hash_value].end(); itor++) {
                if (itor->getkey() == k) {
                    return_value = itor->getvalue();
                    return return_value;
                }
            }
        }
        throw NotImplementedException("No previous key in the list, new entry is put");
        return return_value;
    }



    bool contains(const string& k) {
        try {
            get(k);
        } catch (NotImplementedException& excepetion) {
            return false;
        }

        return true;
    }



    V remove(const string& k) {
        int hash_value = hashValue(hashCode(k));
        V return_value;

        if (this_table[hash_value].size() == 0) {
            throw NotImplementedException("No previous key in the list");
        } else {
            if (this_table[hash_value].size() == 1) {
                if ((this_table[hash_value].begin())->getkey() == k) {
                    return_value = this_table[hash_value].begin()->getvalue();
                    this_table[hash_value].clear();
                    table_size--;
                    entry_size--;
                    return return_value;
                } else {
                    throw NotImplementedException("No previous key in the list");
                }
            } else {
                for (typename list<Entry<V>>::iterator itor = this_table[hash_value].begin(); itor != this_table[hash_value].end(); itor++) {
                    if (itor->getkey() == k) {
                        return_value = itor->getvalue();
                        this_table[hash_value].erase(itor);
                        entry_size--;
                        return return_value;
                    }
                }

                throw NotImplementedException("No previous key in the list");
            }
        }
    }



    size_t getCollision(int hashIndex) {


        for(int i = 0; i < table_capacity; i++) {
            cout << "newi" << endl;
                cout << "?Size at " << i << " is: " << this_table[i].size() << endl;
        }



        return this_table[hashIndex].size();
    }



    void rehash() {
        for (int i = 0; i < (sizeof(primes) / sizeof(primes[0])); i++) {
            if (primes[i] > (2 * table_capacity)) {
                cout << "Size selected is: " << primes[i] << endl;
                vector<list<Entry<V>>> new_vector(primes[i]);
                int old_capacity = table_capacity;
                table_capacity = primes[i];
                for (int index = 0; index < old_capacity; index++) {
                    if (!this_table[index].empty()) {
                        for (typename list<Entry<V>>::iterator itor = this_table[index].begin(); itor != this_table[index].end(); itor++) {
                            int value = hashValue(hashCode(itor->getkey()));
                            new_vector[value].push_back(*itor);
                        }
                    }
                }
                swap(this_table, new_vector);
                new_vector.clear();

            
                return;
            }
        }
    }



    V replace(const string& k, const V& v) {
        int hash_value = hashValue(hashCode(k));
        Entry<V> new_entry(k, v);
        V return_value;

        if (this_table[hash_value].empty()) {
            throw NotImplementedException("No previous key in the list, new entry is put");
        } else {
            for (typename list<Entry<V>>::iterator itor = this_table[hash_value].begin(); itor != this_table[hash_value].end(); itor++) {
                if (itor->getkey() == k) {
                    return_value = itor->getvalue();
                    *itor = new_entry;
                    return return_value;
                }
            }
        }

        throw NotImplementedException("No previous key in the list, new entry is put");

        return return_value;
    }

};
#endif /* HashTable_hpp */
