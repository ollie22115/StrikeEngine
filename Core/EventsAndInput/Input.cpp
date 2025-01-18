#include "Input.h"
#include <Windows.h>

namespace Strike {

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

        case LOC_KEY_TAB:
            return VK_TAB;

        case LOC_KEY_LEFT_SHIFT:
            return VK_LSHIFT;

        case LOC_KEY_RIGHT_SHIFT:
            return VK_RSHIFT;

        case LOC_KEY_LEFT_CONTROL:
            return VK_LCONTROL;

        case LOC_KEY_RIGHT_CONTROL:
            return VK_RCONTROL;

        case LOC_KEY_LEFT_ALT:
            return VK_LMENU;

        case LOC_KEY_RIGHT_ALT:
            return VK_RMENU;

        case LOC_KEY_LEFT_WINDOWS:
            return VK_LWIN;

        case LOC_KEY_RIGHT_WINDOWS:
            return VK_RWIN;

        case LOC_KEY_ESCAPE:
            return VK_ESCAPE;


        case LOC_KEY_F1:
            return VK_F1;
        case LOC_KEY_F2:
            return VK_F2;
        case LOC_KEY_F3:
            return VK_F3;
        case LOC_KEY_F4:
            return VK_F4;
        case LOC_KEY_F5:
            return VK_F5;
        case LOC_KEY_F6:
            return VK_F6;
        case LOC_KEY_F7:
            return VK_F7;
        case LOC_KEY_F8:
            return VK_F8;
        case LOC_KEY_F9:
            return VK_F9;
        case LOC_KEY_F10:
            return VK_F10;
        case LOC_KEY_F11:
            return VK_F11;
        case LOC_KEY_F12:
            return VK_F12;


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


        case LOC_KEY_COMMA:
            return VK_OEM_COMMA;
        }

        return windowsCode;
    }

}