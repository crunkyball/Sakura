/*************************************************************
Sakura Game Framework : SaQueue.h
Author: Darrell Blake

A FIFO queue using a ring buffer and dynamically allocated 
storage.
*************************************************************/

#ifndef _SA_QUEUE_H
#define _SA_QUEUE_H

#include "SaCore.h"

namespace Sakura
{
    template <class T>
    class SaQueue
    {
    public:
        SaQueue();
        SaQueue(uint32_t initialCapacity);
        ~SaQueue();

        void        Push(const T& item);
        T&          Front();
        const T&    Front() const;
        void        Pop();

        void        Clear();

        uint32_t    Size() const;

    private:
        void        Grow();

        uint32_t    m_headIndex;
        uint32_t    m_tailIndex;
        uint32_t    m_capacity;
        uint32_t    m_numItems;
        T*          m_array;
    };
}

#include "SaQueue.inl"

#endif  //_SA_QUEUE_H
