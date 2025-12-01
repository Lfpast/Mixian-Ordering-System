#include "Order.h"
#include <iostream>
/**
 * Print an order to the output stream in a human readable format.
 * @param os Output stream reference.
 * @param order Order reference to print.
 * @return Reference to the given output stream.
 */
ostream& operator<<(ostream& os, const Order& order) {
    os << "Order ID: " << order.getOid() << ", Price: " << order.getPrice();
    return os;
}
