#ifndef RENDER_HANDLER_HH
#define RENDER_HANDLER_HH

#include "GL/glew.h"
#include "include/cef_render_handler.h"

class RenderHandler : public CefRenderHandler
{
private:
	bool _showDirtyRect;
	bool _isTransparent;
	bool initialized_;
	GLuint _tex;
	int _width;
	int _height;
	CefRect popup_rect_;
    RectList update_rect_;
	CefRect original_popup_rect_;
	float spin_x_;
	float spin_y_;
	cef_color_t _backgroundColor;
	double _lastTickTime;
	unsigned int _calls;
	GLuint _bgTexture;
	GLuint _bgGrid;

public:
	RenderHandler();
	~RenderHandler();

	void resize(int w, int h);

	// CefRenderHandler interface
	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;
	virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) override;
	void Render();

	GLuint getTex() const;
	void Initialize();
	void Cleanup();
	void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show);
	void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect &rect);
	CefRect GetPopupRectInWebView(const CefRect &original_rect);
	void ClearPopupRects();

	void loadBgTexture();
	void loadBgGridTexture();

	// CefBase interface
	IMPLEMENT_REFCOUNTING(RenderHandler);
};

#endif // RENDER_HANDLER_HH