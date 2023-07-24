#include "structs.hpp"
#pragma once
bool isAppOpen(const std::wstring &appName);
#pragma once
std::wstring GetCurrentDirectoryW();
#pragma once
std::string convertWStringToUtf8(const std::wstring &wstr);
#pragma once

// i stole this
bool IsLineIntersect(vector<Vector2> &CircleToPoint, vector<Vector2> &RecLine)
{
    Vector2 l1p1 = CircleToPoint[0];
    Vector2 l1p2 = CircleToPoint[1];
    Vector2 l2p1 = RecLine[0];
    Vector2 l2p2 = RecLine[1];
    float q = (l1p1.y - l2p1.y) * (l2p2.x - l2p1.x) - (l1p1.x - l2p1.x) * (l2p2.y - l2p1.y);
    float d = (l1p2.x - l1p1.x) * (l2p2.y - l2p1.y) - (l1p2.y - l1p1.y) * (l2p2.x - l2p1.x);

    if (d == 0)
    {
        return false;
    }

    float r = q / d;

    q = (l1p1.y - l2p1.y) * (l1p2.x - l1p1.x) - (l1p1.x - l2p1.x) * (l1p2.y - l1p1.y);
    float s = q / d;

    if (r <= 0 || r >= 1 || s <= 0 || s >= 1)
    {
        return false;
    }
    return true;
}

bool LineRectangleCollision(vector<Vector2> &CircleToPoint, vector<vector<Vector2>> &RecLines, int size)
{

    for (int j = 0; j < size; j++)
    {
        if (IsLineIntersect(CircleToPoint, RecLines[j]))
        {
            return true;
        }
    }
    return false;
}
string FormatTime(float timesecond)
{
    string combine;
    int second = timesecond;
    int milisecond = timesecond * 1000;
    int minute = second / 60;
    int hour = minute / 60;
    int day = hour / 24;
    if (day > 0)
    {
        string daystr = TextFormat("%i", (day));
        combine = combine + daystr + ":";
    }

    if (hour > 0)
    {
        string hourstr = TextFormat("%02i", (hour % 24));
        combine = combine + hourstr + ":";
    }

    if (minute > 0)
    {
        string minutestr = TextFormat("%02i", (minute % 60));
        combine = combine + minutestr + ":";
    }
    string milistr = TextFormat("%03i", (milisecond % 1000));
    string secondstr = TextFormat("%02i", (second % 60));
    combine = combine + secondstr + ":" + milistr;
    return combine;
}

void StopwatchToggle(std::wstring appName, vector<Stopwatch> &osuStopwatch, System &settings)
{
    // cout << settings.sessionCount;
    int fontSize = settings.screenHeight / 10;
    if (isAppOpen(appName))
    {

        if (!settings.appOpen) // start up sequence
        {

            settings.sessionCount++;
            osuStopwatch.push_back(Stopwatch());
            osuStopwatch[settings.sessionCount].ToggleSession(&osuStopwatch[settings.sessionCount].timeStart, &osuStopwatch[settings.sessionCount].dateStart);
            settings.appOpen = true;
        }
        Stopwatch osuResult = osuStopwatch[settings.sessionCount];
        osuStopwatch[settings.sessionCount].sessionTime += GetFrameTime();
        string tease = "You are playing osu! for ";
        DrawText(tease.c_str(), settings.screenWidth / 2.0f - MeasureText(tease.c_str(), fontSize) / 2, 0, fontSize, PINK);
        string addictTime = FormatTime(osuResult.sessionTime);
        DrawText(addictTime.c_str(), settings.screenWidth / 2.0f - MeasureText(addictTime.c_str(), fontSize) / 2, fontSize + 10, fontSize, PINK);

        DrawText("SINCE", settings.screenWidth / 2.0 - MeasureText("SINCE", fontSize) / 2, 3 * (fontSize + 10), fontSize, PINK);
        DrawText(osuResult.timeStart.c_str(), settings.screenWidth / 2.0 - MeasureText(osuResult.timeStart.c_str(), fontSize) / 2, 4 * (fontSize + 10), fontSize, PINK);
        DrawText(osuResult.dateStart.c_str(), settings.screenWidth / 2.0 - MeasureText(osuResult.dateStart.c_str(), fontSize) / 2, 5 * (fontSize + 10), fontSize, PINK);
        return;
    }
    if (settings.appOpen && settings.sessionCount >= 0) // shut down sequence
    {

        settings.appOpen = false;
        osuStopwatch[settings.sessionCount].ToggleSession(&osuStopwatch[settings.sessionCount].timeEnd, &osuStopwatch[settings.sessionCount].dateEnd);
    }
    if (settings.sessionCount < 0)
    {

        DrawText("You are not playing osu!", settings.screenWidth / 2.0f - MeasureText("You are not playing osu!", fontSize) / 2, 0, fontSize, GREEN);

        DrawText("Since the app opening", settings.screenWidth / 2.0f - MeasureText("Since the app opening", fontSize) / 2, 1 * (fontSize + 10), fontSize, GREEN);
    }
    else
    {
        Stopwatch osuResult = osuStopwatch[settings.sessionCount];
        string tease = "You have played osu! for: ";
        DrawText(tease.c_str(), settings.screenWidth / 2.0f - MeasureText(tease.c_str(), fontSize) / 2, 0, fontSize, PINK);
        string addictTime = FormatTime(osuResult.sessionTime);
        DrawText(addictTime.c_str(), settings.screenWidth / 2.0f - MeasureText(addictTime.c_str(), fontSize) / 2, fontSize + 10, fontSize, PINK);
        DrawText("END TIME:", settings.screenWidth - MeasureText(osuResult.dateEnd.c_str(), fontSize) / 2 - MeasureText("END TIME:", fontSize) / 2, 3 * (fontSize + 10), fontSize, PINK);
        DrawText(osuResult.timeEnd.c_str(), settings.screenWidth - MeasureText(osuResult.dateEnd.c_str(), fontSize) / 2 - MeasureText(osuResult.timeEnd.c_str(), fontSize) / 2, 4 * (fontSize + 10), fontSize, PINK);
        DrawText(osuResult.dateEnd.c_str(), settings.screenWidth - MeasureText(osuResult.dateEnd.c_str(), fontSize), 5 * (fontSize + 10), fontSize, PINK);

        DrawText("START TIME:", 0, 3 * (fontSize + 10), fontSize, PINK);
        DrawText(osuResult.timeStart.c_str(), 0 + MeasureText("START TIME:", fontSize) / 2 - MeasureText(osuResult.timeStart.c_str(), fontSize) / 2, 4 * (fontSize + 10), fontSize, PINK);
        DrawText(osuResult.dateEnd.c_str(), 0 + MeasureText("START TIME:", fontSize) / 2 - MeasureText(osuResult.dateStart.c_str(), fontSize) / 2, 5 * (fontSize + 10), fontSize, PINK);
    }
}
template <typename T>
bool CheckEveryPermutation(vector<Vector2> &CircleToPoint, vector<T> &Rec, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (Rec[i].visible == false)
        {
            continue;
        }
        vector<Vector2> BeginPos = {{Rec[i].position.x, Rec[i].position.y},
                                    {Rec[i].position.x + Rec[i].size.x, Rec[i].position.y},
                                    {Rec[i].position.x, Rec[i].position.y + Rec[i].size.y},
                                    {Rec[i].position.x + Rec[i].size.x, Rec[i].position.y + Rec[i].size.y}};
        vector<vector<Vector2>>
            RecLines = {{BeginPos[0], BeginPos[1]}, {BeginPos[0], BeginPos[2]}, {BeginPos[1], BeginPos[3]}, {BeginPos[2], BeginPos[3]}};
        if (LineRectangleCollision(CircleToPoint, RecLines, RecLines.size()))
        {
            return true;
        }
    }

    return false;
}

int RandomRange(int min, int max)
{
    int range;
    if (max < min)
    {
        range = min - max + 1;
        return (rand() % range) + max;
    }
    else
    {
        range = max - min + 1;
        return (rand() % range) + min;
    }
}

void DrawDonutV(Vector2 &CenterPos, float startrad, int delta, Color Color)
{
    for (int i = 0; i < delta * 10; i++)
    {
        DrawCircleLines(CenterPos.x, CenterPos.y, startrad + i / 10, Color);
    }
}
template <typename T>
void DrawRecs(T &ToDraw)
{
    ToDraw.DrawRec();
}
template <typename T>
void DrawCirc(T &ToDraw)
{
    ToDraw.DrawCircle();
}
template <typename T>
void DrawWall(T &ToDraw)
{
    ToDraw.DrawRecBlackOutline();
}
template <typename T>
void MoveAndDraw(T &ToDraw)
{
    ToDraw.Update();
}
template <typename T>
void DrawObject(vector<T> &ToDraw, int size, void (*DrawingSequence)(T &ToDraw))
{

    for (int i = 0; i < size; i++)
    {
        DrawingSequence(ToDraw[i]);
    }
}
