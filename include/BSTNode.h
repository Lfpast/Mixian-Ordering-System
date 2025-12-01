#ifndef __BSTNODE_SELF_DEF_H__
#define __BSTNODE_SELF_DEF_H__

#include "LinkedList.h"
#include "SmartPtr.h"
#include "Order.h"
#include "BST.h"

template <typename S>
class BSTNode 
{
    public:
        //K means key, which used to compare the node in BST
        // It should satisfy the BST requirement
        S key;
        
        // The value corresponding to this key
        LinkedList value;

        BST<S> left;
        BST<S> right;

        BSTNode(S key, SmartPtr<Order> order) : key(key) { value.add(order); }
        BSTNode(const BSTNode& node) = default;
        void add(SmartPtr<Order> order) { value.add(order); }
};

#endif // __BSTNODE_SELF_DEF_H__
