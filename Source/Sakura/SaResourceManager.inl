/*************************************************************
Sakura Game Framework : SaResourceManager.inl
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RESOURCE_MANAGER_H
#error This should only be included from SaResourceManager.h
#endif

#include "SaDebug.h"
#include <cstring>
#include "SaHash.h"
#include "SaFile.h"
#include "SaFileLoader.h"
#include PLATFORM_INCLUDE( SA_EFFECT_API_DIR/SaEffect_Platform.h )

//Template functions for SaResourceManager.

namespace Sakura
{

    template <class T>
    void SaResourceManager::ReleaseResources(SaHashTable<const char*, SaResource<T>>* pTable)
    {
        ms_tableMutex.Lock();
        SaHashTableItr<const char*, SaResource<T>> itr;
        for (SaResource<T>* pResource = itr.Begin(pTable); pResource != NULL; pResource = itr.Next())
        {
            UnloadResource(pResource);
        }
        ms_tableMutex.Unlock();
    }

    template <class T>
    SaResource<T>* SaResourceManager::LoadResource(const char* pFileName)
    {
        uint32_t hash = SaHash(pFileName);

        ms_tableMutex.Lock();

        SaResource<T>* pResource = GetResourceTable<T>()->FastFind(hash);

        if (!pResource)
        {
            pResource = GetResourceTable<T>()->FastReserve(hash);

            pResource->m_refCount = 0;
            pResource->m_hash = hash;
            pResource->m_state = SaResource<T>::STATE_LOADING;

#ifdef SA_BUILD_DEBUG
            strcpy_s(pResource->m_debugName, SaResource<T>::DEBUG_NAME_SIZE, pFileName);
            pResource->m_debugName[SaResource<T>::DEBUG_NAME_SIZE - 1] = 0;
            pResource->m_element.SetDebugName(pResource->m_debugName);
#endif

            SaResourceJob job(hash, ResourceManagerThread_Load<T>);
            job.SetFileName(pFileName);
            ms_resourceManagerJobQueue.AddJob(job);
        }

        ms_tableMutex.Unlock();

        pResource->m_refCount++;

        return pResource;
    }

    template <class T>
    void SaResourceManager::UnloadResource(SaResource<T>*& rpResource)
    {
        SaResourceJob job(rpResource->m_hash, ResourceManagerThread_Unload<T>);
        ms_resourceManagerJobQueue.AddJob(job);
        rpResource = NULL;
    }

    template <class T>
    void SaResourceManager::ResourceManagerThread_Load(const SaResourceJob* pJob)
    {
        ms_tableMutex.Lock();
        SaResource<T>* pResource = GetResourceTable<T>()->FastFind(pJob->GetResourceHash());
        ms_tableMutex.Unlock();

        if (pResource)
        {
            SaFileLoader fileLoader;
            fileLoader.Load(pJob->GetFileName(), NO_CALLBACK, false, true);

            bool success = false;

            if (fileLoader.Succeeded())
            {
                pResource->m_element.Load(fileLoader.GetDataPtr(), fileLoader.GetSize(), BIND_FUNC(&OnLoadDone));
                success = WaitForLoad();
                fileLoader.Release(NO_CALLBACK, true);
            }

            pResource->m_state = success ? SaResource<T>::STATE_READY : SaResource<T>::STATE_ERROR;
        }
    }

    template <>
    void SaResourceManager::ResourceManagerThread_Load<SaEffect>(const SaResourceJob* pJob)
    {
        ms_tableMutex.Lock();
        SaResource<SaEffect>* pEffect = GetResourceTable<SaEffect>()->FastFind(pJob->GetResourceHash());
        ms_tableMutex.Unlock();

        SaFileLoader vertexShaderLoader;
        SaFileLoader fragmentShaderLoader;

        if (pEffect)
        {
            const int32_t MAX_NAME_SIZE = 64;

            bool success = false;
            char shaderFileName[MAX_NAME_SIZE];
            sprintf_s(shaderFileName, MAX_NAME_SIZE, "%s_v%s", pJob->GetFileName(), SaEffect_Platform::FILE_EXTENSION);
            vertexShaderLoader.Load(shaderFileName, NO_CALLBACK, true, true);

            if (vertexShaderLoader.Succeeded())
            {
                sprintf_s(shaderFileName, MAX_NAME_SIZE, "%s_f%s", pJob->GetFileName(), SaEffect_Platform::FILE_EXTENSION);
                fragmentShaderLoader.Load(shaderFileName, NO_CALLBACK, true, true);
                if (fragmentShaderLoader.Succeeded())
                {
                    pEffect->m_element.Load(vertexShaderLoader.GetDataPtr(), fragmentShaderLoader.GetDataPtr(), BIND_FUNC(&OnLoadDone));
                    success = WaitForLoad();
                    fragmentShaderLoader.Release(NO_CALLBACK, true);
                }

                vertexShaderLoader.Release(NO_CALLBACK, true);
            }

            pEffect->m_state = success ? SaResource<SaEffect>::STATE_READY : SaResource<SaEffect>::STATE_ERROR;
        }
    }

    template <class T>
    void SaResourceManager::ResourceManagerThread_Unload(const SaResourceJob* pJob)
    {
        ms_tableMutex.Lock();
        SaResource<T>* pResource = GetResourceTable<T>()->FastFind(pJob->GetResourceHash());
        ms_tableMutex.Unlock();

        if (pResource)
        {
            if (--pResource->m_refCount <= 0)
            {
                pResource->m_element.Unload(BIND_FUNC(&OnLoadDone));
                WaitForLoad();

                ms_tableMutex.Lock();
                GetResourceTable<T>()->FastRemove(pResource->m_hash);
                ms_tableMutex.Unlock();
            }
        }
    }

}
