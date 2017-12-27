﻿#include <iostream>
#include "RenderHandler.hh"
#include "ImageLoader.hh"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif
#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif
#ifndef GL_UNSIGNED_INT_8_8_8_8_REV
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#endif

// DCHECK on gl errors.
#if DCHECK_IS_ON()
#define VERIFY_NO_ERROR                                                      \
  {                                                                          \
	int _gl_error = glGetError();                                            \
	DCHECK(_gl_error == GL_NO_ERROR) << "glGetError returned " << _gl_error; \
  }
#else
#define VERIFY_NO_ERROR
#endif
namespace bl {
	const RenderHandler::s_texture_vertices RenderHandler::m_bgVertices[] = {{0.0f, 1.0f, -1.0f, -1.0f, 0.0f},
																			 {1.0f, 1.0f, 1.0f,  -1.0f, 0.0f},
																			 {1.0f, 0.0f, 1.0f,  1.0f,  0.0f},
																			 {0.0f, 0.0f, -1.0f, 1.0f,  0.0f}};
	const RenderHandler::s_texture_vertices RenderHandler::m_bgGridVertices[] = {{0.0f,  10.0f, -1.0f, -1.0f, 0.0f},
																				 {20.0f, 10.0f, 1.0f,  -1.0f, 0.0f},
																				 {20.0f, 0.0f,  1.0f,  1.0f,  0.0f},
																				 {0.0f,  0.0f,  -1.0f, 1.0f,  0.0f}};

	RenderHandler::RenderHandler()
			:
			m_showDirtyRect(false),
			m_isTransparent(true),
			m_initialized(false),
			m_tex(0),
			m_width(0),
			m_height(0),
			m_spin_x(0),
			m_spin_y(0),
			m_backgroundColor(255) {
		if (m_initialized) {
			return;
		}
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		VERIFY_NO_ERROR;
		if (m_isTransparent) {
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			VERIFY_NO_ERROR;
		} else {
			glClearColor(float(CefColorGetR(m_backgroundColor)) / 255.0f,
						 float(CefColorGetG(m_backgroundColor)) / 255.0f,
						 float(CefColorGetB(m_backgroundColor)) / 255.0f,
						 1.0f);
			VERIFY_NO_ERROR;
		}

		// Necessary for non-power-of-2 textures to render correctly.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		VERIFY_NO_ERROR;

		// Create the texture.
		glGenTextures(1, &m_tex);
		VERIFY_NO_ERROR;
		DCHECK_NE(m_tex, 0U);
		VERIFY_NO_ERROR;
		glBindTexture(GL_TEXTURE_2D, m_tex);
		VERIFY_NO_ERROR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		VERIFY_NO_ERROR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		VERIFY_NO_ERROR;
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		VERIFY_NO_ERROR;

		// initial GL state
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		m_initialized = true;
		this->m_lastTickTime = glfwGetTime();
		this->m_calls = 0;
		this->loadBgTexture();
		this->loadBgGridTexture();
	}

	RenderHandler::~RenderHandler() {
		if (m_tex != 0) {
			glDeleteTextures(1, &m_tex);
		}
		if (m_bgTexture != 0) {
			glDeleteTextures(1, &m_bgTexture);
		}
		if (m_bgGrid != 0) {
			glDeleteTextures(1, &m_bgGrid);
		}
	}

	void RenderHandler::resize(
			int w,
			int h
	) {
		m_width = w;
		m_height = h;
	}

	void
	RenderHandler::OnPaint(
			CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList &dirtyRects,
			const void *buffer,
			int width,
			int height
	) {
		if (this->m_isTransparent) {
			// Enable alpha blending.
			glEnable(GL_BLEND);
			VERIFY_NO_ERROR;
		}

		// Enable 2D textures.
		glEnable(GL_TEXTURE_2D);
		VERIFY_NO_ERROR;
		DCHECK_NE(this->m_tex, 0U);
		glBindTexture(GL_TEXTURE_2D, this->m_tex);
		VERIFY_NO_ERROR;
		if (type == PET_VIEW) {
			int old_width = m_width;
			int old_height = m_height;
			m_width = width;
			m_height = height;
			if (m_showDirtyRect) {
				m_update_rect = dirtyRects;
			}
			glPixelStorei(GL_UNPACK_ROW_LENGTH, m_width);
			VERIFY_NO_ERROR;
			if (old_width != m_width || old_height != m_height ||
					(dirtyRects.size() == 1 &&
							dirtyRects[0] == CefRect(0, 0, m_width, m_height))) {
				// Update/resize the whole texture.
				glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
				VERIFY_NO_ERROR;
				glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
				VERIFY_NO_ERROR;
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
							 GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, buffer);
				VERIFY_NO_ERROR;
			} else {
				// Update just the dirty rectangles.
				CefRenderHandler::RectList::const_iterator i = dirtyRects.begin();
				for (; i != dirtyRects.end();
					   ++i) {
					const CefRect &rect = *i;
					DCHECK(rect.x + rect.width <= m_width);
					DCHECK(rect.y + rect.height <= m_height);
					glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect.x);
					VERIFY_NO_ERROR;
					glPixelStorei(GL_UNPACK_SKIP_ROWS, rect.y);
					VERIFY_NO_ERROR;
					glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y,
									rect.width,
									rect.height, GL_BGRA,
									GL_UNSIGNED_INT_8_8_8_8_REV,
									buffer);
					VERIFY_NO_ERROR;
				}
			}
		} else if (type == PET_POPUP && m_popup_rect.width > 0 &&
				m_popup_rect.height > 0) {
			int skip_pixels = 0, x = m_popup_rect.x;
			int skip_rows = 0, y = m_popup_rect.y;
			int w = width;
			int h = height;

			// Adjust the popup to fit inside the view.
			if (x < 0) {
				skip_pixels = -x;
				x = 0;
			}
			if (y < 0) {
				skip_rows = -y;
				y = 0;
			}
			if (x + w > m_width) {
				w -= x + w - m_width;
			}
			if (y + h > m_height) {
				h -= y + h - m_height;
			}

			// Update the popup rectangle.
			glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
			VERIFY_NO_ERROR;
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, skip_pixels);
			VERIFY_NO_ERROR;
			glPixelStorei(GL_UNPACK_SKIP_ROWS, skip_rows);
			VERIFY_NO_ERROR;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_BGRA,
							GL_UNSIGNED_INT_8_8_8_8_REV, buffer);
			VERIFY_NO_ERROR;
		}

		// Disable 2D textures.
		glDisable(GL_TEXTURE_2D);
		VERIFY_NO_ERROR;
		if (m_isTransparent) {
			// Disable alpha blending.
			glDisable(GL_BLEND);
			VERIFY_NO_ERROR;
		}
		const double currentTime = glfwGetTime();
		const double delta = currentTime - this->m_lastTickTime;
		++this->m_calls;
		if (delta >= 1.0) {
			this->m_avgFrameCallTime = 1000.0 / this->m_calls;
			this->m_calls = 0;
			this->m_lastTickTime += 1.0;
		}
	}

	void RenderHandler::Render() {
		if (m_width == 0 || m_height == 0) {
			return;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		VERIFY_NO_ERROR;
		glMatrixMode(GL_MODELVIEW);
		VERIFY_NO_ERROR;
		glLoadIdentity();
		VERIFY_NO_ERROR;

		// Match GL units to screen coordinates.
		glViewport(0, 0, m_width, m_height);
		VERIFY_NO_ERROR;
		glMatrixMode(GL_PROJECTION);
		VERIFY_NO_ERROR;
		glLoadIdentity();
		VERIFY_NO_ERROR;

		// Draw the background gradient.
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		VERIFY_NO_ERROR;
		// Don't check for errors until glEnd().
		glBegin(GL_QUADS);
		glColor4f(1.0, 0.0, 0.0, 1.0);  // red
		glVertex2f(-1.0, -1.0);
		glVertex2f(1.0, -1.0);
		glColor4f(0.0, 0.0, 1.0, 1.0);  // blue
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);
		glEnd();
		VERIFY_NO_ERROR;
		glPopAttrib();
		VERIFY_NO_ERROR;
		if (true /*IsTransparent()*/) {
			// Alpha blending style. Texture values have premultiplied alpha.
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			VERIFY_NO_ERROR;

			// Enable alpha blending.
			glEnable(GL_BLEND);
			VERIFY_NO_ERROR;
		}

		// Enable 2D textures.
		glEnable(GL_TEXTURE_2D);
		VERIFY_NO_ERROR;

		// draw bg
		glBindTexture(GL_TEXTURE_2D, this->m_bgTexture);
		VERIFY_NO_ERROR;
		glInterleavedArrays(GL_T2F_V3F, 0, RenderHandler::m_bgVertices);
		VERIFY_NO_ERROR;
		glDrawArrays(GL_QUADS, 0, 4);
		VERIFY_NO_ERROR;

		// draw bg grid
		glBindTexture(GL_TEXTURE_2D, this->m_bgGrid);
		VERIFY_NO_ERROR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		VERIFY_NO_ERROR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		VERIFY_NO_ERROR;
		glInterleavedArrays(GL_T2F_V3F, 0, RenderHandler::m_bgGridVertices);
		VERIFY_NO_ERROR;
		glDrawArrays(GL_QUADS, 0, 4);
		VERIFY_NO_ERROR;

		// Draw the facets with the texture.
		DCHECK_NE(m_tex, 0U);
		VERIFY_NO_ERROR;
		glBindTexture(GL_TEXTURE_2D, m_tex);
		VERIFY_NO_ERROR;
		glInterleavedArrays(GL_T2F_V3F, 0, RenderHandler::m_bgVertices);
		VERIFY_NO_ERROR;
		glDrawArrays(GL_QUADS, 0, 4);
		VERIFY_NO_ERROR;

		// Disable 2D textures.
		glDisable(GL_TEXTURE_2D);
		VERIFY_NO_ERROR;
		if (m_isTransparent) {
			// Disable alpha blending.
			glDisable(GL_BLEND);
			VERIFY_NO_ERROR;
		}

		// Draw a rectangle around the update region.
		if (m_showDirtyRect && m_update_rect.size() > 0) {
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			VERIFY_NO_ERROR
			glMatrixMode(GL_PROJECTION);
			VERIFY_NO_ERROR;
			glPushMatrix();
			VERIFY_NO_ERROR;
			glLoadIdentity();
			VERIFY_NO_ERROR;
			glOrtho(0, m_width, m_height, 0, 0, 1);
			VERIFY_NO_ERROR;
			glLineWidth(1);
			VERIFY_NO_ERROR;
			glColor3f(1.0f, 0.0f, 0.0f);
			VERIFY_NO_ERROR;
			for (unsigned int i = 0;
				 i < m_update_rect.size();
				 i++) {
				int left = m_update_rect[i].x;
				int right = m_update_rect[i].x + m_update_rect[i].width;
				int top = m_update_rect[i].y;
				int bottom = m_update_rect[i].y + m_update_rect[i].height;
				#if defined(OS_LINUX)
				// Shrink the box so that top & right sides are drawn.
			top += 1;
			right -= 1;
				#else
				// Shrink the box so that left & bottom sides are drawn.
				left += 1;
				bottom -= 1;
				#endif
				// Don't check for errors until glEnd().
				glBegin(GL_LINE_STRIP);
				glVertex2i(left, top);
				glVertex2i(right, top);
				glVertex2i(right, bottom);
				glVertex2i(left, bottom);
				glVertex2i(left, top);
			}
			glEnd();
			VERIFY_NO_ERROR;
			glPopMatrix();
			VERIFY_NO_ERROR;
			glPopAttrib();
			VERIFY_NO_ERROR;
		}
	}

	void RenderHandler::OnPopupShow(
			CefRefPtr<CefBrowser> browser,
			bool show
	) {
		if (!show) {
			// Clear the popup rectangle.
			ClearPopupRects();
		}
	}

	void RenderHandler::OnPopupSize(
			CefRefPtr<CefBrowser> browser,
			const CefRect &rect
	) {
		if (rect.width <= 0 || rect.height <= 0) {
			return;
		}
		m_original_popup_rect = rect;
		m_popup_rect = GetPopupRectInWebView(m_original_popup_rect);
	}

	CefRect RenderHandler::GetPopupRectInWebView(const CefRect &original_rect) {
		CefRect rc(original_rect);
		// if x or y are negative, move them to 0.
		if (rc.x < 0) {
			rc.x = 0;
		}
		if (rc.y < 0) {
			rc.y = 0;
		}
		// if popup goes outside the view, try to reposition origin
		if (rc.x + rc.width > m_width) {
			rc.x = m_width - rc.width;
		}
		if (rc.y + rc.height > m_height) {
			rc.y = m_height - rc.height;
		}
		// if x or y became negative, move them to 0 again.
		if (rc.x < 0) {
			rc.x = 0;
		}
		if (rc.y < 0) {
			rc.y = 0;
		}
		return rc;
	}

	void RenderHandler::ClearPopupRects() {
		m_popup_rect.Set(0, 0, 0, 0);
		m_original_popup_rect.Set(0, 0, 0, 0);
	}

	bool
	RenderHandler::GetViewRect(
			CefRefPtr<CefBrowser> browser,
			CefRect &rect
	) {
		rect = CefRect(0, 0, this->m_width, this->m_height);
		return true;
	}

	void RenderHandler::loadBgTexture() {
		ImageLoader::loadTexture(this->m_bgTexture, "../resources/html/img/bg.jpg", false);
	}

	void RenderHandler::loadBgGridTexture() {
		ImageLoader::loadTexture(this->m_bgGrid, "../resources/html/img/gridbg-glow2.png", true);
	}

	double RenderHandler::getAverageFrameCallTime() const {
		return (this->m_avgFrameCallTime);
	}
}