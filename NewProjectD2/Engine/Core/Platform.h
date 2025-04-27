#pragma once

/** Window Platform 확인 */
#if defined(_WIN32) && defined(_WIN64)

#define PLATFORM_WINDOWS 1

#endif


/** Window Platform용 헤더 로드 */
#if PLATFORM_WINDOWS

#include "Core/Platform/WindowsPlatform.h"

#endif