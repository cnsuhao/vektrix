/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009-2010 Fuse-Software (tm)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "Basic.h"
#include "vtxtestsUnitTestHost.h"

#include "vtxFileManager.h"
#include "vtxMovieDebugger.h"
#include "vtxRoot.h"

#include "vtxFontManager.h"

#include "windows.h"

#include <GL/gl.h>

__namespace3(vtx, tests, opengl)
//-----------------------------------------------------------------------
Basic* Basic::thiz = NULL;
//-----------------------------------------------------------------------
Basic::Basic(UnitTestHost* host) 
: UnitTest(host)
{
	thiz = this;
}
//-----------------------------------------------------------------------
Basic::~Basic()
{

}
//-----------------------------------------------------------------------
void Basic::started()
{
	mRoot = new Root;

	LogManager::getSingletonPtr()->logToCout(true);

	// load vektrix plugins
	VTX_LOAD_PLUGIN(vektrix_AS3Plugin);
	VTX_LOAD_PLUGIN(vektrix_CairoPlugin);
	VTX_LOAD_PLUGIN(vektrix_FreeTypePlugin);
	VTX_LOAD_PLUGIN(vektrix_OgrePlugin);
	VTX_LOAD_PLUGIN(vektrix_OpenGLPlugin);
	VTX_LOAD_PLUGIN(vektrix_SwfPlugin);

	FileManager::getSingletonPtr()->addFileContainer(VTX_TEST_MEDIA_PATH(opengl, Basic));
	FileManager::getSingletonPtr()->addFileContainer("C:/Windows/Fonts");

	FontManager::getSingletonPtr()->loadFontFile("times.ttf");
	FontResource* font = FontManager::getSingletonPtr()->getFont("Times New Roman");

	Movie* movie = mRoot->createMovie("swf_movie", "EditText.swf", "OpenGL_Cairo_Movie");
	movie->play();

	HDC hDC;				/* device context */
	HGLRC hRC;				/* opengl context */
	HWND  hWnd;				/* window */
	MSG   msg;				/* message */

	hWnd = (HWND)createOpenGLWindow("OpenGL - Basic Test", 0, 0, 256, 256, PFD_TYPE_RGBA, 0);
	if (hWnd == NULL)
		exit(1);

	hDC = GetDC(hWnd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	ShowWindow(hWnd, SW_SHOW);

	RECT rcClient, rcWindow;
	POINT ptDiff;
	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWindow);
	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
	MoveWindow(hWnd,rcWindow.left, rcWindow.top, 800 + ptDiff.x, 600 + ptDiff.y, TRUE);

	mHost->startOIS((uint)hWnd, 800, 600);

	while(GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(hWnd, hDC);
	wglDeleteContext(hRC);
	DestroyWindow(hWnd);
}
//-----------------------------------------------------------------------
void Basic::stopped()
{
	mHost->stopOIS();
}
//-----------------------------------------------------------------------
void Basic::render()
{
	mRoot->update(0.1f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(0,  1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2i(-1, -1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(1, -1);
	glEnd();
	glFlush();
}
//-----------------------------------------------------------------------
uint Basic::createOpenGLWindow(char* title, int x, int y, int width, int height, uchar type, int flags)
{
	int         pf;
	HDC         hDC;
	HWND        hWnd;
	WNDCLASS    wc;
	PIXELFORMATDESCRIPTOR pfd;
	static HINSTANCE hInstance = 0;

	/* only register the window class once - use hInstance as a flag. */
	if (!hInstance)
	{
		hInstance = GetModuleHandle(NULL);
		wc.style         = CS_OWNDC;
		wc.lpfnWndProc   = (WNDPROC)WindowProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = hInstance;
		wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = "OpenGL";

		if(!RegisterClass(&wc))
		{
			MessageBox(NULL, "RegisterClass() failed:  "
				"Cannot register window class.", "Error", MB_OK);
			return NULL;
		}
	}

	hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, width, height, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL) {
		MessageBox(NULL, "CreateWindow() failed:  Cannot create a window.",
			"Error", MB_OK);
		return NULL;
	}

	hDC = GetDC(hWnd);

	/* there is no guarantee that the contents of the stack that become
	the pfd are zeroed, therefore _make sure_ to clear these bits. */
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize        = sizeof(pfd);
	pfd.nVersion     = 1;
	pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
	pfd.iPixelType   = type;
	pfd.cColorBits   = 32;

	pf = ChoosePixelFormat(hDC, &pfd);
	if (pf == 0) {
		MessageBox(NULL, "ChoosePixelFormat() failed:  "
			"Cannot find a suitable pixel format.", "Error", MB_OK); 
		return 0;
	} 

	if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
		MessageBox(NULL, "SetPixelFormat() failed:  "
			"Cannot set format specified.", "Error", MB_OK);
		return 0;
	} 

	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	ReleaseDC(hWnd, hDC);

	return (uint)hWnd;
}
//-----------------------------------------------------------------------
LONG WINAPI Basic::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
	static PAINTSTRUCT ps;

	switch(uMsg)
	{
	case WM_PAINT:
		thiz->render();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		PostMessage(hWnd, WM_PAINT, 0, 0);
		return 0;

	case WM_CHAR:
		switch (wParam)
		{
		case 27:			/* ESC key */
			PostQuitMessage(0);
			break;
		}
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); 
}
//-----------------------------------------------------------------------
}}}
