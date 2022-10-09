#include "LayerStack.h"

#include <algorithm>

namespace Alpha {
	LayerStack::LayerStack(){

	}

	LayerStack::~LayerStack(){
		for (auto layer : m_LayerStackData) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_LayerStackData.emplace(begin() + m_LayerIndex++, layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer){
		auto LayerIndex = std::find(begin(), end(), layer);
		if (LayerIndex != end() ) {
			m_LayerStackData.erase(LayerIndex);
			m_LayerIndex--;
		}
		layer->OnDeattach();
	}
	void LayerStack::PushOverlay(Layer* layer){
		m_LayerStackData.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* layer){
		auto LayerIndex = std::find(begin(), end(), layer);
		if (LayerIndex != end()) {
			m_LayerStackData.erase(LayerIndex);
		}
		layer->OnAttach();
	}
}