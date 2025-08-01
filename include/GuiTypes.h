#pragma once

class CursorState {
    bool mouseDown;
};

enum GUIUnit {
    PIXELS,
    REL_PARENT,
    REL_SELF,
    REL_SCREEN,
    REL_WINDOW
};

enum TransformType {
    IDLE,
    MOVE,
    RESIZE_TOP,
    RESIZE_RIGHT,
    RESIZE_BOTTOM,
    RESIZE_LEFT,
    RESIZE_TOP_LEFT,
    RESIZE_TOP_RIGHT,
    RESIZE_BOTTOM_RIGHT,
    RESIZE_BOTTOM_LEFT
};

enum MouseButtonType {
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_UNKNOWN
};

enum KeyName {
    UNKNOWN_KEY,
    SPACE_KEY,
    APOSTROPHE_KEY,
    COMMA_KEY,
    MINUS_KEY,
    PERIOD_KEY,
    SLASH_KEY,
    ZERO_KEY,
    ONE_KEY,
    TWO_KEY,
    THREE_KEY,
    FOUR_KEY,
    FIVE_KEY,
    SIX_KEY,
    SEVEN_KEY,
    EIGHT_KEY,
    NINE_KEY,
    SEMICOLON_KEY,
    EQUAL_KEY,
    A_KEY,
    B_KEY,
    C_KEY,
    D_KEY,
    E_KEY,
    F_KEY,
    G_KEY,
    H_KEY,
    I_KEY,
    J_KEY,
    K_KEY,
    L_KEY,
    M_KEY,
    N_KEY,
    O_KEY,
    P_KEY,
    Q_KEY,
    R_KEY,
    S_KEY,
    T_KEY,
    U_KEY,
    V_KEY,
    W_KEY,
    X_KEY,
    Y_KEY,
    Z_KEY,
    L_BRACKET_KEY,
    BACKSLASH_KEY,
    R_BRACKET_KEY,
    GRAVE_ACCENT_KEY,
    ESC_KEY,
    ENTER_KEY,
    TAB_KEY,
    BACKSPACE_KEY,
    INSERT_KEY,
    DELETE_KEY,
    RIGHT_ARROW_KEY,
    LEFT_ARROW_KEY,
    DOWN_ARROW_KEY,
    UP_ARROW_KEY,
    CAPSLOCK_KEY,
    L_SHIFT_KEY,
    L_CTRL_KEY,
    L_ALT_KEY,
    L_SUPER_KEY,
    R_SHIFT_KEY,
    R_CTRL_KEY,
    R_ALT_KEY,
    R_SUPER_KEY
};

enum ModKeyName {
    MOD_CTRL,
    MOD_SHIFT,
    MOD_ALT,
    MOD_SUPER,
    MOD_CAPSLOCK,
    MOD_NUMLOCK
};
