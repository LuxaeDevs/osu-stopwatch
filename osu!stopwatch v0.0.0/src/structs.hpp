#include <iostream>
#include <vector>
#include <raylib.h>
#include <cmath>
#include <chrono>
#include <ctime>
#include <raymath.h>
#include <rlgl.h>
#include <raygui.h>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
using std::cout;

using std::string;
using std::vector;
int RandomRange(int min, int max);
struct System
{
    float screenWidth = 800.0f;
    float screenHeight = 480.0f;
    bool appOpen = false;
    int currentscreen = 0;
    int FPS = 300;
    int sessionCount = -1;
};

struct Stopwatch
{
    float sessionTime = 0;
    int year;
    int month;
    int day;
    string timeStart;
    string dateStart;
    string timeEnd;
    string dateEnd;
    Stopwatch()
    {
        timeStart = "";
        dateStart = "";
        timeEnd = "";
        dateEnd = "";
    }
    typedef std::chrono::system_clock Clock;
    struct tm *GetTime()
    {
        auto now = Clock::now();
        std::time_t now_c = Clock::to_time_t(now);
        struct tm *parts = std::localtime(&now_c);
        return parts;
    }
    void ToggleSession(string *timeSet, string *daySet)
    {
        struct tm *Time = GetTime();
        string strsec = TextFormat("%02i", Time->tm_sec);
        string strmin = TextFormat("%02i", Time->tm_min);
        string strhour = TextFormat("%02i", Time->tm_hour);
        *timeSet = strhour + ":" + strmin + ":" + strsec;
        string strday = TextFormat("%02i", Time->tm_mday);
        string strmonth = TextFormat("%02i", Time->tm_mon);
        string stryear = TextFormat("%02i", 1900 + Time->tm_year);
        *daySet = strday + "/" + strmonth + "/" + stryear;
    }
};

struct Objects
{
    bool visible = true;

    Color colorInfo;
    Vector2 direction = {0, 0};
    Vector2 velocity = {0, 0};
    Vector2 position = {0, 0};
    Objects(Color colorInfo, Vector2 position)
    {
        this->colorInfo = colorInfo;
        this->position = position;
    }
    void ChangeDirection(Vector2 direction)
    {
        this->direction = direction;
    }
};
struct GeneralRectangle
{
    Vector2 size;
};
