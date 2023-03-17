#include "Input.h"


Input::Input()
{
    for (BYTE i = 1; i < 255; i++)
    {
        keys[i] = States::NOTPRESS;
    }
}


void Input::InputUpdate()
{
    for (BYTE i = 1; i < 255; i++)
    {
        keys[i] = Input::gatherKeyState(i);
    }
}

States Input::gatherKeyState(BYTE keyValue)
{
    SHORT value = GetAsyncKeyState(keyValue);

    switch (keys[keyValue])
    {
    case States::NOTPRESS:
        if (value < 0) return States::PRESSED;
        break;
    case States::PRESSED:
        return States::HOLD;
    case States::HOLD:
        if (value == 0) return States::RELEASED;
        break;
    case States::RELEASED:
        return States::NOTPRESS;
    }

    return keys[keyValue];
}

States Input::getKeyState(BYTE keyValue) {
    return keys[keyValue];
}
