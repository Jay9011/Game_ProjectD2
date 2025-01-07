#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// Direct 3D
#include <d3d9.h>
#include <d3dx9.h>

// 입출력 관련
#include <stdlib.h>
#include <tchar.h>

// 메모리 관련
#include <malloc.h>
#include <memory.h>

// Third Party
#include <AntTweakBar.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")