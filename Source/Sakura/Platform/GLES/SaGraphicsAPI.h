/***************************************************
Sakura Game Framework : SaGraphicsAPI.h
Author: Darrell Blake

NOTE: This is just a helper header file for 
including the graphics API header(s).
***************************************************/

#ifndef _SA_GRAPHICS_API_H
#define _SA_GRAPHICS_API_H

#include <GLES2/gl2.h>
#include "../../SaDebug.h"

inline bool CheckOpenGLError(const char* doing, bool assert = false)
{
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        if (assert)
        {
            SA_FAIL("OpenGL error 0x%x: %s.", error, doing);
        }
        else
        {
            SA_PRINTF("OpenGL error 0x%x: %s.\n", error, doing);
        }

        return true;
    }

    return false;
}

#endif  //_SA_GRAPHICS_API_H
