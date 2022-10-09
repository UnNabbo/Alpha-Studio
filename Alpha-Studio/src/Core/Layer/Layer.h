#pragma once

#include <string>

namespace Alpha{

	class Event;

	class Layer {
	public:

		Layer(std::string name = "Layer") : m_Name(name) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDeattach() {};

		virtual void OnUpdate() {};
		virtual void OnUIRender() {};
		virtual void OnEvent(Event& e) {};

	private:
		std::string m_Name;
	};
}