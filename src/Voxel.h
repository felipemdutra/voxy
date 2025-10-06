#ifndef VOXEL_H
#define VOXEL_H

#include <vector>
#include <glm/glm.hpp>

#include "block_type.h"
#include "defs.h"

constexpr float kBlockSideLen = 0.5f; // Every block will have the same lenght
                                      // for all sides.

/*
 * Should be created by it's parent chunk.
 */
class Block {
        glm::ivec3 pos_; // Block's position inside it's chunk.
        BlockType block_type_;

        static const std::vector<float> kVertices;
        static const std::vector<u32> kIndices;

        static std::vector<float> StartVertices();
        static std::vector<u32> StartIndices();

public:
        Block(int x, int y, int z, BlockType type);
        Block(glm::ivec3 pos, BlockType type);

        inline const glm::ivec3 &GetPosInChunk() const { return pos_; }

        inline const int GetX() const { return pos_.x; };
        inline const int GetY() const { return pos_.y; };
        inline const int GetZ() const { return pos_.z; };

        inline void SetBlockType(BlockType new_type) { block_type_ = new_type; }

        inline void SetPos(const glm::ivec3 &new_pos) { pos_ = new_pos; }
        inline void SetPos(int x, int y, int z) 
        {
                pos_.x = x;
                pos_.y = y;
                pos_.z = z;
        }
};

#endif //VOXEL_H
