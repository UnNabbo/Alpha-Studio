#pragma once

#include "LayerStack.h"
#include "Layer.h"


#include <vector>

namespace Alpha {
	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);


		inline std::vector<Layer*>::iterator begin() { return m_LayerStackData.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_LayerStackData.end(); }

	private:
		std::vector<Layer*> m_LayerStackData;
		uint32_t m_LayerIndex = 0;
	};
}