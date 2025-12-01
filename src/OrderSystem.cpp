#include "OrderSystem.h"
#include "Order.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/**
 * Default constructor for OrderSystem.
 * Initializes the internal hash table and BSTs.
 */
OrderSystem::OrderSystem(): ht(769, hashFunc) {}

/**
 * Hash function used to map order ids into the hashtable index space.
 * @param oid The order id to hash.
 * @return Integer hash value within the acceptable range.
 */
int OrderSystem::hashFunc(int oid) 
{ 
    long long key {static_cast<long long>(oid) * oid + 13 * oid - 7};
    if (key < 0) key = key % INT_MAX + 1;
    else key %= INT_MAX;
    return static_cast<int>(key);
}

/**
 * Construct an OrderSystem from a vector of orders and insert them into the indexes.
 * @param order Vector of SmartPtr<Order> to insert during initialization.
 */
OrderSystem::OrderSystem(vector<SmartPtr<Order>> order): ht(769, hashFunc) 
{
    for (size_t i = 0; i < order.size(); ++i)
    {
        ht.add(order[i]);
        bst_soup.add(order[i]->getSoup(), order[i]);
        bst_spciness.add(order[i]->getSpicyLevel(), order[i]);
    }   
}

/**
 * Destructor for the OrderSystem. Defaulted; resources are managed by contained containers.
 */
OrderSystem::~OrderSystem() {}

/**
 * Add an order into the system (into hash table & BST indexes) if not already present.
 * @param order Smart pointer representing the order to insert.
 */
void OrderSystem::addOrder(SmartPtr<Order> order) 
{
    if (!containsOrder(order->getOid()))
    {
        ht.add(order);
        bst_spciness.add(order->getSpicyLevel(), order);
        bst_soup.add(order->getSoup(), order);
    }
}

/**
 * Remove an order from the system and its indexes.
 * @param order Smart pointer representing the order to remove.
 */
void OrderSystem::removeOrder(SmartPtr<Order> order) 
{
    if (containsOrder(order->getOid()))
    {
        ht.remove(order);
        bst_spciness.remove(order->getSpicyLevel(), order);
        bst_soup.remove(order->getSoup(), order);
    }
}

bool OrderSystem::containsOrder(int oid) const { return bool(this->getOrder(oid)); }

/**
 * Get an order by its id.
 * @param oid Order id to search for.
 * @return SmartPtr<Order> the matching order or a null SmartPtr if not found.
 */
SmartPtr<Order> OrderSystem::getOrder(int oid) const 
{
    SmartPtr<Order> temp {ht.get(oid)};
    if (temp.isNull()) return SmartPtr<Order>();
    else return temp;
}


void OrderSystem::printOrders() const 
{
    this->ht.printTable();
    this->bst_soup.printTree();
    this->bst_spciness.printTree();
}    
