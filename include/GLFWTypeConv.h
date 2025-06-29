#pragma once

#include "GLFWTypeConv.h"
#include <GLFW/glfw3.h>
#include <vector>

#include "GuiTypes.h"

KeyName convGLFWKey(int GLFWKey) {
    switch (GLFWKey) {
    case GLFW_KEY_SPACE:          return KeyName::spaceKey;
    case GLFW_KEY_APOSTROPHE:     return KeyName::apostropheKey;
    case GLFW_KEY_COMMA:          return KeyName::commaKey;
    case GLFW_KEY_MINUS:          return KeyName::minusKey;
    case GLFW_KEY_PERIOD:         return KeyName::periodKey;
    case GLFW_KEY_SLASH:          return KeyName::slashKey;
    case GLFW_KEY_0:              return KeyName::zeroKey;
    case GLFW_KEY_1:              return KeyName::oneKey;
    case GLFW_KEY_2:              return KeyName::twoKey;
    case GLFW_KEY_3:              return KeyName::threeKey;
    case GLFW_KEY_4:              return KeyName::fourKey;
    case GLFW_KEY_5:              return KeyName::fiveKey;
    case GLFW_KEY_6:              return KeyName::sixKey;
    case GLFW_KEY_7:              return KeyName::sevenKey;
    case GLFW_KEY_8:              return KeyName::eightKey;
    case GLFW_KEY_9:              return KeyName::nineKey;
    case GLFW_KEY_SEMICOLON:      return KeyName::semicolonKey;
    case GLFW_KEY_EQUAL:          return KeyName::equalKey;
    case GLFW_KEY_A:              return KeyName::aKey;
    case GLFW_KEY_B:              return KeyName::bKey;
    case GLFW_KEY_C:              return KeyName::cKey;
    case GLFW_KEY_D:              return KeyName::dKey;
    case GLFW_KEY_E:              return KeyName::eKey;
    case GLFW_KEY_F:              return KeyName::fKey;
    case GLFW_KEY_G:              return KeyName::gKey;
    case GLFW_KEY_H:              return KeyName::hKey;
    case GLFW_KEY_I:              return KeyName::iKey;
    case GLFW_KEY_J:              return KeyName::jKey;
    case GLFW_KEY_K:              return KeyName::kKey;
    case GLFW_KEY_L:              return KeyName::lKey;
    case GLFW_KEY_M:              return KeyName::mKey;
    case GLFW_KEY_N:              return KeyName::nKey;
    case GLFW_KEY_O:              return KeyName::oKey;
    case GLFW_KEY_P:              return KeyName::pKey;
    case GLFW_KEY_Q:              return KeyName::qKey;
    case GLFW_KEY_R:              return KeyName::rKey;
    case GLFW_KEY_S:              return KeyName::sKey;
    case GLFW_KEY_T:              return KeyName::tKey;
    case GLFW_KEY_U:              return KeyName::uKey;
    case GLFW_KEY_V:              return KeyName::vKey;
    case GLFW_KEY_W:              return KeyName::wKey;
    case GLFW_KEY_X:              return KeyName::xKey;
    case GLFW_KEY_Y:              return KeyName::yKey;
    case GLFW_KEY_Z:              return KeyName::zKey;
    case GLFW_KEY_LEFT_BRACKET:   return KeyName::leftBracketKey;
    case GLFW_KEY_BACKSLASH:      return KeyName::backslashKey;
    case GLFW_KEY_RIGHT_BRACKET:  return KeyName::rightBracketKey;
    case GLFW_KEY_GRAVE_ACCENT:   return KeyName::graveAccentKey;
    case GLFW_KEY_ESCAPE:         return KeyName::escKey;
    case GLFW_KEY_ENTER:          return KeyName::enterKey;
    case GLFW_KEY_TAB:            return KeyName::tabKey;
    case GLFW_KEY_BACKSPACE:      return KeyName::backspaceKey;
    case GLFW_KEY_INSERT:         return KeyName::insertKey;
    case GLFW_KEY_DELETE:         return KeyName::deleteKey;
    case GLFW_KEY_RIGHT:          return KeyName::rightArrowKey;
    case GLFW_KEY_LEFT:           return KeyName::leftArrowKey;
    case GLFW_KEY_DOWN:           return KeyName::downArrowKey;
    case GLFW_KEY_UP:             return KeyName::upArrowKey;
    case GLFW_KEY_CAPS_LOCK:      return KeyName::capsLockKey;
    case GLFW_KEY_LEFT_SHIFT:     return KeyName::leftShiftKey;
    case GLFW_KEY_LEFT_CONTROL:   return KeyName::leftCtrlKey;
    case GLFW_KEY_LEFT_ALT:       return KeyName::leftAltKey;
    case GLFW_KEY_LEFT_SUPER:     return KeyName::leftSuperKey;
    case GLFW_KEY_RIGHT_SHIFT:    return KeyName::rightShiftKey;
    case GLFW_KEY_RIGHT_CONTROL:  return KeyName::rightCtrlKey;
    case GLFW_KEY_RIGHT_ALT:      return KeyName::rightAltKey;
    case GLFW_KEY_RIGHT_SUPER:    return KeyName::rightSuperKey;
    default:                     return KeyName::unknownKey;
    }
}

std::vector<ModKeyName> convGLFWMods(int GLFWMods) {
    std::vector<ModKeyName> modsList;
    if (GLFWMods & GLFW_MOD_CONTROL)   modsList.push_back(ModCtrl);
    if (GLFWMods & GLFW_MOD_SHIFT)     modsList.push_back(ModShift);
    if (GLFWMods & GLFW_MOD_ALT)       modsList.push_back(ModAlt);
    if (GLFWMods & GLFW_MOD_SUPER)     modsList.push_back(ModSuper);
    if (GLFWMods & GLFW_MOD_CAPS_LOCK) modsList.push_back(ModCapsLock);
    if (GLFWMods & GLFW_MOD_NUM_LOCK)  modsList.push_back(ModNumLock);
    return modsList;
}

MouseButtonType convGLFWMouseType(int GLFWButton) {
    switch (GLFWButton) {
    case GLFW_MOUSE_BUTTON_LEFT:    return MouseButtonType::MouseLeft;
    case GLFW_MOUSE_BUTTON_RIGHT:   return MouseButtonType::MouseRight;
    case GLFW_MOUSE_BUTTON_MIDDLE:  return MouseButtonType::MouseMiddle;
    default:                        return MouseButtonType::MouseUnknown;
    }
}
