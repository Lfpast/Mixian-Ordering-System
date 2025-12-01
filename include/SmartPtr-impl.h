#ifndef SMARTPTR_IMPL_H
#define SMARTPTR_IMPL_H

#include "SmartPtr.h"


/**
 * SmartPtr<T> - A minimal reference-counting smart pointer implementation.
 * NOTE: This implementation uses a separate reference count integer that is allocated
 * on the heap together with references to the managed object pointer.
 */

// Constructors & Destructors
/**
 * Default constructor: create a null SmartPtr with no managed object.
 */
template <typename T>
SmartPtr<T>::SmartPtr(): ptr(nullptr), ref_count(nullptr) {}

/**
 * Construct SmartPtr from a raw pointer. Assumes pointer was created with `new`.
 * @param p Raw pointer to take ownership of.
 */
template <typename T>
SmartPtr<T>::SmartPtr(T* p) 
{
    if (p) 
    { 
        ptr = p;
        ref_count = new unsigned int(1);
    }
    else
    {
        ptr = nullptr; 
        ref_count = nullptr; 
    }
}

/**
 * Construct SmartPtr by copying a value (creates a new managed copy).
 * The value type T must be copy-constructible.
 * @param val Reference to an existing value to copy and manage.
 */
template <typename T>
SmartPtr<T>::SmartPtr(T& val) 
{
    T* temp = new T(val); // Make a copy to prevent deletion
    ptr = temp;
    ref_count = new unsigned int(1);
}

/**
 * Copy constructor: shares ownership of the managed object by increasing the reference count.
 * @param sp SmartPtr to copy from.
 */
template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& sp) 
{
    if (sp.isNull()) // operator overloading
    {
        ptr = nullptr;
        ref_count = nullptr;
    }
    else
    {
        ptr = sp.ptr;
        ref_count = sp.ref_count;
        *ref_count += 1;
    }
}

/**
 * Destructor: decrease the reference count and delete the object when the count reaches zero.
 */
template <typename T>
SmartPtr<T>::~SmartPtr() 
{
    if (ptr)
    {
        *ref_count -= 1;
        if (*ref_count == 0)    // check whether we should delete the obj
        {
            delete ptr;
            delete ref_count;
        }
    }
}

// Mutators
/**
 * Replace the managed object by making a copy of the supplied value (copy semantics).
 * If a previously managed object existed, this decreases its reference count and frees it
 * if no other SmartPtr points to it.
 * @param val Reference to the value to set.
 */
template <typename T>
void SmartPtr<T>::set(T& val) 
{
    T* temp {new T(val)};     // Make a copy to prevent deletion
    if (ptr)    // Not a nullptr
    {
        *ref_count -= 1;
        if (*ref_count == 0)    // If no other pointers, do the cleaning.
        {
            delete ptr;
            delete ref_count;
        }
    }

    ptr = temp;
    ref_count = new unsigned int(1);
}

/**
 * Unset the smart pointer, decreasing the ref count and freeing the managed object if needed.
 */
template <typename T>
void SmartPtr<T>::unset() 
{
    if (ptr)    // Only do unset op for non nullptr
    {
        *ref_count -= 1;
        if (*ref_count == 0)
        {
            delete ptr;
            delete ref_count;
        }

        ptr = nullptr;
        ref_count = nullptr;    // overlap the old values
    }
}

template <typename T>
bool SmartPtr<T>::isNull() const { return !bool(*this); }

// Common operators & accessors
/**
 * Assignment operator that implements strong exception-safety by using copy-and-swap idiom.
 * @param sp Source SmartPtr to assign from.
 * @return Reference to this SmartPtr after assignment.
 */
template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& sp) 
{
    SmartPtr<T> temp(sp);   // Do the copying
    if (ptr != temp.ptr)   // Only do = if they are different
    {
        if (ptr)    // Originally not a nullptr
        {
            *ref_count -= 1;
            if (*ref_count == 0)    // Do the cleaning
            {
                delete ptr;
                delete ref_count;
            }
        }
        
        ptr = temp.ptr;
        ref_count = temp.ref_count;
        if (!temp.isNull()) // If not nullptr, increase count by one
            *ref_count += 1;
    }
    
    return *this;
}

/**
 * Equality operator: return true if both SmartPtr instances manage the same raw pointer.
 * @param sp other SmartPtr to compare with.
 * @return true if raw pointers are equal, false otherwise.
 */
template <typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T>& sp) const 
{
    if (ptr == sp.ptr)  return true;
    return false;
}

template <typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& sp) const 
{
    if (ptr != sp.ptr) return true;
    return false;
}

/**
 * Dereference operator: return reference to the managed value. Behavior undefined if null.
 * @return Reference to the managed object.
 */
template <typename T>
T& SmartPtr<T>::operator*() const { return *ptr; }

/**
 * Member access operator: return raw pointer to managed object. Behavior undefined if null.
 * @return Raw pointer to managed object.
 */
template <typename T>
T* SmartPtr<T>::operator->() const { return ptr; }

/**
 * Boolean conversion operator: return true if SmartPtr is non-null.
 * @return true if pointer is non-null, false otherwise.
 */
// Note that the SmartPtr<T>::isNull() function is calling this bool operator
template <typename T>
SmartPtr<T>::operator bool() const 
{
    if (ptr) return true;
    return false;
}

#endif // SMARTPTR_IMPL_H
