#include "Input.h"

bool Input::INIT()
{
    for (BYTE i = 1; i < 255; i++)
    {
        Input::keys[i] = NOTPRESS;
    }
}

void Input::InputUpdate()
{
    for (BYTE i = 1; i < 255; i++)
    {
        Input::keys[i] = Input::getKeyState(Input::keys[i]);
    }
}

Input::States Input::getKeyState(BYTE keyValue)
{
    switch (Input::keys[keyValue])
    {
        case Input::NOTPRESS:
            if (GetAsyncKeyState(keyValue) < 0) 
            {
                Input::keys[keyValue] = Input::NOTPRESS;
            }
            else 
            {
                Input::keys[keyValue] = Input::PRESSED;
            }
        break;
        
        case Input::HOLD:
            if (GetAsyncKeyState(keyValue) < 0)
            {
                Input::keys[keyValue] = Input::RELEASED;
            }
            else
            {
                Input::keys[keyValue] = Input::HOLD;
            }
        break;
        
        case Input::PRESSED:
            if (GetAsyncKeyState(keyValue) < 0)
            {
                Input::keys[keyValue] = Input::RELEASED;
            }
            else
            {
                Input::keys[keyValue] = Input::HOLD;
            }
        break;
        
        case Input::RELEASED:
            if (GetAsyncKeyState(keyValue) < 0)
            {
                Input::keys[keyValue] = Input::NOTPRESS;
            }
            else
            {
                Input::keys[keyValue] = Input::PRESSED;
            }
        break;
    }

    return Input::keys[keyValue];
}
