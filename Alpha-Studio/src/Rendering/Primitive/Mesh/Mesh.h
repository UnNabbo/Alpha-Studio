#pragma once

#include "Core/Core.h"

#include "Asset/Asset.h"

#include "glm/glm.hpp"

namespace Alpha {

	class Mesh3D : public Asset {
	public:
		Mesh3D();
		~Mesh3D();
		
		

		virtual void Reload() override;

		static Reference<Mesh3D> Load(std::string_view path);
	private:

	};
}