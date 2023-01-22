/*************************************************************
Sakura Game Framework : SaResourceLoader.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RESOURCE_LOADER_H
#define _SA_RESOURCE_LOADER_H

#include "SaCore.h"
#include "SaFileLoader.h"

namespace Sakura
{
    class SaResourceLoader
    {
    public:
        SaResourceLoader();

        void LoadFromFile(const char* pFileName, bool addNTC = false);
        //Effects have two files. Probably should just accept an array of file names 
        //if it becomes a popular feature.
        void LoadFromFile(const char* pFileName1, const char* pFileName2, bool addNTC = false);

    private:
        void OnFileRead(SaFileLoader::EResult result);

        static const uint32_t   MAX_FILENAME_LENGTH = 32;
        char                    m_fileNames[2][MAX_FILENAME_LENGTH];
        SaFileLoader            m_fileLoaders[2];
    };
}

#endif  //_SA_RESOURCE_LOADER_H
