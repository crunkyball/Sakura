/*************************************************************
Sakura Game Framework : SaHashTable.h
Author: Darrell Blake

I could have stored the key in the Entry, rather than storing 
the hashed value but storing the hashed value allows for fast  
comparing. The only problem will be if there are any full hash 
collisions, rather than bucket collisions, but in that case 
there will no doubt be other issues too.

Important: The fast functions MUST recieve hashes that were 
generated with the hash function provided on construction!!!
*************************************************************/

#ifndef _SA_HASH_TABLE_H
#define _SA_HASH_TABLE_H

#include "SaCore.h"

namespace Sakura
{
    template <class Key, class T>
    class SaHashTable
    {
        template <class, class>
        friend class SaHashTableItr;

    public:
        typedef uint32_t (*HashFunc)(Key key);

        SaHashTable(uint32_t size, HashFunc hashFunc);
        ~SaHashTable();

        T* Insert(const Key& rKey, const T& rData);
        T* FastInsert(uint32_t hash, const T& rData);

        T* Reserve(const Key& rKey);
        T* FastReserve(uint32_t hash);

        T* Find(const Key& rKey);
        T* FastFind(uint32_t hash);

        void Remove(const Key& rKey);
        void FastRemove(uint32_t hash);

        void Clear();

        uint32_t GetSize() const { return m_size; }
        uint32_t GetNumEntries() const { return m_numEntries; }

#ifdef SA_BUILD_DEBUG
        //Debug. To allow me to see the structure/efficiency of the table.
        void DebugPrint();
#endif

    private:
        struct Entry
        {
            uint32_t    hash;
            T           data;
            Entry*      pNext;
        };

        const uint32_t  m_size;
        uint32_t        m_numEntries;
        Entry**         m_buckets;
        HashFunc        m_hashFunc;
    };

    template <class Key, class T>
    class SaHashTableItr
    {
    public:
        SaHashTableItr();

        T* Begin(SaHashTable<Key, T>* pTable);
        T* Next();

    private:
        SaHashTable<Key, T>*                    m_pTable;
        typename SaHashTable<Key, T>::Entry*    m_pCurrent;
        int32_t                                 m_bucketIdx;
    };
}

#include "SaHashTable.inl"

#endif  //_SA_HASH_TABLE_H
