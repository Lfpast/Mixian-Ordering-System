#include "HashTable.h"

/**
 * Construct a HashTable with a fixed number of buckets and a custom hash function.
 * @param size Number of buckets in the hash table.
 * @param hash Pointer to a hash function that takes an int and returns an int.
 */
HashTable::HashTable(int size, int (*hash)(int)): hashTable(size), size(size), hash(hash) {}

/**
 * Copy constructor for HashTable.
 * @param ht HashTable to copy from.
 */
HashTable::HashTable(const HashTable& ht): hashTable(ht.size), size(ht.size), hash(ht.hash) 
{
    for (int i = 0; i < size; ++i)
        hashTable[i] = ht.hashTable[i];
}

/**
 * Add an order into the appropriate bucket if it doesn't already exist.
 * @param order Smart pointer to the Order to add.
 * @return void
 */
void HashTable::add(SmartPtr<Order> order) 
{
    int index {hash(order->getOid()) % size};
    if (!hashTable[index].contains(order))
        hashTable[index].add(order);
}

/**
 * Retrieve an order from the hashtable using its key.
 * @param key Key (order id) to search for.
 * @return SmartPtr<Order> The matching order smart pointer or null smart pointer if not found.
 */
SmartPtr<Order> HashTable::get(int key) const 
{
    int index {hash(key) % size};
    for (int i = 0; i < hashTable[index].length(); ++i)
        if (hashTable[index][i]->getOid() == key)
            return hashTable[index][i];
        
    return SmartPtr<Order>();
}

/**
 * Remove an order from the hashtable.
 * @param order Smart pointer to the Order to remove.
 * @return void
 */
void HashTable::remove(SmartPtr<Order> order) 
{
    int index {hash(order->getOid()) % size};
    if (hashTable[index].contains(order))
        hashTable[index].remove(order);
}

bool HashTable::contains(int key) const { return bool(this->get(key)); }

/**
 * Operator overload to access order by key, same as get().
 * @param key Key (order id) to search for.
 * @return SmartPtr<Order> The matching order smart pointer or null smart pointer if not found.
 */
SmartPtr<Order> HashTable::operator[](int key) const 
{
    int index {hash(key) % size};
    for (int i = 0; i < hashTable[index].length(); ++i)
        if (hashTable[index][i]->getOid() == key)
            return hashTable[index][i];

    return SmartPtr<Order>();
}

void HashTable::printTable() const 
{
    // Print the table
    std::cout << "HashTable:" << std::endl;
    for (size_t i = 0; i < hashTable.size(); ++i) 
    {
        std::cout << "Index: " << i << ": ";
        std::cout << hashTable[i] << std::endl;
    }
}
