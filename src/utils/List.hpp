#ifndef LIST
#define LIST
template <class T> class List
{   
public:
    virtual void add(T item) = 0;
    virtual T get(int index) = 0;
    virtual T removeAt(int index) = 0;
    virtual T remove(T item) = 0;
    virtual void clear() = 0;
    virtual bool contains(T item) = 0;
    virtual int indexOf(T item) = 0;
    virtual void set(int index, T item) = 0;
    virtual int getSize() = 0;
};
#endif