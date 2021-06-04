#ifndef ARRAYLIST
#define ARRAYLIST
#include "List.hpp"
#include <iostream>
#include <string.h>

#define BASE_SIZE 100

template <class T> class ArrayList : public List<T> 
{
    private:
        T* elements;
        int size;
        int maxSize;

    public:
        ArrayList();
        ~ArrayList();
        void add(T item);
        T get(int index);
        T removeAt(int index);
        T remove(T item);
        void clear();
        bool contains(T item);
        int indexOf(T item);
        void set(int index, T item);
        int getSize();

    //helper functions
    private:
        void resize();
};

template<class T> ArrayList<T>::ArrayList() {
    this->size = 0;
    this->maxSize = BASE_SIZE;
    this->elements = new T[BASE_SIZE];
}

template<class T> ArrayList<T>::~ArrayList() {
    delete[] this->elements;
}

template<class T> int ArrayList<T>::getSize() {
    return this->size;
}

template<class T> void ArrayList<T>::add(T item) {
    if (this->size + 1 > this->maxSize) {
        resize();
    }
    this->elements[this->size] = item;
    this->size++;
}

template<class T> void ArrayList<T>::resize() {
    int newSize = this->maxSize * 2;
    T* newArr = new T[newSize];
    for (int i = 0; i < this->maxSize; i++) {
        newArr[i] = this->elements[i];
    }
    T* ptr = this->elements;
    this->elements = newArr;
    this->maxSize = newSize;
    delete[] ptr;
    newArr = NULL;
    delete newArr;
}

template<class T> T ArrayList<T>::get(int index) {
    if (index < 0 || index >= this->size) {
        std::string errMsg;
        errMsg = "Index out of bounds";
        throw std::runtime_error(errMsg.c_str());
    } else {
        return this->elements[index];
    }
}

template<class T> T ArrayList<T>::remove(T item) {
    for (int i = 0; i < this->size; i++) {
        if (item == this->elements[i]) {
            T val = this->elements[i];
            for (int j = i; j < this->size - 1; j++) {
                this->elements[j] = this->elements[j + 1];
            }
            this->size--;
            return val;
        }
    }
    std::string errMsg;
    errMsg = "item is not contained in this list";
    throw std::runtime_error(errMsg.c_str());
}

template<class T> T ArrayList<T>::removeAt(int index) {
     if (index < 0 || index >= this->size) {
        std::string errMsg;
        errMsg = "Index out of bounds";
        throw std::runtime_error(errMsg.c_str());
    } else {
        T val = this->elements[index];
        for (int i = index; i < this->size - 1; i++) {
            this->elements[i] = this->elements[i + 1];
        }
        this->size--;
        return val;
    }
}

template<class T> void ArrayList<T>::clear() {
    delete[] this->elements;
    this->elements = new T[this->maxSize];
    this->size = 0;
}

template<class T> bool ArrayList<T>::contains(T item) {
    for (int i = 0; i < this->size; i++) {
        if (item == this->elements[i]) {
            return true;
        }
    }
    return false;
}

template<class T> int ArrayList<T>::indexOf(T item) {
    for (int i = 0; i < this->size; i++) {
        if (item == this->elements[i]) {
            return i;
        }
    }
    return -1;
}

template<class T> void ArrayList<T>::set(int index, T item) {
    this->elements[index] = item;
}
#endif