// This is to implement the smart pointer class

#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>

template <typename T>
/**
 * SmartPtr<T> - a simple reference-counting smart pointer type.
 * It keeps a shared reference count for the managed object and deletes the
 * object when the last SmartPtr referencing it is destroyed or unset.
 */
class SmartPtr {
    public:
        // Constructors & Destructors
        /**
         * Default constructor: Create a null SmartPtr.
         */
        SmartPtr();
        // Adding explicit keyword to prevent from implicit conversion, causing deletion of the raw pointer
        // When the student directly parse the raw pointer to functions which accepts SmartPtr<T> as parameter
        /**
         * Construct a SmartPtr from a raw pointer (takes ownership).
         * @param p Raw pointer to manage. Must be allocated via new.
         */
        explicit SmartPtr(T* p);
        /**
         * Construct a SmartPtr by copying a value T into a newly allocated object.
         * @param val Value to copy into newly managed object (copy construction).
         */
        SmartPtr(T& val);
        /**
         * Copy constructor; shares ownership and increments reference count.
         * @param sp SmartPtr to copy from.
         */
        SmartPtr(const SmartPtr<T>& sp);
        /**
         * Destructor; decrements reference count and deletes managed object when it reaches zero.
         */
        ~SmartPtr();

        // Mutators
        /**
         * Replace the current managed object with a copy of the provided value.
         * If the previous managed object becomes unreferenced, it will be deleted.
         * @param val Value to copy into managed object.
         */
        void set(T& val);
        /**
         * Release the managed object (reduce ref count and possibly delete it), leaving this SmartPtr null.
         */
        void unset();
        /**
         * Check whether this SmartPtr is null (not owning any object).
         * @return true when there is no managed object, false otherwise.
         */
        bool isNull() const;

        // Common operators & accessors
        /**
         * Copy assignment operator; after assignment, both SmartPtr instances share the managed object.
         * @param sp Source SmartPtr to assign from.
         * @return Reference to this SmartPtr.
         */
        SmartPtr<T>& operator=(const SmartPtr<T>& sp);
        /**
         * Equality operator; compares underlying raw pointers.
         */
        bool operator==(const SmartPtr<T>& sp) const;
        /**
         * Inequality operator; compares underlying raw pointers.
         */
        bool operator!=(const SmartPtr<T>& sp) const;
        /**
         * Dereference operator.
         * @return Reference to the managed object (undefined behavior if null).
         */
        T& operator*() const;
        /**
         * Member access operator.
         * @return Raw pointer to the managed object (undefined behavior if null).
         */
        T* operator->() const;
        /**
         * Bool conversion: true if the SmartPtr owns an object.
         */
        explicit operator bool() const;

        void printDetails() const {
            if (ptr == nullptr) {
                std::cout << "SmartPtr: (nullptr, ref_count: nullptr)" << std::endl;
                return;
            }
            std::cout << "SmartPtr: (" << *ptr << " ref_count: " << *ref_count << ")" << std::endl;
        }
        // Other methods
        friend std::ostream& operator<<(std::ostream& os, const SmartPtr<T>& sp) {
            if (sp.ptr == nullptr) {
                os << "SmartPtr: (nullptr)";
                return os;
            }
            os << "SmartPtr: (" << *sp.ptr << ")";
            return os;
        }

    private:
        // A raw pointer inside this container
        T* ptr;
        // A reference count for the raw pointer, showing how many SmartPtr objects are pointing to it
        unsigned int* ref_count;
};

#include "SmartPtr-impl.h"

#endif // SMARTPTR_H
