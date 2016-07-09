#ifndef INJECTOR_H
#define INJECTOR_H

#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <vector>

namespace Injector
{
    bool injectDLL(HANDLE processHandle, const char * dllPath);
    HANDLE getProcessHandle(char * processName);
    std::vector<std::string> listProcesses();
}

#endif // INJECTOR_H
