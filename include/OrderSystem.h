#ifndef __ORDER_SYSTEM_SELF_DEF_H__
#define __ORDER_SYSTEM_SELF_DEF_H__

#include "Order.h"
#include "SmartPtr.h"
#include "LinkedList.h"
#include "BST.h"
#include "HashTable.h"

#include <vector>
#include <climits> // modified

/**
 * OrderSystem: Main system to store and query orders.
 * It maintains various indexes (hash table for lookup, BSTs for range queries).
 */
class OrderSystem {
    public:
        /**
         * Hash function used for indexing orders by id.
         * @param oid Order id to hash.
         * @return integer hash value.
         */
        static int hashFunc(int oid);
        // Constructor & Destructor
        /**
         * Default constructor, constructs internal indexes.
         */
        OrderSystem();
        /**
         * Construct an OrderSystem and populate it with a vector of orders.
         * @param order Vector of orders to pre-populate the system with.
         */
        OrderSystem(vector<SmartPtr<Order>> order);
        OrderSystem(const OrderSystem& os) = delete;
        /**
         * Destructor; resources are managed by contained containers.
         */
        ~OrderSystem();

        /**
         * Insert an order into the system.
         * @param order Smart pointer to the order to add.
         */
        void addOrder(SmartPtr<Order> order);
        /**
         * Remove an order from the system and indexes.
         * @param order Smart pointer to the order to remove.
         */
        void removeOrder(SmartPtr<Order> order);
        /**
         * Check whether an order with given id exists.
         * @param oid Order id.
         * @return true if order exists.
         */
        bool containsOrder(int oid) const;
        /**
         * Get order by id.
         * @param oid Order id.
         * @return Smart pointer to order or null SmartPtr if not found.
         */
        SmartPtr<Order> getOrder(int oid) const;

        // Get number of mixian included in that range
        template <typename T>
        int getNumberMixianStat(T start, T end, const BST<T>& tree) const;

        // Get the total revenue of mixian sold in that range
        template <typename T>
        float getPriceSumStat(T start, T end, const BST<T>& tree) const;
        /**
         * Debug print all internal indexes for developers.
         */
        void printOrders() const;
        const BST<int>& getBSTSpiciness() const {
            return this->bst_spciness;
        }
        const BST<Soup>& getBSTSoup() const {
            return this->bst_soup;
        }
    private:
        BST<int> bst_spciness;
        BST<Soup> bst_soup;
        HashTable ht;
};

#include "OrderSystem-impl.h"

#endif // __ORDER_SYSTEM_SELF_DEF_H__
