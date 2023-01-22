#include "SaResourceLoader.h"
#include "SaDebug.h"

using namespace Sakura;

SaResourceLoader::SaResourceLoader()
{
}

void SaResourceLoader::LoadFromFile(const char* pFileName, bool addNTC)
{
    SA_ASSERT(strlen(pFileName) < MAX_FILENAME_LENGTH-1, "Increase MAX_FILENAME_LENGTH");

    strncpy(m_fileNames[0], pFileName, MAX_FILENAME_LENGTH-1);
    m_fileNames[0][MAX_FILENAME_LENGTH-1] = 0;

    m_fileLoaders[0].Load(m_fileNames[0], BIND_MEMBER_FUNC(&SaResourceLoader::OnFileRead, this), addNTC);
}

void SaResourceLoader::LoadFromFile(const char* pFileName1, const char* pFileName2, bool addNTC)
{
    SA_ASSERT(strlen(pFileName1) < MAX_FILENAME_LENGTH-1, "Increase MAX_FILENAME_LENGTH");
    SA_ASSERT(strlen(pFileName2) < MAX_FILENAME_LENGTH-1, "Increase MAX_FILENAME_LENGTH");

    strncpy(m_fileNames[0], pFileName1, MAX_FILENAME_LENGTH-1);
    m_fileNames[0][MAX_FILENAME_LENGTH-1] = 0;

    strncpy(m_fileNames[1], pFileName2, MAX_FILENAME_LENGTH-1);
    m_fileNames[1][MAX_FILENAME_LENGTH-1] = 0;

    m_fileLoaders[0].Load(m_fileNames[0], BIND_MEMBER_FUNC(&SaResourceLoader::OnFileRead, this), addNTC);
    m_fileLoaders[1].Load(m_fileNames[1], BIND_MEMBER_FUNC(&SaResourceLoader::OnFileRead, this), addNTC);
}

void SaResourceLoader::OnFileRead(SaFileLoader::EResult result)
{
    if ((!m_fileLoaders[0].InUse() || m_fileLoaders[0].IsDone()) && 
        (!m_fileLoaders[1].InUse() || m_fileLoaders[1].IsDone()))
    {
        SA_HOOK();
    }
}
