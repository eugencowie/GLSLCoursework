#include "window.hpp"
#include "util.inl"
#include <glad/glad.h>

Window::Window(const string& title, ivec2 size)
{
	// Initialise SDL
	int sdl = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdl != 0) util::panic("Failed to initialise SDL");

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

	// Create window
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_OPENGL);
	if (!m_window) util::panic("Failed to create SDL window");

	// Create OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(m_window);
	if (!context) util::panic("Failed to create OpenGL context");

	// Load OpenGL functions
	int glad = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	if (!glad) util::panic("Failed to load OpenGL functions");

	// Check for minimum requirements
	if (!GLAD_GL_VERSION_3_3)
		util::panic("Unsupported OpenGL version");
}

Window::~Window()
{
	// Destroy window and shutdown SDL
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::processEvents()
{
	SDL_Event e;

	// Clear events list
	m_events.clear();

	// Poll for window events
	while (SDL_PollEvent(&e))
	{
		// Add event to events list
		m_events.push_back(e);

		if (e.type == SDL_QUIT)
			m_shouldClose = true;
	}
}
