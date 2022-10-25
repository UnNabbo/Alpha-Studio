#include "Alpha_Studio.h"

#include "Rendering/Camera/EditorCamera.h"

#include <iostream>

class AlphaApp : public Alpha::Application {

};

class Game : public Alpha::Layer {
public:
	void OnUpdate() {

	}
};

int main() {
	AlphaApp x;
	x.PushLayer(new Game);
	x.Run();
}