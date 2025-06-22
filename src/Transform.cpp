#include "Transform.h"

template <typename T>
Transform<T>::Transform(float scalar) : transform(scalar) {}

template <typename T>
Transform<T>::Transform(glm::vec2 vec2) : transform(vec2) {}

template <typename T>
Transform<T>::Transform(glm::vec4 vec4) : transform(vec4) {}
