#include "Input.h"
#include <Windows.h>

uint16_t Input::getInput(uint16_t keyCode) {
    return GetAsyncKeyState(keyCodeLOCtoWindows(keyCode));
}

uint16_t Input::keyCodeLOCtoWindows(uint16_t windowsCode) {
    //TODO!!! Continue implementing different keys

    switch (windowsCode) {
        case LOC_KEY_LEFT:
            return VK_LEFT;

        case LOC_KEY_RIGHT:
            return VK_RIGHT;

        case LOC_KEY_UP:
            return VK_UP;

        case LOC_KEY_DOWN:
            return VK_DOWN;


        case LOC_KEY_SPACE:
            return VK_SPACE;


        case LOC_KEY_0:
            return 0x30;

        case LOC_KEY_1:
            return 0x31;

        case LOC_KEY_2:
            return 0x32;

        case LOC_KEY_3:
            return 0x33;

        case LOC_KEY_4:
            return 0x34;

        case LOC_KEY_5:
            return 0x35;

        case LOC_KEY_6:
            return 0x36;

        case LOC_KEY_7:
            return 0x37;

        case LOC_KEY_8:
            return 0x38;

        case LOC_KEY_9:
            return 0x39;

    }

    return windowsCode;
}
