#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <wrapgl/wrapgl.h>

#include "Block.h"

enum Direction {
        kRight,
        kLeft,
        kFront,
        kBack,
        kUp,
        kDown,
};

class Chunk {
        static const int kChunkSize = 16; // 16x16x16 chunk size.

        Block *blocks[kChunkSize][kChunkSize][kChunkSize];

        GLuint vao_, vbo_, ebo_;
        u32 index_count_;

        bool dirty_ = true; // If dirty = true, we update the mesh with the updated vertex data.

        void InitializeChunk();
        void DestroyChunk();

        void UpdateVertexData();

        bool HasNeighbor(Block *block, Direction dir);

        static void AddFace(
                        Block *block,
                        const std::vector<glm::vec3> &vertex_in,
                        const std::vector<u32> &index_in,
                        std::vector<u32> &index_out,
                        std::vector<float> &vertex_out
                        );

public:
        Chunk();
        ~Chunk();

        void Render(wgl::Renderer &renderer);

        Block *GetBlockAt(const glm::ivec3 &pos);
        Block *GetBlockAt(int x, int y, int z);
};

#endif

