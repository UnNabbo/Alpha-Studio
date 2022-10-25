#include "ArenaAllocator.h"

#include "Core/Core.h"

namespace Alpha {
    ArenaAllocator::ArenaAllocator(size_t size) : m_MemArenaSize(size) {
        m_MemArena = malloc(size);
    }

    ArenaAllocator::ArenaAllocator(const ArenaAllocator& other) {
        m_MemArenaSize = other.m_MemArenaSize;
        m_MemArena = other.m_MemArena;
        m_MemTop = other.m_MemTop;
    }



    ArenaAllocator::~ArenaAllocator(){
        free(m_MemArena);
    }
}