/*************************************************************
Sakura Game Framework : SaHashTable.inl
Author: Darrell Blake
*************************************************************/

#ifndef _SA_HASH_TABLE_H
#error This should only be included from SaHashTable.h
#endif

#include "SaDebug.h"

namespace Sakura
{

template <class Key, class T>
SaHashTable<Key, T>::SaHashTable(uint32_t size, HashFunc hashFunc) :
    m_size(size),
    m_hashFunc(hashFunc),
    m_numEntries(0)
{
    m_buckets = new Entry*[m_size];
    
    for (uint32_t bucketIdx = 0; bucketIdx < m_size; bucketIdx++)
    {
        m_buckets[bucketIdx] = NULL;
    }
}

template <class Key, class T>
SaHashTable<Key, T>::~SaHashTable()
{
    Clear();
    delete[] m_buckets;
}

template <class Key, class T>
T* SaHashTable<Key, T>::Insert(const Key& rKey, const T& rData)
{
    uint32_t hash = m_hashFunc(rKey);
    return FastInsert(hash, rData);
}

template <class Key, class T>
T* SaHashTable<Key, T>::FastInsert(uint32_t hash, const T& rData)
{
    T* pEntry = FastReserve(hash);

    if (pEntry)
        *pEntry = rData;

    return pEntry;
}

template <class Key, class T>
T* SaHashTable<Key, T>::Reserve(const Key& rKey)
{
    uint32_t hash = m_hashFunc(rKey);
    return FastReserve(hash);
}

template <class Key, class T>
T* SaHashTable<Key, T>::FastReserve(uint32_t hash)
{
    uint32_t bucketIdx = hash % m_size;

    Entry* pPrevEntry = NULL;
    Entry** ppInsertEntry = &m_buckets[bucketIdx];

    uint32_t bucketLen = 0;

    //The vast majority of the time we shouldn't enter here.
    if (m_buckets[bucketIdx])
    {
        for (Entry* pEntry = m_buckets[bucketIdx]; pEntry != NULL; pEntry = pEntry->pNext)
        {
            if (pEntry->hash == hash)
            {
                SA_PRINTF("Hash entry 0x%x already exists!\n", hash);
                return &pEntry->data;
            }

            pPrevEntry = pEntry;
            ppInsertEntry = &pEntry->pNext;

            SA_ASSERT_ONCE(++bucketLen < 3, "Hash bucket getting out of hand. May need a better hash func or a larger table?");
        }

        SA_PRINTF("Warning: Hash bucket collision!\n");
    }

    *ppInsertEntry = new Entry;
    (*ppInsertEntry)->hash = hash;
    (*ppInsertEntry)->pNext = NULL;

    if (pPrevEntry)
        pPrevEntry->pNext = *ppInsertEntry;

    m_numEntries++;
    return &(*ppInsertEntry)->data;
}

template <class Key, class T>
T* SaHashTable<Key, T>::Find(const Key& rKey)
{
    uint32_t hash = m_hashFunc(rKey);
    return FastFind(hash);
}

template <class Key, class T>
T* SaHashTable<Key, T>::FastFind(uint32_t hash)
{
    uint32_t bucketIdx = hash % m_size;

    if (m_buckets[bucketIdx])
    {
        //The vast majority of the time we should only ever have to check this entry.
        if (m_buckets[bucketIdx]->hash == hash)
            return &m_buckets[bucketIdx]->data;

        for (Entry* pEntry = m_buckets[bucketIdx]->pNext; pEntry != NULL; pEntry = pEntry->pNext)
        {
            if (pEntry->hash == hash)
                return &pEntry->data;
        }
    }

    return NULL;
}

template <class Key, class T>
void SaHashTable<Key, T>::Remove(const Key& rKey)
{
    uint32_t hash = m_hashFunc(rKey);
    FastRemove(hash);
}

template <class Key, class T>
void SaHashTable<Key, T>::FastRemove(uint32_t hash)
{
    uint32_t bucketIdx = hash % m_size;

    for (Entry** ppEntry = &m_buckets[bucketIdx]; *ppEntry != NULL; ppEntry = &(*ppEntry)->pNext)
    {
        if ((*ppEntry)->hash == hash)
        {
            Entry* pNext = (*ppEntry)->pNext;
            delete *ppEntry;
            *ppEntry = pNext;

            m_numEntries--;
            return;
        }
    }

    SA_FAIL("Didn't find entry to remove!");
}

template <class Key, class T>
void SaHashTable<Key, T>::Clear()
{
    for (uint32_t bucketIdx = 0; bucketIdx < m_size; bucketIdx++)
    {
        for (Entry* pEntry = m_buckets[bucketIdx]; pEntry != NULL; )
        {
            Entry* pNextEntry = pEntry->pNext;
            delete pEntry;
            pEntry = pNextEntry;
        }

        m_buckets[bucketIdx] = NULL;
    }
};

#ifdef SA_BUILD_DEBUG
template <class Key, class T>
void SaHashTable<Key, T>::DebugPrint()
{
    for (uint32_t bucketIdx = 0; bucketIdx < m_size; bucketIdx++)
    {
        SA_PRINTF("[");
        bool comma = false;
        for (Entry* pEntry = m_buckets[bucketIdx]; pEntry != NULL; pEntry = pEntry->pNext )
        {
            SA_PRINTF("%s%u", comma ? ", " : "", pEntry->hash);
            comma = true;
        }
        SA_PRINTF("]\n");
    }
}
#endif

template <class Key, class T>
SaHashTableItr<Key, T>::SaHashTableItr() :
    m_pTable(NULL),
    m_bucketIdx(0)
{
}

template <class Key, class T>
T* SaHashTableItr<Key, T>::Begin(SaHashTable<Key, T>* pTable)
{
    m_pTable = pTable;
    m_pCurrent = NULL;
    m_bucketIdx = -1;
    return Next();
}

template <class Key, class T>
T* SaHashTableItr<Key, T>::Next()
{
    if (m_pCurrent)
        m_pCurrent = m_pCurrent->pNext;

    if (m_pCurrent == NULL)
    {
        while (++m_bucketIdx < m_pTable->GetSize())
        {
            m_pCurrent = m_pTable->m_buckets[m_bucketIdx];

            if (m_pCurrent)
                break;
        }
    }

    if (m_pCurrent)
        return &m_pCurrent->data;

    return NULL;
}

}
