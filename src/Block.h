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

        static const std::vector<glm::vec3> kRightFace;
        static const std::vector<glm::vec3> kLeftFace;
        static const std::vector<glm::vec3> kFrontFace;
        static const std::vector<glm::vec3> kBackFace;
        static const std::vector<glm::vec3> kUpFace;
        static const std::vector<glm::vec3> kDownFace;

        static const std::vector<u32> kRightFaceIdx;
        static const std::vector<u32> kLeftFaceIdx;
        static const std::vector<u32> kFrontFaceIdx;
        static const std::vector<u32> kBackFaceIdx;
        static const std::vector<u32> kUpFaceIdx;
        static const std::vector<u32> kDownFaceIdx;

        static std::vector<float> StartVertices();
        static std::vector<u32> StartIndices();

public:
        Block(int x, int y, int z, BlockType type);
        Block(glm::ivec3 pos, BlockType type);

        inline const glm::ivec3 &GetPosInChunk() const { return pos_; }

        inline int GetX() const { return pos_.x; };
        inline int GetY() const { return pos_.y; };
        inline int GetZ() const { return pos_.z; };

        inline BlockType GetType() const { return block_type_; }

        inline const std::vector<glm::vec3>& GetRightFaceVertices() const
        { return kRightFace; }

        inline const std::vector<glm::vec3>& GetLeftFaceVertices() const
        { return kLeftFace; }

        inline const std::vector<glm::vec3>& GetFrontFaceVertices() const
        { return kFrontFace; }

        inline const std::vector<glm::vec3>& GetBackFaceVertices() const
        { return kBackFace; }

        inline const std::vector<glm::vec3>& GetUpFaceVertices() const
        { return kUpFace; }

        inline const std::vector<glm::vec3>& GetDownFaceVertices() const
        { return kDownFace; }

        inline const std::vector<u32>& GetRightFaceIndices() const
        { return kRightFaceIdx; }

        inline const std::vector<u32>& GetLeftFaceIndices() const
        { return kLeftFaceIdx; }

        inline const std::vector<u32>& GetFrontFaceIndices() const
        { return kFrontFaceIdx; }

        inline const std::vector<u32>& GetBackFaceIndices() const
        { return kBackFaceIdx; }

        inline const std::vector<u32>& GetUpFaceIndices() const
        { return kUpFaceIdx; }

        inline const std::vector<u32>& GetDownFaceIndices() const
        { return kDownFaceIdx; }

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
