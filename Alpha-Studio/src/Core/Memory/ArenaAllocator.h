#pragma once

#include <memory>

namespace Alpha {
	class ArenaAllocator {
	public:
		ArenaAllocator(size_t size = 8);
		ArenaAllocator(const ArenaAllocator& other);

		~ArenaAllocator();
		
		inline void* GetMemArena() { return m_MemArena; }
		inline size_t& GetMemSize() { return m_MemArenaSize; }
		inline size_t& GetMemTop() { return m_MemTop; }

		template<typename type, typename... Args>
		type* Allocate(Args... args) {
			type* ptr = new (((char*)m_MemArena) + m_MemTop) type(args...);
			m_MemTop += sizeof(type);
			if (m_MemArenaSize <= m_MemTop) {
				m_MemArenaSize = m_MemArenaSize + m_MemArenaSize / 2;
				realloc(m_MemArena, m_MemArenaSize);
			}
			return ptr;
		}


		template<typename type, ArenaAllocator& alloc>
		struct SmartDeleter {
			void operator ()(type const* ptr)
			{
				memset((void*)ptr, 0, sizeof(type));
				size_t offset = (char*)ptr - (char*)alloc.GetMemArena();
				memmove((void*)((char*)ptr - offset), (void *)ptr, alloc.GetMemSize() - offset);
				alloc.GetMemTop() -= sizeof(type);
			}
		};

	private:
		void * m_MemArena;
		size_t m_MemArenaSize;
		size_t m_MemTop = 0;
	};
}