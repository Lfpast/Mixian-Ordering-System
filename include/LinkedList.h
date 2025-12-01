#ifndef __LINKEDLIST_SELF_DEF_H__
#define __LINKEDLIST_SELF_DEF_H__

#include "SmartPtr.h"
#include "Order.h"

#include <iostream>
#include <stdexcept>

using namespace std;
// Store Order Pointer in each node
class LLNode {
    public:
        LLNode(SmartPtr<Order> order) {
            if (!order) {
                throw invalid_argument{"You are providing a nullptr order!"};
            }
            this->order = order;
            this->next = SmartPtr<LLNode>();
            this->prev = SmartPtr<LLNode>();
        }
        ~LLNode() = default;
        
        SmartPtr<Order> getOrder() {
            return this->order;
        }
        SmartPtr<LLNode> getNext() {
            return this->next;
        }
        SmartPtr<LLNode> getPrev() {
            return this->prev;
        }
        
        void setNext(SmartPtr<LLNode> next) {
            this->next = next;
        }
        void setPrev(SmartPtr<LLNode> prev) {
            this->prev = prev;
        }
    
    private:
        SmartPtr<Order> order;
        SmartPtr<LLNode> next;
        SmartPtr<LLNode> prev;
        friend class LinkedList;
        friend class SmartPtr<LLNode>;
};

// LinkedList container for Order pointers
class LinkedList {
    public:
        /**
         * Construct an empty linked list.
         */
        LinkedList();
        /**
         * Copy constructor performs a deep copy of another linked list.
         * @param ll LinkedList to copy from.
         */
        LinkedList(const LinkedList& ll);
        /**
         * Destructor, releases node resources.
         */
        ~LinkedList();
        /**
         * Append an order to the end of the list.
         * @param order The order to add; must not be null.
         */
        void add(SmartPtr<Order> order);
        /**
         * Remove the first occurrence of the order from the list.
         * @param order Smart pointer to the order to remove.
         */
        void remove(SmartPtr<Order> order);
        /**
         * Return the number of orders in the list.
         * @return Current size of the list.
         */
        int length() const;
        /**
         * Check whether the list is empty.
         * @return true if list contains no elements, false otherwise.
         */
        bool isEmpty() const;
        /**
         * Check whether the list contains the specified order.
         * @param order Smart pointer to the order to check for.
         * @return true if order exists in the list; false otherwise.
         */
        bool contains(SmartPtr<Order> order) const;
        /**
         * Remove all elements from the list.
         */
        void clear();

        /**
         * Access an order by index in the list.
         * @param index 0-based index of the element.
         * @return Smart pointer to the Order at index or a null SmartPtr if index is out of range.
         */
        SmartPtr<Order> operator[](int index) const;


        /**
         * Debugging output for the linked list.
         */
        friend std::ostream& operator<<(std::ostream& os, const LinkedList& ll);
        /**
         * Deep-copy assignment operator.
         * @param ll Source linked list to copy.
         */
        LinkedList& operator=(const LinkedList& ll);


    private:
        SmartPtr<LLNode> _head;
        SmartPtr<LLNode> _tail;
        int _size;
        SmartPtr<LLNode> find(SmartPtr<Order> order) {
            SmartPtr<LLNode> cur = this->_head;
            while (cur) {
                if (cur->getOrder() == order) {
                    return cur;
                }
                cur = cur->getNext();
            }
            return SmartPtr<LLNode>();
        }
};

#endif // __LINKEDLIST_SELF_DEF_H__
