#pragma once

#include <cstdio>
#include <memory>

#if WIN32
#define _OS_WIN      1
#define _GAPI_GL     1
#include <Windows.h>
#endif

#include "Utils.h"

namespace Common
{
}