#pragma once

#include "Asset/Resource.h"
#include "Core/Core.h"
#include "Core/UUID.h"
#include "Core/Container/DenseMap.h"

#include "FileWatcher.h"

#include <memory>

namespace Alpha {

	class ResourceManager {
	public:

		template<typename T>
		inline static void Load(Reference<T>& item) {
			auto ID = UUID();
			m_UUIDS[item->GetPath()] = ID;
			Reference<Resource> res = std::static_pointer_cast<Resource>(item);
			m_FileWatcher.Insert(item->GetPath());
			m_Resources.insert_or_do_nothing(ID, res);
		}

		inline static void CheckForUpdates() {
			m_FileWatcher.Check();
		}

		template<typename T>
		inline static Reference<T> Retrive(std::string_view item) {
			if (m_UUIDS.find(item) == m_UUIDS.end()) {
				return nullptr;
			}

			auto ID = m_UUIDS[item];

			return std::static_pointer_cast<T>(m_Resources[ID]);
		}

		inline static void LoadAssetDump() {


		}
		

	private:
		inline static DenseMap<UUID, Reference<Resource>> m_Resources;
		inline static std::unordered_map<std::string_view, UUID> m_UUIDS;
		inline static FileWatcher m_FileWatcher;
	};
}