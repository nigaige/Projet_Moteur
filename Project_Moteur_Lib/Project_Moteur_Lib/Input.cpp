#include "Input.h"

bool Input::previousKey = NULL;

bool Input::anyKeyDown()
{
    return false;
}


bool Input::getKeyDown(char* VK)
{
    if (GetKeyState(*VK) & 0x8000)
        return true;
    else
        return false;
}

bool Input::getKeyUp(char* VK)
{
    if (Input::getKeyDown(VK))
    {
        Input::previousKey = VK;
        return false;
    }
    else
    {
        if (!(GetKeyState(*VK) & 0x8000) && Input::flag)
        {
            Input::flag = false;
            return true;
        }
        else {
            return false;
        }
    }
}

bool Input::getKeyDown(int VK)
{
    if (GetKeyState(VK) & 0x8000)
        return true;
    else
        return false;
}

bool Input::getKeyUp(int VK)
{
    if (GetKeyState(VK) & 0x8000)
    {
        Input::flag = true;
        return false;
    }
    else 
    {
        if (!(GetKeyState(VK) & 0x8000) && Input::flag)
        {
            Input::flag = false;
            return true;
        }
        else {
            return false;
        }
    }
}
