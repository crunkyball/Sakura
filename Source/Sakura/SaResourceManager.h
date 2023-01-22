/*************************************************************
Sakura Game Framework : SaResourceManager.h
Author: Darrell Blake

Note: The hash table used uses a linked list for the buckets. 
This means that the resources will be stored non-contiguously 
in memory and as such won't be cache efficient. At some point 
this needs to be changed to contiguous pool of resources which 
the hash table contains pointers into. On the TODO list.
*************************************************************/

#ifndef _SA_RESOURCE_MANAGER_H
#define _SA_RESOURCE_MANAGER_H

//Static class to manage resources.

#include "SaCore.h"
#include "SaEffect.h"
#include "SaHashTable.h"
#include "SaTexture.h"
#include "SaModel.h"
#include <SakuraThread/SaMutex.h>
#include <SakuraThread/SaSemaphore.h>
#include <SakuraThread/SaThread.h>
#include <SakuraThread/SaAsyncJobQueue.h>
#include "SaResourceJob.h"
#include "SaResource.h"

namespace Sakura
{
    class SaResourceManager
    {
    public:
        struct InitParams
        {
            uint32_t    TextureHashTableSize;
            uint32_t    EffectHashTableSize;
            uint32_t    ModelHashTableSize;
        };

        static void Initialise(const InitParams& params);
        static void Release();

        static SaResource<SaTexture>* LoadTexture(const char* pFileName);
        static SaResource<SaEffect>* LoadEffect(const char* pFileName);
        static SaResource<SaModel>* LoadModel(const char* pFileName);

        static void UnloadTexture(SaResource<SaTexture>*& rpTexture);
        static void UnloadEffect(SaResource<SaEffect>*& rpEffect);
        static void UnloadModel(SaResource<SaModel>*& rpModel);

    private:
        template <class T>
        static void ReleaseResources(SaHashTable<const char*, SaResource<T>>* pTable);

        template <class T>
        static SaResource<T>* LoadResource(const char* pFileName);

        template <class T>
        static void UnloadResource(SaResource<T>*& rpResource);

        static void ResourceManagerThread_Main();

        template <class T>
        static SaHashTable<const char*, SaResource<T>>* GetResourceTable() { SA_FAIL("No specialisation!"); return NULL; }
        template <>
        static SaHashTable<const char*, SaResource<SaEffect>>* GetResourceTable<SaEffect>() { return ms_pEffects; }
        template <>
        static SaHashTable<const char*, SaResource<SaTexture>>* GetResourceTable<SaTexture>() { return ms_pTextures; }
        template <>
        static SaHashTable<const char*, SaResource<SaModel>>* GetResourceTable<SaModel>() { return ms_pModels; }

        template <class T>
        static void ResourceManagerThread_Load(const SaResourceJob* pJob);
        template <>
        static void ResourceManagerThread_Load<SaEffect>(const SaResourceJob* pJob);

        template <class T>
        static void ResourceManagerThread_Unload(const SaResourceJob* pJob);

        static bool WaitForLoad();
        static void OnLoadDone(bool success);

        static bool                                         ms_resourceManagerThreadExit;
        static SakuraThread::SaThread                       ms_resourceManagerThread;
        static SakuraThread::SaAsyncJobQueue<SaResourceJob> ms_resourceManagerJobQueue;

        static bool                             ms_blockLoadDone;
        static SakuraThread::SaMutex                ms_blockLoadMutex;
        static SakuraThread::SaConditionVariable    ms_blockLoadCondition;
        static bool                             ms_blockLoadResult;

        static SakuraThread::SaMutex                ms_tableMutex;
        static SaHashTable<const char*, SaResource<SaTexture>>* ms_pTextures;
        static SaHashTable<const char*, SaResource<SaEffect>>*  ms_pEffects;
        static SaHashTable<const char*, SaResource<SaModel>>*   ms_pModels;
    };
}

#include "SaResourceManager.inl"

#endif  //_SA_RESOURCE_MANAGER_H
