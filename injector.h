#ifndef INJECTOR_H
#define INJECTOR_H

#include <Windows.h>
#include <Psapi.h>
#include <string>

namespace Injector
{
    bool injectDLL(HANDLE processHandle, const char * dllPath);
    HANDLE getProcessHandle(char * processName);
}

#endif // INJECTOR_H
