#ifndef __BST_SELF_DEF_H__
#define __BST_SELF_DEF_H__

#include "SmartPtr.h"
#include "LinkedList.h"
#include "Order.h"
#include "Pair.h"

#include <vector>

template <typename K>
class BST {
    public:
        BST();
        BST(const BST& bst);
        ~BST();

        bool contains(const K& key, SmartPtr<Order> order) const;
        void add(const K& key, SmartPtr<Order> order);
        
        // Return # of values in the tree (Total # of lLNodes in the Linked List for each BSTNode)
        // NOT the # of BST Nodes
        int size() const;
        
        // We cannot use SmartPointer here because BST itself is stack allocated
        // If we wrap by a SmartPtr, then the BST will call 'delete' instead of let stack to handle it
        const BST<K>* find(const K& key) const;
        const BST<K>* findMin() const;
        void remove(const K& key, SmartPtr<Order> order);

        // Return the kth smallest element, and its corresponding key as a Pair in the tree
        // The Pair<K, SmartPtr<Order>> is the kth smallest element in the tree
        // Valid range: [0, size() - 1]
        // If k >= size(), simply return a default constructed Pair
        // Example: <key, length of the linked list>
        //            <5, 5>
        //   <3, 3>          <7, 2>
        // then bst[6] will return K = 5, and the forth element in the linked list
        // Reason: smallest key 3, there are 3 elements in the linked list, so not in node <3,3>
        // The second node is <5, 5>, then the remaining elements need to visit is 4 (< 5 in the total length)
        // Thus this is the target node, return the forth element in the linked list
        Pair<K, SmartPtr<Order>> operator[](int index) const;

        // Return a vector contains all Order pointers which its key is in the range [lower, upper]
        // Assume K supports operator== / != / + / - / < / > / <= / >=
        // If it is the same key, then the order of the vector should be the same order as the tree Linked List
        //
        // Hint: You can easily implement this with a non-recursion way once implemented operator[]
        // Collect all for [lower, upper] and sort them by the index of operator[]
        // Then return the vector
        // If reverse=true, then the order should be reversed
        std::vector<SmartPtr<Order>> rangeSelect(const K& lower, const K& upper, bool reverse = false) const;
        
        bool isEmpty() const {
            // Using operator bool
            return !root;
        }

        // We have provided
        void printTree(int depth=0) const;

    private:
        #include "BSTNode.h"
        SmartPtr<BSTNode<K>> root;
        void _remove(const K& key);
};

#include "BST-impl.h"

#endif
