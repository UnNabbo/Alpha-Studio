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

#include "Utility/Serialization/Serializer.h"

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

			if (m_IDs.find(res->GetPath()) != m_IDs.end()) {
				return std::static_pointer_cast<T>(m_Resources[m_IDs[res->GetPath()]]);
			}

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

		inline static void Clear() {

		}
		

	private:
		inline static ArenaAllocator m_ArenaAllocator = ArenaAllocator(1024 * 1024);
		inline static std::unordered_map<std::string_view, UUID> m_IDs;
		inline static FileWatcher m_FileWatcher;
		inline static DenseMap<UUID, Reference<Asset>> m_Resources;
	};
}