#include "Utils.h"


//Utils::DebugLogMessage((vertToDisplay == nullptr) ? "true" : "false");


void Utils::DebugLogMessage(const char* message)
{
    std::string txt = message;
    txt += "\n";
    OutputDebugStringA(txt.c_str());
}

void Utils::DebugLogMessage(std::string* message)
{
    *message += "\n";
    OutputDebugStringA(message->c_str());
}

void Utils::DebugLogMessage(int* message)
{
    char msgd[10];
    sprintf_s(msgd, "%d\n", *message);
    OutputDebugStringA(msgd);
}

void Utils::DebugLogMessage(int message)
{
    char msgd[10];
    sprintf_s(msgd, "%d\n", message);
    OutputDebugStringA(msgd);
}


float Utils::DegToRad(float Angle)  { return Angle * DEGTORAD; }
float Utils::RadToDeg(float Rad)    { return Rad * RADTODEG; }