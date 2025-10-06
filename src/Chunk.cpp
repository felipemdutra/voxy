#include "Chunk.h"
#include "Block.h"
#include "block_type.h"
#include <cassert>
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include <wrapgl/renderer.h>

using std::vector;
using namespace glm;

void Chunk::AddFace(
                Block *block,
                const std::vector<glm::vec3> &face_vertices,
                const std::vector<u32> &face_indices,
                std::vector<u32> &index_out,
                std::vector<float> &vertex_out
                )
{
        for (auto &vert : face_vertices) {
                glm::vec3 final_pos = vert + glm::vec3(block->GetX(), block->GetY(), block->GetZ());
                vertex_out.push_back(final_pos.x);
                vertex_out.push_back(final_pos.y);
                vertex_out.push_back(final_pos.z);

                // Color vertices 
                vertex_out.push_back(0.2f);
                vertex_out.push_back(1.0f);
                vertex_out.push_back(0.3f);
        }

        for (auto &idx : face_indices) {
                size_t vert_offset = vertex_out.size() / 6;
                index_out.push_back(idx + vert_offset);
        }
}

bool Chunk::HasNeighbor(Block *block, Direction dir)
{
        static ivec3 right = {1, 0, 0};
        static ivec3 left  = {-1, 0, 0};
        static ivec3 front = {0, 0, -1};
        static ivec3 back  = {0, 0, 1};
        static ivec3 up    = {0, 1, 0};
        static ivec3 down  = {0, -1, 0};

        ivec3 rpos = block->GetPosInChunk() + right;
        ivec3 lpos = block->GetPosInChunk() + left;
        ivec3 fpos = block->GetPosInChunk() + front;
        ivec3 bpos = block->GetPosInChunk() + back;
        ivec3 upos = block->GetPosInChunk() + up;
        ivec3 dpos = block->GetPosInChunk() + down;

        switch (dir) {
                case kRight:
                        return GetBlockAt(rpos) == nullptr ? false : true;
                case kLeft:
                        return GetBlockAt(lpos) == nullptr ? false : true;
                case kFront:
                        return GetBlockAt(fpos) == nullptr ? false : true;
                case kBack:
                        return GetBlockAt(bpos) == nullptr ? false : true;
                case kUp:
                        return GetBlockAt(upos) == nullptr ? false : true;
                case kDown:
                        return GetBlockAt(dpos) == nullptr ? false : true;
                default:
                        return false;
        }
}

void Chunk::InitializeChunk()
{
        for (int x = 0; x < kChunkSize; ++x) {
                for (int y = 0; y < kChunkSize; ++y) {
                        for (int z = 0; z < kChunkSize; ++z) {
                                blocks[x][y][z] = new Block(x, y, z, kGrassBlock); 
                        }
                }
        }

        UpdateVertexData();
}

void Chunk::DestroyChunk()
{
        for (int x = 0; x < kChunkSize; ++x) {
                for (int y = 0; y < kChunkSize; ++y) {
                        for (int z = 0; z < kChunkSize; ++z) {
                                delete blocks[x][y][z];
                        }
                }
        }
}

Block *Chunk::GetBlockAt(const glm::ivec3 &pos)
{
        if (pos.x >= 16 || pos.x < 0 ||
            pos.y >= 16 || pos.y < 0 ||
            pos.z >= 16 || pos.z < 0) {
                return nullptr;
        }

        Block *block = blocks[pos.x][pos.y][pos.z];
        if (block->GetType() == kAirBlock) {
                return nullptr;
        }

        return block;
}

Block *Chunk::GetBlockAt(int x, int y, int z) {
        return GetBlockAt(glm::ivec3(x, y, z));
}

Chunk::Chunk()
{
        InitializeChunk();
}

Chunk::~Chunk() {
        DestroyChunk();
}

void Chunk::UpdateVertexData()
{
        if (!dirty_) {
                return;
        }

        vector<float> chunk_vertices;

        // This isn't enough, but it's best to reallocate later then to waste memory.
        chunk_vertices.reserve(16*16*16);

        vector<u32> chunk_indices;
        chunk_indices.reserve(16*16*16);

        for (int x = 0; x < kChunkSize; ++x) {
                for (int y = 0; y < kChunkSize; ++y) {
                        for (int z = 0; z < kChunkSize; ++z) {
                                Block *block = GetBlockAt(x, y, z);
                                if (!block) {
                                        continue;
                                }

                                // Only send the vertex data of the faces that
                                // are visible (faces that aren't facing other
                                // faces).
                                if (!HasNeighbor(block, kRight)) {
                                        AddFace(block, block->GetRightFaceVertices(), block->GetRightFaceIndices(), chunk_indices, chunk_vertices);
                                }

                                if (!HasNeighbor(block, kLeft)) {
                                        AddFace(block, block->GetLeftFaceVertices(), block->GetLeftFaceIndices(), chunk_indices, chunk_vertices);
                                }

                                if (!HasNeighbor(block, kFront)) {
                                        AddFace(block, block->GetFrontFaceVertices(), block->GetFrontFaceIndices(), chunk_indices, chunk_vertices);
                                }

                                if (!HasNeighbor(block, kBack)) {
                                        AddFace(block, block->GetBackFaceVertices(), block->GetBackFaceIndices(), chunk_indices, chunk_vertices);
                                }

                                if (!HasNeighbor(block, kUp)) {
                                        AddFace(block, block->GetUpFaceVertices(), block->GetUpFaceIndices(), chunk_indices, chunk_vertices);
                                }

                                if (!HasNeighbor(block, kDown)) {
                                        AddFace(block, block->GetDownFaceVertices(), block->GetDownFaceIndices(), chunk_indices, chunk_vertices);
                                }
                        }
                }
        }

        index_count_ = chunk_indices.size();
        assert(index_count_ != 0);

        assert(glGetError() == GL_NO_ERROR);

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * chunk_vertices.size(), chunk_vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * chunk_indices.size(), chunk_indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // positions
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color
        glEnableVertexAttribArray(1);


        assert(glGetError() == GL_NO_ERROR);
        dirty_ = false;
}

void Chunk::Render(wgl::Renderer &renderer)
{
        UpdateVertexData();
        renderer.SetUniformMatrix4f("model", glm::mat4(1.0f));
        renderer.Draw(vao_, index_count_);
}

