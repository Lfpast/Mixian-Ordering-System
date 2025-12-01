#ifndef __ORDERSYSTEM_IMPL_SELF_DEF_H__
#define __ORDERSYSTEM_IMPL_SELF_DEF_H__

#include "OrderSystem.h"

/**
 * Count the number of orders whose key values in the given BST fall in the inclusive range [start, end].
 * Generic for key type T (e.g., soup or spiciness level).
 * @param start Lower bound of the range (inclusive).
 * @param end Upper bound of the range (inclusive).
 * @param tree BST to query.
 * @return Number of orders in the specified range.
 */
template <typename T>
int OrderSystem::getNumberMixianStat(T start, T end, const BST<T>& tree) const 
    { return tree.rangeSelect(start, end).size(); }

/**
 * Compute the total price of orders whose key values in the given BST are within [start, end].
 * Generic for key type T (e.g., soup or spiciness level).
 * @param start Lower bound of the range (inclusive).
 * @param end Upper bound of the range (inclusive).
 * @param tree BST to query.
 * @return Sum of the price values for orders in the specified range.
 */
template <typename T>
float OrderSystem::getPriceSumStat(T start, T end, const BST<T>& tree) const 
{ 
    std::vector<SmartPtr<Order>> temp = tree.rangeSelect(start, end); 
    float price {0};

    for (size_t i = 0; i < temp.size(); ++i)
        price += temp[i]->getPrice();

    return price;
}
    
#endif // __ORDERSYSTEM_IMPL_SELF_DEF_H__
