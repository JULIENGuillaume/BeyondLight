#ifndef RENDER_HANDLER_HH
#define RENDER_HANDLER_HH

#include "GL/glew.h"
#include "include/cef_render_handler.h"

class RenderHandler : public CefRenderHandler
{
private:
	int _width;
	int _height;
	GLuint _tex;

public:
	RenderHandler();

	void init();
	void resize(int w, int h);

	// CefRenderHandler interface
	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
	virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override;

	GLuint getTex() const;

	// CefBase interface
	IMPLEMENT_REFCOUNTING(RenderHandler);
};

#endif // RENDER_HANDLER_HH