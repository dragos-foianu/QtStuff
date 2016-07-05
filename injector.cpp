#include "injector.h"

bool Injector::injectDLL(HANDLE processHandle, const char * dllPath)
{
    /* Allocate memory in the external process */
    void * remotePtr = VirtualAllocEx(processHandle, NULL, sizeof(dllPath), MEM_COMMIT, PAGE_READWRITE);
    if (remotePtr != NULL)
    {
        /* Write dllPath into the memory allocated previously */
        if (WriteProcessMemory(processHandle, remotePtr, dllPath, sizeof(dllPath), NULL))
        {
            /* Create a thread in the remote process and load library at remotePtr (our dll file name) */
            if (CreateRemoteThread(processHandle, NULL, NULL,
                (LPTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle((LPCWSTR) "Kernel32"), "LoadLibraryA"), remotePtr, NULL, NULL))
            {
                Sleep(500);

                /* Injected, now clean up */
                VirtualFreeEx(processHandle, remotePtr, sizeof(dllPath), MEM_RELEASE);
                return true;
            }
        }
    }
    return false;
}

HANDLE Injector::getProcessHandle(char * targetProcessName)
{
    HANDLE pHandle = NULL;
    DWORD runningProcesses[1024], cbNeeded;

    /* Enumerate processes */
    if (!EnumProcesses(runningProcesses, sizeof(runningProcesses), &cbNeeded))
    {
        return false;
    }

    for (size_t i = 0; i < (cbNeeded / sizeof(DWORD)); i++)
    {
        if (runningProcesses[i] && (pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, runningProcesses[i])))
        {
            HMODULE hModule;
            DWORD cbNeeded;

            /* Enumerate modules */
            if (EnumProcessModules(pHandle, &hModule, sizeof(hModule), &cbNeeded))
            {
                char openedProcessName[MAX_PATH];

                /* Get opened process name in ASCII and compare to target process name */
                GetModuleBaseNameA(pHandle, hModule, (LPSTR) openedProcessName, sizeof(openedProcessName));

                if (!strcmp(openedProcessName, targetProcessName))
                {
                    return pHandle;
                }

                /* Nope, close this process */
                CloseHandle(pHandle);
                pHandle = NULL;
            }
        }
    }

    return pHandle;
}

std::vector<std::string> Injector::listProcesses()
{
    HANDLE pHandle = NULL;
    DWORD runningProcesses[1024], cbNeeded;
    std::vector<std::string> processList;

    if (!EnumProcesses(runningProcesses, sizeof(runningProcesses), &cbNeeded))
    {
        return processList;
    }

    for (size_t i = 0; i < (cbNeeded / sizeof(DWORD)); i++)
    {
        if (runningProcesses[i] && (pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, runningProcesses[i])))
        {
            HMODULE hModule;
            DWORD cbNeeded;

            /* Enumerate modules */
            if (EnumProcessModules(pHandle, &hModule, sizeof(hModule), &cbNeeded))
            {
                char openedProcessName[MAX_PATH];

                /* Get opened process name in ASCII and compare to target process name */
                GetModuleBaseNameA(pHandle, hModule, (LPSTR) openedProcessName, sizeof(openedProcessName));

                processList.push_back(std::string(openedProcessName));

                /* Nope, close this process */
                CloseHandle(pHandle);
                pHandle = NULL;
            }
        }
    }

    return processList;
}
