#pragma once

#include <string>

#include "Utility/Serialization/Serializer.h"

#define SERIALIZE_ASSET_FN(x) \
\
		virtual void Serialize(Serializer::InputArchive<Serializer::BinaryData> arr) { x(arr) }\
		virtual void Serialize(Serializer::OutputArchive<Serializer::BinaryData> arr) { x(arr) }\
\

#define SERIALIZE_ASSET_FN() \
\
		virtual void Serialize(Serializer::InputArchive<Serializer::BinaryData>) { }\
		virtual void Serialize(Serializer::OutputArchive<Serializer::BinaryData>) { }\
\

namespace Alpha {
	class Asset {
	public:
		std::string& GetPath() { return m_path; }
		virtual void Reload() {};

		SERIALIZE_ASSET_FN()
	protected:
		void SetPath(std::string path) { m_path = path; }
		void SetPath(std::string_view path) { m_path = std::string(path); }
	private:
		std::string m_path = "";
	};
}

