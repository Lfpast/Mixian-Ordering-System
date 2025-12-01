#ifndef __HASHTABLE_SELF_DEF_H__
#define __HASHTABLE_SELF_DEF_H__

#include "LinkedList.h"
#include "SmartPtr.h"
#include "Order.h"

#include <vector>

/**
 * HashTable: Simple hash table implementation with chaining using LinkedList.
 */
class HashTable {
    public:
        /**
         * Default constructor.
         */
        HashTable() : hashTable(), size(), hash() {}
        /**
         * Create a HashTable with the given number of buckets and hash function pointer.
         * @param size Number of buckets.
         * @param hash Pointer to a function that maps keys to integers.
         */
        HashTable(int size, int (*hash)(int));
        HashTable(const HashTable& ht);
        ~HashTable() = default;

        /**
         * Add an order to the table if it's not already present.
         * @param order The order to add.
         */
        void add(SmartPtr<Order> order);
        /**
         * Remove an order from the table if present.
         * @param order The order to remove.
         */
        void remove(SmartPtr<Order> order);
        /**
         * Check if an order with the given key exists.
         * @param key Order id/key to search for.
         * @return true if exists, false otherwise.
         */
        bool contains(int key) const;

        /**
         * Obtain an order by key.
         * @param key Key for which to fetch the order.
         * @return Smart pointer to the order or null SmartPtr if not found.
         */
        SmartPtr<Order> get(int key) const;
        /**
         * Access operator for fetching an order by key.
         */
        SmartPtr<Order> operator[](int key) const;
        /**
         * Print the content of HashTable to stdout (for debugging).
         */
        void printTable() const;
    private:
        std::vector<LinkedList> hashTable;
        int size;
        int (*hash)(int);
};

#endif // __HASHTABLE_SELF_DEF_H__
