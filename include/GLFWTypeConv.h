#pragma once

#include "GLFWTypeConv.h"
#include <GLFW/glfw3.h>
#include <vector>

#include "GuiTypes.h"

KeyName convGLFWKey(int GLFWKey) {
    switch (GLFWKey) {
    case GLFW_KEY_SPACE:          return KeyName::SPACE_KEY;
    case GLFW_KEY_APOSTROPHE:     return KeyName::APOSTROPHE_KEY;
    case GLFW_KEY_COMMA:          return KeyName::COMMA_KEY;
    case GLFW_KEY_MINUS:          return KeyName::MINUS_KEY;
    case GLFW_KEY_PERIOD:         return KeyName::PERIOD_KEY;
    case GLFW_KEY_SLASH:          return KeyName::SLASH_KEY;
    case GLFW_KEY_0:              return KeyName::ZERO_KEY;
    case GLFW_KEY_1:              return KeyName::ONE_KEY;
    case GLFW_KEY_2:              return KeyName::TWO_KEY;
    case GLFW_KEY_3:              return KeyName::THREE_KEY;
    case GLFW_KEY_4:              return KeyName::FOUR_KEY;
    case GLFW_KEY_5:              return KeyName::FIVE_KEY;
    case GLFW_KEY_6:              return KeyName::SIX_KEY;
    case GLFW_KEY_7:              return KeyName::SEVEN_KEY;
    case GLFW_KEY_8:              return KeyName::EIGHT_KEY;
    case GLFW_KEY_9:              return KeyName::NINE_KEY;
    case GLFW_KEY_SEMICOLON:      return KeyName::SEMICOLON_KEY;
    case GLFW_KEY_EQUAL:          return KeyName::EQUAL_KEY;
    case GLFW_KEY_A:              return KeyName::A_KEY;
    case GLFW_KEY_B:              return KeyName::B_KEY;
    case GLFW_KEY_C:              return KeyName::C_KEY;
    case GLFW_KEY_D:              return KeyName::D_KEY;
    case GLFW_KEY_E:              return KeyName::E_KEY;
    case GLFW_KEY_F:              return KeyName::F_KEY;
    case GLFW_KEY_G:              return KeyName::G_KEY;
    case GLFW_KEY_H:              return KeyName::H_KEY;
    case GLFW_KEY_I:              return KeyName::I_KEY;
    case GLFW_KEY_J:              return KeyName::J_KEY;
    case GLFW_KEY_K:              return KeyName::K_KEY;
    case GLFW_KEY_L:              return KeyName::L_KEY;
    case GLFW_KEY_M:              return KeyName::M_KEY;
    case GLFW_KEY_N:              return KeyName::N_KEY;
    case GLFW_KEY_O:              return KeyName::O_KEY;
    case GLFW_KEY_P:              return KeyName::P_KEY;
    case GLFW_KEY_Q:              return KeyName::Q_KEY;
    case GLFW_KEY_R:              return KeyName::R_KEY;
    case GLFW_KEY_S:              return KeyName::S_KEY;
    case GLFW_KEY_T:              return KeyName::T_KEY;
    case GLFW_KEY_U:              return KeyName::U_KEY;
    case GLFW_KEY_V:              return KeyName::V_KEY;
    case GLFW_KEY_W:              return KeyName::W_KEY;
    case GLFW_KEY_X:              return KeyName::X_KEY;
    case GLFW_KEY_Y:              return KeyName::Y_KEY;
    case GLFW_KEY_Z:              return KeyName::Z_KEY;
    case GLFW_KEY_LEFT_BRACKET:   return KeyName::L_BRACKET_KEY;
    case GLFW_KEY_BACKSLASH:      return KeyName::BACKSLASH_KEY;
    case GLFW_KEY_RIGHT_BRACKET:  return KeyName::R_BRACKET_KEY;
    case GLFW_KEY_GRAVE_ACCENT:   return KeyName::GRAVE_ACCENT_KEY;
    case GLFW_KEY_ESCAPE:         return KeyName::ESC_KEY;
    case GLFW_KEY_ENTER:          return KeyName::ENTER_KEY;
    case GLFW_KEY_TAB:            return KeyName::TAB_KEY;
    case GLFW_KEY_BACKSPACE:      return KeyName::BACKSPACE_KEY;
    case GLFW_KEY_INSERT:         return KeyName::INSERT_KEY;
    case GLFW_KEY_DELETE:         return KeyName::DELETE_KEY;
    case GLFW_KEY_RIGHT:          return KeyName::RIGHT_ARROW_KEY;
    case GLFW_KEY_LEFT:           return KeyName::LEFT_ARROW_KEY;
    case GLFW_KEY_DOWN:           return KeyName::DOWN_ARROW_KEY;
    case GLFW_KEY_UP:             return KeyName::UP_ARROW_KEY;
    case GLFW_KEY_CAPS_LOCK:      return KeyName::CAPSLOCK_KEY;
    case GLFW_KEY_LEFT_SHIFT:     return KeyName::L_SHIFT_KEY;
    case GLFW_KEY_LEFT_CONTROL:   return KeyName::L_CTRL_KEY;
    case GLFW_KEY_LEFT_ALT:       return KeyName::L_ALT_KEY;
    case GLFW_KEY_LEFT_SUPER:     return KeyName::L_SUPER_KEY;
    case GLFW_KEY_RIGHT_SHIFT:    return KeyName::R_SHIFT_KEY;
    case GLFW_KEY_RIGHT_CONTROL:  return KeyName::R_CTRL_KEY;
    case GLFW_KEY_RIGHT_ALT:      return KeyName::R_ALT_KEY;
    case GLFW_KEY_RIGHT_SUPER:    return KeyName::R_SUPER_KEY;
    default:                      return KeyName::UNKNOWN_KEY;
    }
}

std::vector<ModKeyName> convGLFWMods(int GLFWMods) {
    std::vector<ModKeyName> modsList;
    if (GLFWMods & GLFW_MOD_CONTROL)   modsList.push_back(MOD_CTRL);
    if (GLFWMods & GLFW_MOD_SHIFT)     modsList.push_back(MOD_SHIFT);
    if (GLFWMods & GLFW_MOD_ALT)       modsList.push_back(MOD_ALT);
    if (GLFWMods & GLFW_MOD_SUPER)     modsList.push_back(MOD_SUPER);
    if (GLFWMods & GLFW_MOD_CAPS_LOCK) modsList.push_back(MOD_CAPSLOCK);
    if (GLFWMods & GLFW_MOD_NUM_LOCK)  modsList.push_back(MOD_NUMLOCK);
    return modsList;
}

MouseButtonType convGLFWMouseType(int GLFWButton) {
    switch (GLFWButton) {
    case GLFW_MOUSE_BUTTON_LEFT:    return MouseButtonType::MOUSE_LEFT;
    case GLFW_MOUSE_BUTTON_RIGHT:   return MouseButtonType::MOUSE_RIGHT;
    case GLFW_MOUSE_BUTTON_MIDDLE:  return MouseButtonType::MOUSE_MIDDLE;
    default:                        return MouseButtonType::MOUSE_UNKNOWN;
    }
}
