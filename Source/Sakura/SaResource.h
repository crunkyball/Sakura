/*************************************************************
Sakura Game Framework : SaResource.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RESOURCE_H
#define _SA_RESOURCE_H

#include "SaCore.h"

namespace Sakura
{
    template <class T>
    class SaResource
    {
        friend class SaResourceManager;

    public:
        enum EState
        {
            STATE_UNLOADED = 0,
            STATE_LOADING,
            STATE_READY,
            STATE_ERROR
        };

        SaResource() {};

        bool IsLoading() { return m_state == STATE_LOADING; }
        bool IsReady() { return m_state == STATE_READY; }
        bool IsError() { return m_state == STATE_ERROR; }

        T& Get() { return m_element; }
        const T& Get() const { return m_element; }

        T* GetPtr() { return &m_element; }
        const T* GetPtr() const { return &m_element; }

    private:
        uint32_t        m_hash;
        EState          m_state;
        uint32_t        m_refCount;
        T               m_element;

#ifdef SA_BUILD_DEBUG
        static const uint32_t   DEBUG_NAME_SIZE = 32;
        char                    m_debugName[DEBUG_NAME_SIZE];
#endif
    };
}

#endif  //_SA_RESOURCE_H
