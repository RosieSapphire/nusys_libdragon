#include <string.h>

#include "vector.h"

void vector_copy(f32 *dst, f32 *src, u8 size)
{
	for (u8 i = 0; i < size; i++)
		dst[i] = src[i];
}
