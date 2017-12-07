#ifndef RENDER_HANDLER_HH
#define RENDER_HANDLER_HH

#include "GL/glew.h"
#include "include/cef_render_handler.h"

namespace bl {
	class RenderHandler : public CefRenderHandler {
	public:
		RenderHandler();
		~RenderHandler();
		void resize(
				int w,
				int h
		);
		// CefRenderHandler interface
		virtual bool GetViewRect(
				CefRefPtr<CefBrowser> browser,
				CefRect &rect
		) override;
		virtual void OnPaint(
				CefRefPtr<CefBrowser> browser,
				PaintElementType type,
				const RectList &dirtyRects,
				const void *buffer,
				int width,
				int height
		) override;
		void Render();
		GLuint getTex() const;
		void Initialize();
		void Cleanup();
		void OnPopupShow(
				CefRefPtr<CefBrowser> browser,
				bool show
		);
		void OnPopupSize(
				CefRefPtr<CefBrowser> browser,
				const CefRect &rect
		);
		CefRect GetPopupRectInWebView(const CefRect &original_rect);
		void ClearPopupRects();
		void loadBgTexture();
		void loadBgGridTexture();
	private:
		bool m_showDirtyRect;
		bool m_isTransparent;
		bool m_initialized;
		GLuint m_tex;
		int m_width;
		int m_height;
		CefRect m_popup_rect;
		RectList m_update_rect;
		CefRect m_original_popup_rect;
		float m_spin_x;
		float m_spin_y;
		cef_color_t m_backgroundColor;
		double m_lastTickTime;
		unsigned int m_calls;
		GLuint m_bgTexture;
		GLuint m_bgGrid;
	IMPLEMENT_REFCOUNTING(RenderHandler);
	};
}
#endif // RENDER_HANDLER_HH