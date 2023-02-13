/*************************************************************
Sakura Game Framework : SaResourceManager.cpp
Author: Darrell Blake
*************************************************************/

#include "SaResourceManager.h"
#include "SaEffect.h"
#include <cstdio>

using namespace Sakura;
using namespace SakuraThread;

bool SaResourceManager::ms_resourceManagerThreadExit = false;
SaThread SaResourceManager::ms_resourceManagerThread;
SaAsyncJobQueue<SaResourceJob> SaResourceManager::ms_resourceManagerJobQueue;
SaMutex SaResourceManager::ms_blockLoadMutex;
SaConditionVariable SaResourceManager::ms_blockLoadCondition;
bool SaResourceManager::ms_blockLoadDone = false;
bool SaResourceManager::ms_blockLoadResult = false;
SaMutex SaResourceManager::ms_tableMutex;

SaHashTable<const char*, SaResource<SaTexture>>* SaResourceManager::ms_pTextures = NULL;
SaHashTable<const char*, SaResource<SaEffect>>* SaResourceManager::ms_pEffects = NULL;
SaHashTable<const char*, SaResource<SaModel>>* SaResourceManager::ms_pModels = NULL;

void SaResourceManager::Initialise(const InitParams& params)
{
    ms_pTextures = new SaHashTable<const char*, SaResource<SaTexture>>(params.TextureHashTableSize, SaHash);
    ms_pEffects = new SaHashTable<const char*, SaResource<SaEffect>>(params.EffectHashTableSize, SaHash);
    ms_pModels = new SaHashTable<const char*, SaResource<SaModel>>(params.ModelHashTableSize, SaHash);

    ms_resourceManagerThreadExit = false;

    ms_resourceManagerThread.Initialise("Resource Manager Thread", ResourceManagerThread_Main);
    ms_resourceManagerThread.Run();
}

void SaResourceManager::Release()
{
    ReleaseResources(ms_pTextures);
    ReleaseResources(ms_pEffects);
    ReleaseResources(ms_pModels);

    ms_resourceManagerThreadExit = true;
    ms_resourceManagerJobQueue.Kill();
    ms_resourceManagerThread.Join();
}

SaResource<SaTexture>* SaResourceManager::LoadTexture(const char* pFileName)
{
    SaResource<SaTexture>* pResource = LoadResource<SaTexture>(pFileName);
    return pResource;
}

void SaResourceManager::UnloadTexture(SaResource<SaTexture>*& rpTexture)
{
    UnloadResource(rpTexture);
}

SaResource<SaEffect>* SaResourceManager::LoadEffect(const char* pFileName)
{
    SaResource<SaEffect>* pResource = LoadResource<SaEffect>(pFileName);
    return pResource;
}

void SaResourceManager::UnloadEffect(SaResource<SaEffect>*& rpEffect)
{
    UnloadResource(rpEffect);
}

SaResource<SaModel>* SaResourceManager::LoadModel(const char* pFileName)
{
    SaResource<SaModel>* pResource = LoadResource<SaModel>(pFileName);
    return pResource;
}

void SaResourceManager::UnloadModel(SaResource<SaModel>*& rpModel)
{
    UnloadResource(rpModel);
}

void SaResourceManager::ResourceManagerThread_Main()
{
    while (!ms_resourceManagerThreadExit)
    {
        ms_resourceManagerJobQueue.ProcessJobs(true);
    }
}

bool SaResourceManager::WaitForLoad()
{
    bool result = false;

    ms_blockLoadMutex.Lock();

    while (!ms_blockLoadDone)
    {
        ms_blockLoadCondition.Wait(ms_blockLoadMutex);
    }

    result = ms_blockLoadResult;
    ms_blockLoadDone = false;

    ms_blockLoadMutex.Unlock();

    return result;
}

void SaResourceManager::OnLoadDone(bool success)
{
    ms_blockLoadMutex.Lock();

    ms_blockLoadDone = true;
    ms_blockLoadResult = success;
    ms_blockLoadCondition.Signal();

    ms_blockLoadMutex.Unlock();
}

//Template specialisations
template <> SaHashTable<const char*, SaResource<SaEffect>>* SaResourceManager::GetResourceTable<SaEffect>() { return ms_pEffects; }
template <> SaHashTable<const char*, SaResource<SaTexture>>* SaResourceManager::GetResourceTable<SaTexture>() { return ms_pTextures; }
template <> SaHashTable<const char*, SaResource<SaModel>>* SaResourceManager::GetResourceTable<SaModel>() { return ms_pModels; }

//Specialise the effect loading as both the vert and fragment shaders are loaded into the resource.
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
