#ifndef __PAIR_SELF_DEF_H__
#define __PAIR_SELF_DEF_H__

template <typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
    Pair() : first(T1()), second(T2()) {}
    Pair(const T1 &a, const T2 &b) : first(a), second(b) {}
    template <typename U1, typename U2>
    Pair(const Pair<U1, U2> &p) : first(p.first), second(p.second) {}
    Pair<T1, T2> &operator=(const Pair<T1, T2> &p)
    {
        first = p.first;
        second = p.second;
        return *this;
    }
};

#endif // __PAIR_SELF_DEF_H__
