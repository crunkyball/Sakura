/*************************************************************
Sakura Game Framework : SaGameProperties.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_GAME_PROPERTIES_H
#define _SA_GAME_PROPERTIES_H

#include "SaCore.h"

namespace Sakura
{
    class SaGameProperties
    {
    public:
        SaGameProperties(const char* name               = "No Name",
                         uint32_t xResolution           = 1280,
                         uint32_t yResolution           = 720,
                         uint32_t textureHashTableSize  = 16,
                         uint32_t effectHashTableSize   = 16,
                         uint32_t modelHashTableSize    = 16) :
                         m_name(name),
                         m_xResolution(xResolution),
                         m_yResolution(yResolution),
                         m_textureHashTableSize(textureHashTableSize),
                         m_effectHashTableSize(effectHashTableSize),
                         m_modelHashTableSize(modelHashTableSize)
        {}

        const char* m_name;
        uint32_t    m_xResolution;
        uint32_t    m_yResolution;

        uint32_t    m_textureHashTableSize;
        uint32_t    m_effectHashTableSize;
        uint32_t    m_modelHashTableSize;
    };
}

#endif  //_SA_GAME_PROPERTIES_H
