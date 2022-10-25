#pragma once

#include "Asset/Asset.h"
#include "Core/Core.h"
#include "Core/UUID.h"
#include "Core/Container/DenseMap.h"
#include "Core/Memory/ArenaAllocator.h"
#include "FileWatcher.h"
#include <memory>
#include "Rendering/Primitive/Mesh/Mesh.h"
#include <fstream>

#define ASSET_DUMP_PATH "D:/DEV/Alpha Studio/Alpha-Studio/asset/AssetDump"

namespace Alpha {
	class AssetManager {
	public:
		template<typename T, typename... Args>
		inline static Reference<T> CreateAsset(Args... args) {
			Reference<T> ptr = Reference<T>(m_ArenaAllocator.Allocate<T>(args...), ArenaAllocator::SmartDeleter<T, m_ArenaAllocator>());
			return Load<T>(ptr);
		}

		template<typename T>
		inline static Reference<T> Load(Reference<T> item) {
			auto ID = UUID();
			Reference<Asset> res = std::static_pointer_cast<Asset>(item);
			m_IDs[res->GetPath()] = ID;
			m_FileWatcher.Insert(res->GetPath());
			m_Resources.insert_or_do_nothing(ID, res);
			return item;
		}

		inline static void CheckForUpdates() {
			m_FileWatcher.Check();
		}

		template<typename T>
		inline static Reference<T> Retrive(std::string_view item) {
			if (m_IDs.find(item) == m_IDs.end()) {
				return nullptr;
			}

			auto ID = m_IDs[item];

			return std::static_pointer_cast<T>(m_Resources[ID]);
		}

#if 0
		inline static void LoadAssetDump() {
			std::fstream file(ASSET_DUMP_PATH, std::ios::in | std::ios::binary);
			if (file.is_open()) {
				std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
				if (!buffer.empty()) {
					size_t buffer_top = 0;
					m_ArenaAllocator.LoadDump(buffer.data());
					void* buffer_data = m_ArenaAllocator.GetMemArena();
					size_t buffer_size = *((size_t*)buffer_data);
					buffer_top += sizeof(size_t);
					while (buffer_top < buffer_size) {
						size_t size = *((size_t*)((char*)buffer_data + buffer_top));
						buffer_top += sizeof(size_t);
						auto ptr = new ((char*)buffer_data + buffer_top) Asset;
						Load<Asset>(Reference<Asset>(ptr));
						buffer_top += size;
					}
				}
			}
		}

		inline static void DumpAsset() {
			std::fstream file(ASSET_DUMP_PATH, std::ios::out | std::ios::binary);
			if (file.is_open()) {
				file.write(reinterpret_cast<char const*>(m_ArenaAllocator.GetMemArena()), m_ArenaAllocator.GetMemTop());
			}
		}
#endif

		inline static void Clear() {

		}
		

	private:
		inline static ArenaAllocator m_ArenaAllocator = ArenaAllocator(1024 * 1024);
		inline static std::unordered_map<std::string_view, UUID> m_IDs;
		inline static FileWatcher m_FileWatcher;
		inline static DenseMap<UUID, Reference<Asset>> m_Resources;
	};
}