#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <iostream>

class DLL
{
private:
    class Node
    {
    public:
        Node * prev;
        int data;
        Node * next;
    public:
        Node(int x = 0) : prev(nullptr), data(x), next(nullptr){}
    };
private:
    Node * head;
    Node * tail;
    int elcount;
private:
    bool closer_to_head(int value) const;
    bool closer_to_tail(int value) const;
    bool is_mid(int value) const;
    void bubble_sort(int * ar, const int num);
    void select_sort(int * ar, const int num);
    void insert_sort(int * ar, const int num);
    void quick_sort(int * ar, const int num);

    void internal_quick_sort(int * ar, int left, int right);
    int partition(int * ar, int left, int right);
    void swap(int & a, int & b);
public:
    enum slicetype{WHITELIST, BLACKLIST};
    enum elem_pos{FRONT, MID, BACK};
    enum type_sort{QUICK, BUBBLE, SELECT, INSERT};
public:
    DLL();
    explicit DLL(const int val);
    DLL(const DLL & obj);
    DLL(DLL && obj);
    ~DLL();
public:
    DLL & operator=(const DLL & obj);
    DLL & operator=(DLL && obj);
    friend DLL operator+(const DLL & d1, const DLL & d2);
public:
    void push(const elem_pos where, const int element);
    void pop(const elem_pos where);
    void insert(const int pos, const int element);
    void remove(const int pos);
    void merge(const DLL & obj);
    void reverse();
    void resize(const int newsize);
    void refresh(const int pos, const int newvalue);
    void sort(const type_sort which = DLL::QUICK);
    void clear();
public:
    DLL slice(const int pos1, const int pos2,
              const slicetype which = DLL::WHITELIST) const;
    const int size() const;
    int at(const int pos) const;
    void print() const;
};

//private
inline bool DLL::closer_to_head(int value) const
{
    return (elcount - value) > (elcount / 2);
}

inline bool DLL::closer_to_tail(int value) const
{
    return (elcount - value) < (elcount / 2);
}

inline bool DLL::is_mid(int value) const
{
    return value == (elcount / 2) + (elcount % 2);
}

inline void DLL::quick_sort(int * ar, const int arsize)
{
    internal_quick_sort(ar, 0, arsize - 1);
}

inline void DLL::swap(int & a, int  & b)
{
    int temp = a;
    a = b;
    b = temp;
}


//public
inline const int DLL::size() const {return elcount;}


#endif
