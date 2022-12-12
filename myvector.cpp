//
//  myvector.cpp
//  CMS
//
//  Created by Pavly Halim on 13/11/2022.
//

#include <stdio.h>
#include "myvector.h"

//======================================
template <typename T>
void MyVector<T>::display()
{
    for(int i=0; i<v_size; i++)
    {
        cout<<data[i]<<endl;
    }
}

//======================================
template <typename T> MyVector<T>::MyVector(int cap) //No argument constructor that creates an empty vector with a default capacity of 0
{
    cap = 0;
    v_size = 0;
    data = new T[v_capacity];
}

//======================================
template <typename T> MyVector<T>::~MyVector()
{
    delete[] data;
}
//======================================
template <typename T> void MyVector<T>::push_back(T element)
{
    if (v_capacity == 0)
    {
        v_capacity = 1;
        data = new T[v_capacity];
    }
    else if (v_size == v_capacity)
    {
        v_capacity *= 2;
        T *temp = new T[v_capacity];
        for (int i = 0; i < v_size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    data[v_size] = element;
    v_size++;
}
//======================================
template <typename T> void MyVector<T>::insert(int index, T element)
{
    if (v_capacity == 0)
    {
        v_capacity = 1;
        data = new T[v_capacity];
    }
    else if (v_size == v_capacity)
    {
        v_capacity *= 2;
        T *temp = new T[v_capacity];
        for (int i = 0; i < v_size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    for (int i = v_size; i > index; i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = element;
    v_size++;
}

//======================================
template <typename T> void MyVector<T>::erase(int index)
{
    if(index<0 or index>=v_size)
        throw out_of_range("Index out of range");
    for(int i=index; i<v_size-1; i++)
        data[i] = data[i+1];
    v_size--;
}

//======================================
template <typename T> T& MyVector<T>::at(int index)
{
    if(index<0 or index>=v_size)
        throw out_of_range("Index out of range");
    return data[index];
}

//======================================
template <typename T> const T& MyVector<T>::front()
{
    if(v_size==0)
        throw out_of_range("Vector is empty");
    return data[0];
}
//======================================
template <typename T> const T& MyVector<T>::back()
{
    if(v_size==0)
        throw out_of_range("Vector is empty");
    return data[v_size-1];
}

//======================================
template <typename T> int MyVector<T>::size() const
{
    return v_size;
}

//======================================
template <typename T> int MyVector<T>::capacity() const
{
    return v_capacity;
}

//======================================
template <typename T> bool MyVector<T>::empty() const
{
    return v_size==0;
}

//======================================
template <typename T> void MyVector<T>::shrink_to_fit()
{
    v_capacity = v_size;
    T *temp = new T[v_capacity];
    for(int i=0; i<v_size; i++)
        temp[i] = data[i];
    delete[] data;
    data = temp;
}

//======================================
template class MyVector<Contact*>;
