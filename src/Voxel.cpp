//
// Created by felipe on 10/4/25.
//

#include "Voxel.h"

#include <vector>

const std::vector<float> Block::kVertices = Block::StartVertices();
const std::vector<u32> Block::kIndices = Block::StartIndices();

Block::Block(int x, int y, int z, BlockType type)
{
        pos_ = {x, y, z};
        block_type_ = type;
}

std::vector<float> Block::StartVertices()
{
        float s = kBlockSideLen;
        return {
                -s, -s,  s,
                s, -s,  s,
                s,  s,  s,
                -s,  s,  s,

                s, -s, -s,
                -s, -s, -s,
                -s,  s, -s,
                s,  s, -s,

                -s, -s, -s,
                -s, -s,  s,
                -s,  s,  s,
                -s,  s, -s,

                s, -s,  s,
                s, -s, -s,
                s,  s, -s,
                s,  s,  s,

                -s,  s,  s,
                s,  s,  s,
                s,  s, -s,
                -s,  s, -s,

                -s, -s, -s,
                s, -s, -s,
                s, -s,  s,
                -s, -s,  s,
        };
}

std::vector<u32> Block::StartIndices()
{
        return {
                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                8, 9, 10, 10, 11, 8,
                12, 13, 14, 14, 15, 12,
                16, 17, 18, 18, 19, 16,
                20, 21, 22, 22, 23, 20
        };
}
