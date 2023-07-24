#include "functions.hpp"

int main()
{

    System settings;

    vector<Stopwatch> osuStopwatch;
    InitWindow((int)settings.screenWidth, (int)settings.screenHeight, "osu! Stopwatch");
    SetTargetFPS(settings.FPS);
    std::wstring appName = L"osu!.exe";
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    // RefreshIfStuck(mainPlayer, hitbox, hitbox.size());
    // Get the full path of the current executable.
    // std::wstring currentDirectory = GetCurrentDirectoryW();
    // string fileName = convertWStringToUtf8(currentDirectory) + "\\Statistics";
    // string currentMonthString = fileName + "

    //";
    // int status = mkdir(fileName.c_str());
    // Create a new Excel book.

    while (!WindowShouldClose())
    {
        settings.screenWidth = GetScreenWidth();
        settings.screenHeight = GetScreenHeight();
        StopwatchToggle(appName, osuStopwatch, settings);

        // cout << osuStopwatch.sessionTime << '\n';
        //   Vector2 MousePos = GetMousePosition();
        //    Vector2 MouseDelta = GetMouseDelta();
        BeginDrawing();
        ClearBackground(BLACK);
        // Replace with the name of the application you want to check

        // textPrompt[0].OpenTextPrompt();

        EndDrawing();
    }
    CloseWindow();
}

#include <windows.h>
#include <Psapi.h>

std::string convertWStringToUtf8(const std::wstring &wstr)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), &strTo[0], size_needed, nullptr, nullptr);
    return strTo;
}

std::wstring GetCurrentDirectoryW()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    std::wstring wdir;
    wdir.reserve(pos);

    for (std::string::size_type i = 0; i < pos; ++i)
    {
        wdir.push_back(static_cast<wchar_t>(buffer[i]));
    }

    return wdir;
}

bool isAppOpen(const std::wstring &appName)
{
    DWORD processIds[1024], cbNeeded, processes;
    if (!EnumProcesses(processIds, sizeof(processIds), &cbNeeded))
    {
        return false;
    }

    processes = cbNeeded / sizeof(DWORD);
    for (DWORD i = 0; i < processes; i++)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIds[i]);
        if (hProcess)
        {
            WCHAR processName[MAX_PATH];
            DWORD size = sizeof(processName) / sizeof(processName[0]);
            if (GetModuleBaseNameW(hProcess, nullptr, processName, size))
            {
                if (_wcsicmp(processName, appName.c_str()) == 0)
                {
                    CloseHandle(hProcess);
                    return true;
                }
            }
            CloseHandle(hProcess);
        }
    }

    return false;
}