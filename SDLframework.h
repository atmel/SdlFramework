#ifndef __TINY_SDL__
#define __TINY_SDL__
/*
Contains simple SDL framework meant for OpenGL development.

NOTE: YOU MUST ADD MODULES/cpp/SDLframework.cpp TO YOUR SOURCE FILES!
*/
#include <SDL.h>
#include <stack>
#include <string>

//often used:
#include <glew.h>
#include <SDL_opengl.h>
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"glew32s.lib")
#pragma comment (lib,"sdl.lib")
#pragma comment (lib,"sdlmain.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")


//class prototypes
class SDLFramework;						//manages it's window
class SDLFrInterface;					//user defines class derivated from this one
class _FrError;							//internal use, error handling
struct GLParam;							//for passing GL parameters to Init function

class _FrError{
public:
	std::string str;
	int type;

	_FrError(){str.clear();}
	~_FrError(){}
};

class SDLFramework {					// *0)
	static bool frCreated;
	SDL_Surface *window;
	unsigned int width, height;
	SDLFrInterface *interface;
	std::stack<_FrError> errors;

public:
	SDLFramework(){}
	~SDLFramework(){SDL_Quit();}

	int Init(											//initialize whole framework, fail if the second framework instance calls Init						
		SDLFrInterface *inter,								//pointer to user-defined interface
		int _width,											//in pixels
		int _height,										//in pixels
		int bitsPP,											//bits per pixel, see *0a)
		Uint32 SdlFlags,									//flags for SDL_SetVideoMode, see *0a) (SDL_ -FULLSCREEN, -NOFRAME) 
		Uint32 initSystems,									//which SDL subsystems should be initialized
		GLParam *glPar,										//pointer to structure containing additional OpenGl parameters
		const char* title,									//title of the window
		const char* minTitle								//title of the window if minimized
						   );								//all passed arguments should be valid and verified before Init is called
	void RunLoop();

	friend bool SetError(const	char *str, int type);		// *3)
	friend int GetLastError(char *out, int size);			// *3a)
};

class SDLFrInterface{										//user's interface may or may not support some of these functions
public:
	SDLFrInterface(){}
	~SDLFrInterface(){}
	virtual void KeyboardEvent(SDL_Event *event){;}
	virtual void MouseEvent(SDL_Event *event){;}
	virtual void WindowEvent(SDL_Event *event){;}
	virtual void OtherEvent(SDL_Event *event){;}
	virtual bool QuitEvent(){return false;}					//framework will exit, if 'false' is returned - suitable for prompt exit...
	virtual Uint32 TimeEvent(signed int timeBalance = 0){return 10;}// *1)
};

struct GLParam{												//see *4)
	int redSize,
		greenSize,
		blueSize,
		alphaSize,
		bufferSize,
		doubleBuffer,
		depthSize,											//on windows, setting stencil size has no effect
		accRedSize,
		accGreenSize,
		accBlueSize,
		accAlphaSize,
		hwAcceleration;										// 1 by default
};
#endif