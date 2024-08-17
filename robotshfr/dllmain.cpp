// RobotsHFR - 60 FPS ASI Loader plugin for Robots (2005)
// 
// MIT License
// 
// Copyright (c) 2024 nastys
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <Windows.h>
#include <Detours.h>

typedef char (*originalFunc)(int classptr);
typedef char (*originalFunc)(int classptr);
originalFunc originalFuncEUPtr = (originalFunc)0x0049DA60;
originalFunc originalFuncUSPtr = (originalFunc)0x00472800;

char hookedFuncEU(int classptr)
{
    char result = originalFuncEUPtr(classptr);

    if (*(int*)0x007BB514 != 9) // level index != Bigweld Chase
    {
        *(int*)0x007AD258 = 60; // target FPS
    }

    return result;
}

char hookedFuncUS(int classptr)
{
    char result = originalFuncUSPtr(classptr);

    if (*(int*)0x007B324C != 9) // level index != Bigweld Chase
    {
        *(int*)0x007B2FEC = 60; // target FPS 1
        *(int*)0x00620020 = 60; // target FPS 2
    }

    return result;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        if (*reinterpret_cast<unsigned char*>(originalFuncEUPtr) == 0x83)
        {
            //MessageBoxW(NULL, L"EU version.", L"RobotsHFR", MB_OK);
            DetourAttach(&(PVOID&)originalFuncEUPtr, (PVOID)hookedFuncEU);
        }
        else if (*reinterpret_cast<unsigned char*>(originalFuncUSPtr) == 0x83)
        {
            //MessageBoxW(NULL, L"US version.", L"RobotsHFR", MB_OK);
            DetourAttach(&(PVOID&)originalFuncUSPtr, (PVOID)hookedFuncUS);
        }
        else
        {
            MessageBoxW(NULL, L"Unsupported game version.", L"RobotsHFR", MB_OK);
        }
        DetourTransactionCommit();
    }

    return TRUE;
}
