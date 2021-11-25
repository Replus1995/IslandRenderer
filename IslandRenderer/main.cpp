#include "../NCLGL/window.h"
#include "Renderer.h"

int main()	{
	Window w("Island Renderer", 1920, 1080, true);

	if(!w.HasInitialised()) {
		return -1;
	}
	
	Renderer renderer(w);
	if(!renderer.HasInitialised()) {
		return -1;
	}

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	while(w.UpdateWindow()  && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		renderer.UpdateScene(w.GetTimer()->GetTimeDeltaSeconds());
		renderer.RenderScene();
		renderer.SwapBuffers();
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F5)) {
			Shader::ReloadAllShaders();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_L)) {
			renderer.ToggleDayLoop();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_O)) {
			renderer.ToggleCameraRoute();
		}
	}
	return 0;
}