#pragma once
#include <stdlib.h>

#include "Vector3AndMatrix4x4.h"
Vector3 Lerp(const Vector3& from, const Vector3& v2, float t);
Vector3 SLerp(const Vector3& from, const Vector3& to, float t);
