#include "util.h"
static int CreatProcess(const char* path) {
    //创建进程
    LPCTSTR applicationName = LPCTSTR(path);
    LPTSTR commandLine = NULL;
    LPSECURITY_ATTRIBUTES processAttributes = NULL;
    LPSECURITY_ATTRIBUTES threadAttributes = NULL;
    BOOL inheritHandles = FALSE;
    DWORD creationFlags = 0;
    LPVOID environment = NULL;
    LPCTSTR currentDirectory = NULL;
    LPSTARTUPINFO startupInfo = new STARTUPINFO();
    LPPROCESS_INFORMATION processInformation = new PROCESS_INFORMATION();

    ZeroMemory(startupInfo, sizeof(STARTUPINFO));
    startupInfo->cb = sizeof(STARTUPINFO);

    // Create the process
    BOOL result = CreateProcess(
        applicationName,
        commandLine,
        processAttributes,
        threadAttributes,
        inheritHandles,
        creationFlags,
        environment,
        currentDirectory,
        startupInfo,
        processInformation
    );

    if (result) {
        cout << "Process created successfully!" << endl;
        cout << "Process ID: " << processInformation->dwProcessId << endl;

        // Close process and thread handles
        CloseHandle(processInformation->hProcess);
        CloseHandle(processInformation->hThread);
    }
    else {
        int error_code = GetLastError();
        return error_code;
    }

    // Clean up allocated memory
    delete startupInfo;
    delete processInformation;

    return 0;
}
static void enumProcess() {
    //枚举并输出所有进程
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    int count = 0;
    if (Process32First(hSnapShot, &pEntry)) {
        cout << setw(35) << "Process Name" << setw(35) << "PID" << setw(35) << "Status" << endl;
        do {
            count++;
            char ch[260];
            char DefChar = ' ';
            WideCharToMultiByte(CP_ACP, 0, pEntry.szExeFile, -1, ch, 260, &DefChar, NULL);
            std::string s(ch);
            cout << setw(35) << s << setw(35) << pEntry.th32ProcessID << setw(35) << (pEntry.dwFlags ? "Stopped" : "Running") << endl;
        } while (Process32Next(hSnapShot, &pEntry));
    }
    CloseHandle(hSnapShot);
    cout << "-------------------------------------------------------\n";
    if (count > 0) {
        cout << "A total of " << count << " processes were found\n";
    }
    else {
        cout << "None of process was found\n";
    }
    cout << "-------------------------------------------------------\n";
}
static int searchProcess(const char* target) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    regex reg = regex(target);
    cmatch match;
    if (Process32First(hSnapShot, &pEntry)) {
        int count = 0;
        do {
            char ch[260];
            char DefChar = ' ';
            WideCharToMultiByte(CP_ACP, 0, pEntry.szExeFile, -1, ch, 260, &DefChar, NULL);
            std::string s(ch);
            
            bool result = regex_match(s.c_str(), match, reg);
            
            if (result) {
                count++;
                if (count == 1) {
                    cout << setw(35) << "Process Name" << setw(35) << "PID" << setw(35) << "Status" << endl;
                }
                cout << setw(35) << s << setw(35) << pEntry.th32ProcessID << setw(35) << (pEntry.dwFlags ? "Stopped" : "Running") << endl;
                
            }
            
        } while (Process32Next(hSnapShot, &pEntry));
        cout << "-------------------------------------------------------\n";
        if (count > 0) {
            cout << "A total of " << count << " processes were found\n";
        }
        else {
            cout << "None of process was found\n";
        }
        cout << "-------------------------------------------------------\n";
    }
    return 0;
}

static int searchProcess(int target_pid) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    target_pid = (DWORD)target_pid;
    if (Process32First(hSnapShot, &pEntry)) {
        int count = 0;
        do {
            
            if (pEntry.th32ProcessID == target_pid) {
                count++;
                char ch[260];
                char DefChar = ' ';
                if (count == 1) {
                    cout << setw(35) << "Process Name" << setw(35) << "PID" << setw(35) << "Status" << endl;
                }
                WideCharToMultiByte(CP_ACP, 0, pEntry.szExeFile, -1, ch, 260, &DefChar, NULL);
                string name(ch);
                cout << setw(35) << name << setw(35) << pEntry.th32ProcessID << setw(35) << (pEntry.dwFlags ? "Stopped" : "Running") << endl;

            }

        } while (Process32Next(hSnapShot, &pEntry));
        cout << "-------------------------------------------------------\n";
        if (count > 0) {
            cout << "A total of " << count << " processes were found\n";
        }
        else {
            cout << "None of process was found\n";
        }
        cout << "-------------------------------------------------------\n";
    }
    return 0;
}


static int CloseProcess(int PID) {
    //根据PID来关闭进程
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    int flag = 0;
    if (Process32First(hSnapShot, &pEntry)) {
        do {
            if (pEntry.th32ProcessID == PID) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
                TerminateProcess(hProcess, 9);
                char ch[260];
                char DefChar = ' ';
                WideCharToMultiByte(CP_ACP, 0, pEntry.szExeFile, -1, ch, 260, &DefChar, NULL);
                std::string s(ch);
                cout << "Process " << s <<"("<< pEntry.th32ProcessID <<")" << " terminated." << endl;
                flag = 1;
                break;
            }
        } while (Process32Next(hSnapShot, &pEntry));
    }
    CloseHandle(hSnapShot);
    return flag;
}
static int CloseProcess(string processName) {
    //根据进程名关闭进程
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    int flag = 0;
    if (Process32First(hSnapShot, &pEntry)) {
        do {
            if (strcmp((const char*)pEntry.szExeFile, processName.c_str()) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
                TerminateProcess(hProcess, 9);
                cout << "Process " << processName <<"(" << pEntry.th32ProcessID << ")"" terminated." << endl;
                flag = 1;
                break;
            }
        } while (Process32Next(hSnapShot, &pEntry));
    }
    CloseHandle(hSnapShot);
    return flag;
}