#include <Editor.hpp>

#include <Junia/Core/Exception.hpp>
#include <Junia/Junia.hpp>
#include <Junia/Rendering/Window.hpp>

#include <Junia/Rendering/Monitor.hpp>
#include <iostream>

static void StartEditor();

int main() {
	try {
		Junia::Init();
		StartEditor();
		Junia::Terminate();
	} catch (const Junia::Exception& ex) {
		std::cout << ex.GetText(true);
		std::cout.flush();
	}
	return 0;
}

static void StartEditor() {
	auto& monitors = Junia::Monitor::GetMonitors();
	for (int i = 0; i < monitors.size(); i++)
		std::cout << monitors[i].GetIndex() << ": " << monitors[i].GetName() << std::endl;

	Junia::Window oglWindow = Junia::Window(u8"Junia Editor OpenGL", Junia::RenderAPI::OPENGL);
	Junia::Window vkWindow  = Junia::Window(u8"Junia Editor Vulkan", Junia::RenderAPI::VULKAN);
	oglWindow.Show();
	vkWindow.Show();

	oglWindow.SetFullscreenMode(Junia::Window::FullscreenMode::FULLSCREEN);

	std::cout << "Dimensions:"
			  << "\n\twidth:  " << oglWindow.GetSize().x
			  << "\n\theight: " << oglWindow.GetSize().y
			  << "\nPosition:"
			  << "\n\tx: " << oglWindow.GetPosition().x
			  << "\n\ty: " << oglWindow.GetPosition().y
			  << std::endl;

	while (oglWindow.IsShown() && vkWindow.IsShown()) {
		oglWindow.HandleEvents();
		vkWindow.HandleEvents();
	}
}
