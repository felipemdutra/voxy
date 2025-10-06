#include "Block.h"

#include <vector>

float s = kBlockSideLen;

Block::Block(int x, int y, int z, BlockType type)
{
        pos_ = {x, y, z};
        block_type_ = type;
}

const std::vector<glm::vec3> Block::kRightFace = {
        {s, -s, -s},  // bottom-back
        {s, -s,  s},  // bottom-front
        {s,  s,  s},  // top-front
        {s,  s, -s}   // top-back
};
const std::vector<u32> Block::kRightFaceIdx = {
        0, 1, 2, 2, 3, 0
};

const std::vector<glm::vec3> Block::kLeftFace = {
        {-s, -s,  s},  // bottom-front
        {-s, -s, -s},  // bottom-back
        {-s,  s, -s},  // top-back
        {-s,  s,  s}   // top-front
};

const std::vector<u32> Block::kLeftFaceIdx = {
        0, 1, 2, 2, 3, 0
};

const std::vector<glm::vec3> Block::kFrontFace = {
        {-s, -s,  s},
        { s, -s,  s},
        { s,  s,  s},
        {-s,  s,  s}
};
const std::vector<u32> Block::kFrontFaceIdx = {
        0, 1, 2, 2, 3, 0
};

const std::vector<glm::vec3> Block::kBackFace = {
        {-s, -s, -s},  // bottom-left
        { s, -s, -s},  // bottom-right
        { s,  s, -s},  // top-right
        {-s,  s, -s}   // top-left
};

const std::vector<u32> Block::kBackFaceIdx = {
        0, 1, 2, 2, 3, 0
};

const std::vector<glm::vec3> Block::kUpFace = {
        {-s,  s,  s},
        { s,  s,  s},
        { s,  s, -s},
        {-s,  s, -s}
};

const std::vector<u32> Block::kUpFaceIdx = {
        0, 1, 2, 2, 3, 0
};

const std::vector<glm::vec3> Block::kDownFace = {
        {-s, -s, -s},
        { s, -s, -s},
        { s, -s,  s},
        {-s, -s,  s}
};

const std::vector<u32> Block::kDownFaceIdx = {
        0, 1, 2, 2, 3, 0
};

