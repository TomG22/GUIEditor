class CursorState {
    bool mouseDown;
};

enum HoverState {
   None,
   Inside,
   TopLeft,
   TopRight,
   BottomRight,
   BottomLeft,
   Top,
   Right,
   Bottom,
   Left,
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
