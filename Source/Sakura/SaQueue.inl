/*************************************************************
Sakura Game Framework : SaQueue.inl
Author: Darrell Blake
*************************************************************/

#ifndef _SA_QUEUE_H
#error This should be included from SaQueue.h
#endif

namespace Sakura
{

template <class T>
SaQueue<T>::SaQueue() :
    m_capacity(8),
    m_numItems(0),
    m_headIndex(0),
    m_tailIndex(0)
{
    m_array = new T[m_capacity];
}

template <class T>
SaQueue<T>::SaQueue(uint32_t initialCapacity) :
    m_capacity(initialCapacity),
    m_numItems(0),
    m_headIndex(0),
    m_tailIndex(0)
{
    m_array = new T[m_capacity];
}

template <class T>
SaQueue<T>::~SaQueue()
{
    delete[] m_array;
}

template <class T>
void SaQueue<T>::Push(const T& item)
{
    if (m_numItems == m_capacity)
        Grow();

    m_array[m_tailIndex] = item;
    m_tailIndex = (m_tailIndex + 1) % m_capacity;

    m_numItems++;
}

template <class T>
T& SaQueue<T>::Front()
{
    return m_array[m_headIndex];
}

template <class T>
const T& SaQueue<T>::Front() const
{
    return m_array[m_headIndex];
}

template <class T>
void SaQueue<T>::Pop()
{
    if (m_numItems > 0)
    {
        m_headIndex = (m_headIndex + 1) % m_capacity;
        m_numItems--;
    }
}

template <class T>
void SaQueue<T>::Clear()
{
    m_headIndex = m_tailIndex;
    m_numItems = 0;
}

//This is slow. We can't do a realloc because we'd cause a split in the 
//ring buffer at the point it loops around (not to mention you shouldn't 
//realloc a buffer created with new anyway!).
template <class T>
void SaQueue<T>::Grow()
{
    T* newArray = new T[m_capacity << 1];

    for (uint32_t itemIdx = 0; itemIdx < m_capacity; itemIdx++)
    {
        uint32_t oldItemIdex = (m_headIndex + itemIdx) % m_capacity;
        newArray[itemIdx] = m_array[oldItemIdex];
    }

    m_capacity <<= 1;

    delete[] m_array;
    m_array = newArray;

    m_headIndex = 0;
    m_tailIndex = m_numItems;
}

template <class T>
uint32_t SaQueue<T>::Size() const
{
    return m_numItems;
}

}
