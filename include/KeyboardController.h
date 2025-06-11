#pragma once

/**
 * Class description...
 */

#include "AudioEngine.h"
#include <iostream>
#include <thread>

class KeyboardController {
public:
    AudioEngine* audioEngine;

/*    struct note {
        std::string soundName;
        bool isplaying = false;
        bool stopping = false;
        bool stopped = false;
    };
*/

    int* configMap;
    int configMapLength;
    int keyIndex;
    int octave = 4;


    // 18 key configMap: white: A -> ', black: W -> P | white: 29 -> 39, black: 16 -> 24
    // 24 Key configMap: white: tab -> \, black: 1 -> backspace | white: 14 -> 27, black: 1 -> 13

    // master key array with maps (using indices) as configMaps;...
    // consider merging master key to be alternating upper/lower rows for index abstraction

    int glfwKeyCodes[53] = {
    96, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 45, 61, 259,
    258, 81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 91, 93, 92,
    280, 65, 83, 68, 70, 71, 72, 74, 75, 76, 59, 39, 257,
    340, 90, 88, 67, 86, 66, 78, 77, 44, 46, 47, 344};


    std::string keyNamesMap[53] = {
    "`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "Backspace",
    "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "\\",
    "Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Right Shift",
    "Left Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Right Shift"};

    std::string controlsNames[5] = {"Sustain", "Octave Down", "Octave Up", "Velocity Down", "Velocity Up"};

    int controlsMap[5] = {42, 43, 44, 45, 46};

    int miniConfigMap[18] = {29, 16, 30, 17, 31, 32, 19, 33, 20, 34, 21, 35, 36, 23, 37, 24, 38, 39};
    int largeConfigMap[24] = {14, 1, 15, 2, 16, 17, 4, 18, 5, 19, 6, 20, 21, 8, 22, 9, 23, 24, 11, 25, 12, 26, 13, 27};


    KeyboardController(AudioEngine* audioEngine);
    void updateInterface();
    void processControlsInput(int key, int action);
    void processNoteInput(int key, int action);
    void playTone();
};