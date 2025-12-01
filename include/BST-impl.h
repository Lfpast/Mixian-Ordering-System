#ifndef __BST_IMPL_SELF_DEF_H__
#define __BST_IMPL_SELF_DEF_H__

#include "BST.h"

template <typename K>
BST<K>::BST() : root(SmartPtr<BSTNode<K>>()) {}

template <typename K>
BST<K>::BST(const BST<K>& bst) 
{
    if (bst.isEmpty()) 
        root = SmartPtr<BSTNode<K>>();
    else
        root = SmartPtr<BSTNode<K>>(new BSTNode<K>(*bst.root));
}

template <typename K>
BST<K>::~BST() {}

template <typename K>
/**
 * Check whether a key exists in the BST and whether a given order is stored under that key.
 * @param key Key to search for in the tree (e.g., order attribute like soup or spiciness).
 * @param order Smart pointer to the Order to check membership for.
 * @return true if the key exists and the order is present under that key; otherwise false.
 */
bool BST<K>::contains(const K& key, SmartPtr<Order> order) const 
{
    if (isEmpty())
        return false;
    if (key < root->key)
        return root->left.contains(key, order);
    else if (key > root->key)
        return root->right.contains(key, order);
    else if (key == root->key)   // equal case, find the correspoding order exist or not
        return root->value.contains(order);
    // default: not found
    return false;
}

template <typename K>
/**
 * Calculate the total number of orders stored in the BST (sum over counts in each node).
 * @return Number of stored orders.
 */
int BST<K>::size() const 
{
    if (isEmpty())
        return 0;
    return root->value.length() + root->left.size() + root->right.size();
}
template <typename K>
/**
 * Add an order under the given key. If the key does not exist, a new node is created.
 * @param key Key (e.g., order attribute) under which to store the order.
 * @param order Smart pointer to the Order to add.
 */
void BST<K>::add(const K& key, SmartPtr<Order> order) 
{
    if (isEmpty())
    {
        root = SmartPtr<BSTNode<K>>(new BSTNode<K>(key, order));
        return;
    }

    if (key < root->key)
        root->left.add(key, order);
    else if (key > root->key)
        root->right.add(key, order);
    else if (key == root->key)
        root->add(order);
}

template <typename K>
/**
 * Find the sub-tree rooted at the given key.
 * @param key Key to find in the tree.
 * @return pointer to the BST node wrapper (const) that contains the key or nullptr if not found.
 */
const BST<K>* BST<K>::find(const K& key) const 
{
    if (isEmpty())
        return nullptr;
    
    if (key < root->key)
        return root->left.find(key);
    else if (key > root->key)
        return root->right.find(key);
    else if (key == root->key)
        return this;
    // default: not found
    return nullptr;
}

template <typename K>
/**
 * Find the minimum key node in this tree (leftmost node).
 * @return pointer to the subtree whose root is the minimum key in this tree.
 */
const BST<K>* BST<K>::findMin() const 
{
    if (!root->left.isEmpty())
        return root->left.findMin();
    else
        return this;
}

template <typename K>
/**
 * Remove a node (and its orders) with the given key from the tree. If the node has two children,
 * it will be replaced by its in-order successor (minimum in the right subtree).
 * @param key Key for the node to be removed.
 */
void BST<K>::_remove(const K& key) 
{
    if (isEmpty())
        return;
    
    if (key < root->key)
        root->left._remove(key);
    else if (key > root->key)
        root->right._remove(key);
    else if (key == root->key)
    {
        if (!root->left.isEmpty() && !root->right.isEmpty())
        {
            const BST<K>* minimum {root->right.findMin()};
            root->key = minimum->root->key;
            root->value = minimum->root->value;
            root->right._remove(minimum->root->key);
        }
        else
        {
            SmartPtr<BSTNode<K>> deleting_node {root};
            root = (root->left.isEmpty()? root->right.root: root->left.root);
            deleting_node->left.root.unset();
            deleting_node->right.root.unset();
        }
    }
}

template <typename K>
/**
 * Remove a specific order under the given key. If the node's order collection becomes empty, the node is removed.
 * @param key Key under which the order is stored.
 * @param order Smart pointer to the order to remove.
 */
void BST<K>::remove(const K& key, SmartPtr<Order> order) 
{
    if (isEmpty())
        return;
    
    if (key < root->key)
        root->left.remove(key, order);
    else if (key > root->key)
        root->right.remove(key, order);
    else if (key == root->key)
    {
        if (root->value.contains(order))
        {
            root->value.remove(order);
            if (root->value.isEmpty())
                _remove(root->key);
        }
        else
            return;
    }
}

template <typename K>
/**
 * Access the order at the given index in an in-order traversal sense (0-based):
 * returns a pair of key and order for the index-th order stored in the tree.
 * @param index Position of the order in in-order traversal (0-based).
 * @return Pair of key and SmartPtr<Order>; an empty pair if index out of range.
 */
Pair<K, SmartPtr<Order>> BST<K>::operator[](int index) const 
{
    int total_count {size()};
    if (index < 0 || index > total_count - 1)
        return Pair<K, SmartPtr<Order>>();
    else
    {
        int temp_index {index - root->left.size()};
        if (temp_index >= 0 && temp_index <= root->value.length() - 1)
            return Pair<K, SmartPtr<Order>>(root->key, root->value[temp_index]);
        else if (temp_index < 0)
            return root->left[index];
        else
            return root->right[temp_index - root->value.length()];
    }
}

template <typename K>
/**
 * Select orders whose keys are within the inclusive range [lower, upper].
 * @param lower Lower bound for key (inclusive).
 * @param upper Upper bound for key (inclusive).
 * @param reverse If false, results are in ascending order; if true, descending order.
 * @return Vector of SmartPtr<Order> matching the range.
 */
std::vector<SmartPtr<Order>> BST<K>::rangeSelect(const K& lower, const K& upper, bool reverse) const 
{
    if (!reverse)
    {
        if (isEmpty())
        return std::vector<SmartPtr<Order>>();

        std::vector<SmartPtr<Order>> temp1 {root->left.rangeSelect(lower, upper, reverse)};
        if (root->key >= lower && root->key <= upper)
            for (int i = 0; i < root->value.length(); ++i)
                temp1.push_back(root->value[i]);

        std::vector<SmartPtr<Order>> temp2 {root->right.rangeSelect(lower, upper, reverse)};
        for (size_t i = 0; i < temp2.size(); ++i)
            temp1.push_back(temp2[i]);
        
        return temp1;
    }
    else
    {
        if (isEmpty())
        return std::vector<SmartPtr<Order>>();

        std::vector<SmartPtr<Order>> temp1 {root->right.rangeSelect(lower, upper, reverse)};
        if (root->key >= lower && root->key <= upper)
            for (int i = 0; i < root->value.length(); ++i)
                temp1.push_back(root->value[i]);

        std::vector<SmartPtr<Order>> temp2 {root->left.rangeSelect(lower, upper, reverse)};
        for (size_t i = 0; i < temp2.size(); ++i)
            temp1.push_back(temp2[i]);
        
        return temp1;
    }
}

template <typename K>
void BST<K>::printTree(int depth) const 
{
    if (isEmpty()) 
        return;

    root->right.printTree(depth + 1);
    for (int i = 0; i < depth; ++i) 
        std::cout << "  ";

    std::cout << "(" << root->key << "," << this->root->value.length() << ")" << std::endl;
    root->left.printTree(depth + 1);
}

#endif // __BST_IMPL_SELF_DEF_H__
