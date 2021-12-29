#include "BARECEGUI.hpp"

// For SDL_GetTicks64()
#include <SDL2/SDL_timer.h>
#include "utf8.h"

#include "Logger.hpp"

namespace BARE2D {

	bool BARECEGUI::m_initialized = false;
	BARECEGUI* BARECEGUI::m_instance = nullptr;
	
	BARECEGUI* BARECEGUI::getInstance() {
		if(!m_instance) {
			m_instance = new BARECEGUI();
		}
		return m_instance;
	}
	
	void BARECEGUI::release() {
		if(m_instance)
			delete m_instance;
	}
	
	BARECEGUI::BARECEGUI() {
		
	}
	
	BARECEGUI::~BARECEGUI() {
		for(CEGUIContextWrapper* e : m_contexts) {
			e->rootWindow->destroy();
			
			delete e;
		}
		m_contexts.clear();
	}
	
	void BARECEGUI::init(std::string& resourceDirectory, unsigned int numContexts) {
		m_contexts.clear(); // Just in case :)
		
		// Create the first context wrapper - we never have less than 1 context.
		CEGUIContextWrapper* primary = new CEGUIContextWrapper;
		
		// Make sure we reuse resources if we can:
		if(m_initialized) {
			// We can reuse the renderer - it has no mutable state.
			primary->renderer = static_cast<CEGUI::OpenGL3Renderer*>(CEGUI::System::getSingleton().getRenderer());
		} else {
			// This is our first time initializing, we need to actually create the renderer.
			primary->renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
			m_initialized = true;
		}
		
		// Now that we have our renderer, we can load all of our resources
		// First, get the resource provider
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		
		// Next, set where CEGUI can actually find each of its specialized types of data.
		rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
		rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");
		
		// Finally, set the labels for the specialized data types.
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
		
		// Now create the context + root window, so we can actually have something to draw/with
		// The actual GUI context
		primary->context = &CEGUI::System::getSingleton().createGUIContext(primary->renderer->getDefaultRenderTarget());
		// The root window (always with a name of root)
		primary->rootWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
		primary->rootWindow->setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
		primary->rootWindow->setPosition(CEGUI::UVector2(cegui_reldim(0.0f), cegui_reldim(0.0f)));
		// Tie it together!
		primary->context->setRootWindow(primary->rootWindow);
		
		// Add the context!
		m_contexts.push_back(primary);
		
		// Create the other contexts and their root windows
		for(unsigned int i = 1; i < numContexts; i++) {
			// As before, use the same renderer if we can (we, indeed, can)
			CEGUI::OpenGL3Renderer* secondaryRenderer = primary->renderer;
			
			// Create a new context, so that we can handle input/output differently from the primary context
			CEGUI::GUIContext* secondaryContext = &CEGUI::System::getSingleton().createGUIContext(secondaryRenderer->getDefaultRenderTarget());
			
			// Create a new root window for this context
			CEGUI::Window* secondaryRootWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "secondary_root_" + std::to_string(i-1));
			secondaryRootWindow->setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
			secondaryRootWindow->setPosition(CEGUI::UVector2(cegui_reldim(0.0f), cegui_reldim(0.0f)));
			
			// Set the (new) context's root
			secondaryContext->setRootWindow(secondaryRootWindow);
			
			// Create a new wrapper and add it to the vector of contexts!
			CEGUIContextWrapper* secondary = new CEGUIContextWrapper;
			secondary->renderer = secondaryRenderer;
			secondary->rootWindow = secondaryRootWindow;
			secondary->context = secondaryContext;
			
			m_contexts.push_back(secondary);
		}
	}

	void BARECEGUI::destroy() {
		for(unsigned int i = 0; i < m_contexts.size(); i++) {
			// Destroy all of the GUI contexts, as well as the root windows for each context.
			CEGUI::System::getSingleton().destroyGUIContext(*m_contexts[i]->context);
			CEGUI::WindowManager::getSingleton().destroyWindow(m_contexts[i]->rootWindow);
		}
		
		// Clear our last little bit of memory.
		m_contexts.clear();
	}

	void BARECEGUI::draw() {
		// To enable semi-transparency within widgets, we must turn off depth-testing.
		glDisable(GL_DEPTH_TEST);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
		glActiveTexture(GL_TEXTURE0);
		
		// First, 'begin' rendering for this current context.
		m_contexts[m_activeContext]->renderer->beginRendering();
		// Actually add the glyphs to whatever data structure
		m_contexts[m_activeContext]->context->draw();
		// Finally, actually draw the stuff
		m_contexts[m_activeContext]->renderer->endRendering();
		
		// Now to clean up after CEGUI.
		// Unbind their vertex array
		glBindVertexArray(0);
		// Disable scissor-testing.
		glDisable(GL_SCISSOR_TEST);
		// Re-enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Unbind whatever texture they've bound
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void BARECEGUI::update() {
		// First of all, find our delta time
		unsigned int elapsed;
		if(m_lastTime == 0) {
			// We are at the verrrrry beginning, so elapsed time is really 0
			elapsed = 0;
			m_lastTime = SDL_GetTicks();
		} else {
			// SDL_GetTicks will wrap over at ~49 days. Not a huge deal and I don't really want to use SDL_GetTicks64
			unsigned int nowTime = SDL_GetTicks();
			elapsed = nowTime - m_lastTime;
			m_lastTime = nowTime;
		}
		
		// Tell CEGUI how much time has passed for updates.
		for(unsigned int i = 0; i < m_contexts.size(); i++) {
			// SDL_GetTicks returns time in milliseconds (seconds * 1e-3) whereas CEGUI takes time pulses in seconds.
			m_contexts[i]->context->injectTimePulse((float)elapsed / 1000.0f);
		}
	}

	void BARECEGUI::setActiveContext(unsigned int contextIndex) {
		if(contextIndex < m_contexts.size()) {
			m_activeContext = contextIndex;
		} else {
			Logger::getInstance()->log("WARNING: Access of CEGUI Context with index " + std::to_string(contextIndex) + " was attempted. This context does not exist.", true);
		}
	}

	void BARECEGUI::setMouseCursor(std::string imageFile) {
		m_contexts[m_activeContext]->context->getMouseCursor().setDefaultImage(imageFile);
	}

	void BARECEGUI::setMouseCursorShown(bool shown) {
		if(shown) {
			m_contexts[m_activeContext]->context->getMouseCursor().show();
		} else {
			m_contexts[m_activeContext]->context->getMouseCursor().hide();
		}
	}

	void BARECEGUI::handleSDLEvent(SDL_Event& evnt) {
		// spark event in each context.
		for(unsigned int i = 0; i < m_contexts.size(); i++) {
			switch(evnt.type) {
				case SDL_MOUSEMOTION:
					// The mouse has moved, so tell CEGUI
					m_contexts[i]->context->injectMousePosition((float)evnt.motion.x, (float)evnt.motion.y);
					break;
				case SDL_KEYDOWN:
					// A key is pressed. Tell CEGUI
					m_contexts[i]->context->injectKeyDown(SDLKeyToCEGUIKey(evnt.key.keysym.sym));
					break;
				case SDL_KEYUP:
					// Conversely, a key has been released. Tell CEGUI
					m_contexts[i]->context->injectKeyUp(SDLKeyToCEGUIKey(evnt.key.keysym.sym));
					break;
				case SDL_MOUSEBUTTONDOWN:
					// A button has been pressed. Convert it to CEGUI enums and inject it
					m_contexts[m_activeContext]->context->injectMouseButtonDown(SDLButtonToCEGUIButton(evnt.button.button));
					break;
				case SDL_MOUSEBUTTONUP:
					// A button has been released. Convert it to CEGUI enums and inject it
					m_contexts[m_activeContext]->context->injectMouseButtonUp(SDLButtonToCEGUIButton(evnt.button.button));
					break;
				case SDL_MOUSEWHEEL:
					// Scrolled! Tell CEGUI
					m_contexts[i]->context->injectMouseWheelChange(evnt.wheel.y);
					break;
					case SDL_TEXTINPUT:
					// SDL Inputs text in UTF8 - CEGUI takes it in UTF32. This is slightly problematic.
					// We will use UTF8 (the library) to convert!
					
					// First, get the text in string form
					std::string evntText = std::string(evnt.text.text);
					// Allocate space for the converted result
					std::vector<int> utf32result;
					// Actually convert it
					utf8::utf8to32(evnt.text.text, evnt.text.text + evntText.size(), std::back_inserter(utf32result));
					// Cast to CEGUI's UTF32 type
					CEGUI::utf32 codePoint = (CEGUI::utf32)utf32result[0];
					
					// Finally, inject the actual UTF32 version of the input.
					m_contexts[i]->context->injectChar(codePoint);
					break;
			}
		}
	}

	void BARECEGUI::loadScheme(std::string schemeFile) {
		// Load a scheme
		CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
	}

	void BARECEGUI::setFont(std::string fontFile) {
		// Create the font
		CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
		// Set the font in each context.
		for(unsigned int i = 0; i < m_contexts.size(); i++) {
			m_contexts[i]->context->setDefaultFont(fontFile);
		}
	}

	CEGUI::Window* BARECEGUI::createWidget(std::string type, glm::vec4 destRectPercent, glm::vec4 destRectPixels, CEGUI::Window* parent, std::string name) {
		// Create the window for the widget
		CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
		// Set its size, position too
		newWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPercent.x, destRectPixels.x), CEGUI::UDim(destRectPercent.y, destRectPixels.y)));
		newWindow->setSize(CEGUI::USize(CEGUI::UDim(destRectPercent.z, destRectPixels.z), CEGUI::UDim(destRectPercent.w, destRectPixels.w)));
		
		// If a parent is given, add it as a child
		if(parent) {
			parent->addChild(newWindow);
		} else {
			// If it's not, add it to the root.
			m_contexts[m_activeContext]->rootWindow->addChild(newWindow);
		}
		
		return newWindow;
	}

	CEGUI::OpenGL3Renderer* BARECEGUI::getRenderer() {
		return m_contexts[m_activeContext]->renderer;
	}
	
	CEGUI::GUIContext* BARECEGUI::getContext() {
		return m_contexts[m_activeContext]->context;
	}
	
	CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode key) {
		using namespace CEGUI;
		switch (key) {
			case SDLK_BACKSPACE:
				return Key::Backspace;
			case SDLK_TAB:
				return Key::Tab;
			case SDLK_RETURN:
				return Key::Return;
			case SDLK_PAUSE:
				return Key::Pause;
			case SDLK_ESCAPE:
				return Key::Escape;
			case SDLK_SPACE:
				return Key::Space;
			case SDLK_COMMA:
				return Key::Comma;
			case SDLK_MINUS:
				return Key::Minus;
			case SDLK_PERIOD:
				return Key::Period;
			case SDLK_SLASH:
				return Key::Slash;
			case SDLK_0:
				return Key::Zero;
			case SDLK_1:
				return Key::One;
			case SDLK_2:
				return Key::Two;
			case SDLK_3:
				return Key::Three;
			case SDLK_4:
				return Key::Four;
			case SDLK_5:
				return Key::Five;
			case SDLK_6:
				return Key::Six;
			case SDLK_7:
				return Key::Seven;
			case SDLK_8:
				return Key::Eight;
			case SDLK_9:
				return Key::Nine;
			case SDLK_COLON:
				return Key::Colon;
			case SDLK_SEMICOLON:
				return Key::Semicolon;
			case SDLK_EQUALS:
				return Key::Equals;
			case SDLK_LEFTBRACKET:
				return Key::LeftBracket;
			case SDLK_BACKSLASH:
				return Key::Backslash;
			case SDLK_RIGHTBRACKET:
				return Key::RightBracket;
			case SDLK_a:
				return Key::A;
			case SDLK_b:
				return Key::B;
			case SDLK_c:
				return Key::C;
			case SDLK_d:
				return Key::D;
			case SDLK_e:
				return Key::E;
			case SDLK_f:
				return Key::F;
			case SDLK_g:
				return Key::G;
			case SDLK_h:
				return Key::H;
			case SDLK_i:
				return Key::I;
			case SDLK_j:
				return Key::J;
			case SDLK_k:
				return Key::K;
			case SDLK_l:
				return Key::L;
			case SDLK_m:
				return Key::M;
			case SDLK_n:
				return Key::N;
			case SDLK_o:
				return Key::O;
			case SDLK_p:
				return Key::P;
			case SDLK_q:
				return Key::Q;
			case SDLK_r:
				return Key::R;
			case SDLK_s:
				return Key::S;
			case SDLK_t:
				return Key::T;
			case SDLK_u:
				return Key::U;
			case SDLK_v:
				return Key::V;
			case SDLK_w:
				return Key::W;
			case SDLK_x:
				return Key::X;
			case SDLK_y:
				return Key::Y;
			case SDLK_z:
				return Key::Z;
			case SDLK_DELETE:
				return Key::Delete;
			case SDLK_KP_PERIOD:
				return Key::Decimal;
			case SDLK_KP_DIVIDE:
				return Key::Divide;
			case SDLK_KP_MULTIPLY:
				return Key::Multiply;
			case SDLK_KP_MINUS:
				return Key::Subtract;
			case SDLK_KP_PLUS:
				return Key::Add;
			case SDLK_KP_ENTER:
				return Key::NumpadEnter;
			case SDLK_KP_EQUALS:
				return Key::NumpadEquals;
			case SDLK_UP:
				return Key::ArrowUp;
			case SDLK_DOWN:
				return Key::ArrowDown;
			case SDLK_RIGHT:
				return Key::ArrowRight;
			case SDLK_LEFT:
				return Key::ArrowLeft;
			case SDLK_INSERT:
				return Key::Insert;
			case SDLK_HOME:
				return Key::Home;
			case SDLK_END:
				return Key::End;
			case SDLK_PAGEUP:
				return Key::PageUp;
			case SDLK_PAGEDOWN:
				return Key::PageDown;
			case SDLK_F1:
				return Key::F1;
			case SDLK_F2:
				return Key::F2;
			case SDLK_F3:
				return Key::F3;
			case SDLK_F4:
				return Key::F4;
			case SDLK_F5:
				return Key::F5;
			case SDLK_F6:
				return Key::F6;
			case SDLK_F7:
				return Key::F7;
			case SDLK_F8:
				return Key::F8;
			case SDLK_F9:
				return Key::F9;
			case SDLK_F10:
				return Key::F10;
			case SDLK_F11:
				return Key::F11;
			case SDLK_F12:
				return Key::F12;
			case SDLK_F13:
				return Key::F13;
			case SDLK_F14:
				return Key::F14;
			case SDLK_F15:
				return Key::F15;
			case SDLK_RSHIFT:
				return Key::RightShift;
			case SDLK_LSHIFT:
				return Key::LeftShift;
			case SDLK_RCTRL:
				return Key::RightControl;
			case SDLK_LCTRL:
				return Key::LeftControl;
			case SDLK_RALT:
				return Key::RightAlt;
			case SDLK_LALT:
				return Key::LeftAlt;
			case SDLK_SYSREQ:
				return Key::SysRq;
			case SDLK_MENU:
				return Key::AppMenu;
			case SDLK_POWER:
				return Key::Power;
			default:
				return Key::Unknown;
		}
	}
	
	CEGUI::MouseButton SDLButtonToCEGUIButton(Uint8 sdlButton) {
		switch (sdlButton) {
			case SDL_BUTTON_LEFT:
				return CEGUI::MouseButton::LeftButton;
			case SDL_BUTTON_MIDDLE:
				return CEGUI::MouseButton::MiddleButton;
			case SDL_BUTTON_RIGHT:
				return CEGUI::MouseButton::RightButton;
			case SDL_BUTTON_X1:
				return CEGUI::MouseButton::X1Button;
			case SDL_BUTTON_X2:
				return CEGUI::MouseButton::X2Button;
		}
		return CEGUI::MouseButton::NoButton;
	}
	
}
