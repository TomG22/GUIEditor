#pragma once

class CursorState {
    bool mouseDown;
};

enum RectPos {
   None,
   Inside,
   TopLeft,
   TopRight,
   BottomRight,
   BottomLeft,
   Top,
   Right,
   Bottom,
   Left
};

enum TransformState {
    Idle,
    Move,
    ResizeTop,
    ResizeRight,
    ResizeBottom,
    ResizeLeft,
    ResizeTopLeft,
    ResizeTopRight,
    ResizeBottomRight,
    ResizeBottomLeft
};

enum MouseButtonType {
    MouseLeft,
    MouseRight,
    MouseMiddle,
    MouseUnknown
};

enum KeyName {
    unknownKey,
    spaceKey,
    apostropheKey,
    commaKey,
    minusKey,
    periodKey,
    slashKey,
    zeroKey,
    oneKey,
    twoKey,
    threeKey,
    fourKey,
    fiveKey,
    sixKey,
    sevenKey,
    eightKey,
    nineKey,
    semicolonKey,
    equalKey,
    aKey,
    bKey,
    cKey,
    dKey,
    eKey,
    fKey,
    gKey,
    hKey,
    iKey,
    jKey,
    kKey,
    lKey,
    mKey,
    nKey,
    oKey,
    pKey,
    qKey,
    rKey,
    sKey,
    tKey,
    uKey,
    vKey,
    wKey,
    xKey,
    yKey,
    zKey,
    leftBracketKey,
    backslashKey,
    rightBracketKey,
    graveAccentKey,
    escKey,
    enterKey,
    tabKey,
    backspaceKey,
    insertKey,
    deleteKey,
    rightArrowKey,
    leftArrowKey,
    downArrowKey,
    upArrowKey,
    capsLockKey,
    leftShiftKey,
    leftCtrlKey,
    leftAltKey,
    leftSuperKey,
    rightShiftKey,
    rightCtrlKey,
    rightAltKey,
    rightSuperKey
};

enum ModKeyName {
    ModCtrl,
    ModShift,
    ModAlt,
    ModSuper,
    ModCapsLock,
    ModNumLock
};
