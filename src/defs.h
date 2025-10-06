#ifndef DEFS_H
#define DEFS_H

#include <cstdint>
#include <wrapgl/wrapgl.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

inline wgl::VertexLayout& GetGlobalDefaultVertexLayout() {
        static wgl::VertexLayout layout;

        return layout;
}


#endif //DEFS_H
