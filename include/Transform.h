#include <glm/glm.hpp>

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
