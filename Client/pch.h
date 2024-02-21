#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <dinput.h>
#include <commdlg.h>

#include <crtdbg.h>
#include <assert.h>

#include <fstream>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <queue>

using std::vector;
using std::list;
using std::map;
using std::queue;
using std::make_pair;
using std::string;
using std::wstring;
using std::wifstream;
using std::wofstream;
using std::wstringstream;


#include "def.h"
#include "struct.h"
#include "func.h"

#include "CDebug.h"


#pragma comment (lib, "Msimg32.lib")



// Gdi+ 헤더
#include <objidl.h>
#include <gdiplus.h>

using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")