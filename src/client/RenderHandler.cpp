#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "RenderHandler.hh"
#include "../../libs/stb/stb_image.h"


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

RenderHandler::RenderHandler()
        : _showDirtyRect(false),
          _isTransparent(true),
          initialized_(false),
          _tex(0),
          _width(0),
          _height(0),
          spin_x_(0),
          spin_y_(0),
          _backgroundColor(255) {

}

RenderHandler::~RenderHandler() {
    Cleanup();
}

void RenderHandler::Initialize() {
    if (initialized_)
        return;

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    VERIFY_NO_ERROR;

    if (_isTransparent) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        VERIFY_NO_ERROR;
    } else {
        glClearColor(float(CefColorGetR(_backgroundColor)) / 255.0f,
                     float(CefColorGetG(_backgroundColor)) / 255.0f,
                     float(CefColorGetB(_backgroundColor)) / 255.0f,
                     1.0f);
        VERIFY_NO_ERROR;
    }

    // Necessary for non-power-of-2 textures to render correctly.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    VERIFY_NO_ERROR;

    // Create the texture.
    glGenTextures(1, &_tex);
    VERIFY_NO_ERROR;
    DCHECK_NE(_tex, 0U);
    VERIFY_NO_ERROR;

    glBindTexture(GL_TEXTURE_2D, _tex);
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

    initialized_ = true;
    this->_lastTickTime = glfwGetTime();
    this->_calls = 0;
    this->loadBgTexture();
    this->loadBgGridTexture();
}

void RenderHandler::resize(int w, int h)
{
	_width = w;
	_height = h;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
{
	if (this->_isTransparent) {
		// Enable alpha blending.
		glEnable(GL_BLEND);
		VERIFY_NO_ERROR;
	}

	// Enable 2D textures.
	glEnable(GL_TEXTURE_2D);
	VERIFY_NO_ERROR;

	DCHECK_NE(this->_tex, 0U);
	glBindTexture(GL_TEXTURE_2D, this->_tex);
	VERIFY_NO_ERROR;

	if (type == PET_VIEW) {
		int old_width = _width;
		int old_height = _height;

		_width = width;
		_height = height;

		if (_showDirtyRect)
			update_rect_ = dirtyRects;

		glPixelStorei(GL_UNPACK_ROW_LENGTH, _width);
		VERIFY_NO_ERROR;

		if (old_width != _width || old_height != _height ||
			(dirtyRects.size() == 1 &&
			 dirtyRects[0] == CefRect(0, 0, _width, _height))) {
			// Update/resize the whole texture.
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			VERIFY_NO_ERROR;
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
			VERIFY_NO_ERROR;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0,
						 GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, buffer);
			VERIFY_NO_ERROR;
		} else {
			// Update just the dirty rectangles.
			CefRenderHandler::RectList::const_iterator i = dirtyRects.begin();
			for (; i != dirtyRects.end(); ++i) {
				const CefRect& rect = *i;
				DCHECK(rect.x + rect.width <= _width);
				DCHECK(rect.y + rect.height <= _height);
				glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect.x);
				VERIFY_NO_ERROR;
				glPixelStorei(GL_UNPACK_SKIP_ROWS, rect.y);
				VERIFY_NO_ERROR;
				glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width,
								rect.height, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV,
								buffer);
				VERIFY_NO_ERROR;
			}
		}
	} else if (type == PET_POPUP && popup_rect_.width > 0 &&
			   popup_rect_.height > 0) {
		int skip_pixels = 0, x = popup_rect_.x;
		int skip_rows = 0, y = popup_rect_.y;
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
		if (x + w > _width)
			w -= x + w - _width;
		if (y + h > _height)
			h -= y + h - _height;

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

	if (_isTransparent) {
		// Disable alpha blending.
		glDisable(GL_BLEND);
		VERIFY_NO_ERROR;
	}
    const double currentTime = glfwGetTime();
    const double delta = currentTime - this->_lastTickTime;
    ++this->_calls;
    if (delta >= 1.0) {
        /*std::cout << std::to_string(1000.0 / this->_calls) << " CEF ms/frame"
                  << std::endl;*/
        this->_calls = 0;
        this->_lastTickTime += 1.0;
    }
}

void RenderHandler::Render() {
    if (_width == 0 || _height == 0)
        return;

    struct {
        float tu, tv;
        float x, y, z;
    } static vertices[] = {{0.0f, 1.0f, -1.0f, -1.0f, 0.0f},
                           {1.0f, 1.0f, 1.0f, -1.0f, 0.0f},
                           {1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
                           {0.0f, 0.0f, -1.0f, 1.0f, 0.0f}}; // todo improve

    struct {
        float tu, tv;
        float x, y, z;
    } static vertices2[] = {{0.0f, 10.0f, -1.0f, -1.0f, 0.0f},
                           {20.0f, 10.0f, 1.0f, -1.0f, 0.0f},
                           {20.0f, 0.0f, 1.0f, 1.0f, 0.0f},
                           {0.0f, 0.0f, -1.0f, 1.0f, 0.0f}};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    VERIFY_NO_ERROR;

    glMatrixMode(GL_MODELVIEW);
    VERIFY_NO_ERROR;
    glLoadIdentity();
    VERIFY_NO_ERROR;

    // Match GL units to screen coordinates.
    glViewport(0, 0, _width, _height);
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
    glBindTexture(GL_TEXTURE_2D, this->_bgTexture);
    VERIFY_NO_ERROR;
    glInterleavedArrays(GL_T2F_V3F, 0, vertices);
    VERIFY_NO_ERROR;
    glDrawArrays(GL_QUADS, 0, 4);
    VERIFY_NO_ERROR;

    // draw bg grid
    glBindTexture(GL_TEXTURE_2D, this->_bgGrid);
    VERIFY_NO_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    VERIFY_NO_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    VERIFY_NO_ERROR;
    glInterleavedArrays(GL_T2F_V3F, 0, vertices2);
    VERIFY_NO_ERROR;
    glDrawArrays(GL_QUADS, 0, 4);
    VERIFY_NO_ERROR;

    // Draw the facets with the texture.
    DCHECK_NE(_tex, 0U);
    VERIFY_NO_ERROR;
    glBindTexture(GL_TEXTURE_2D, _tex);
    VERIFY_NO_ERROR;
    glInterleavedArrays(GL_T2F_V3F, 0, vertices);
    VERIFY_NO_ERROR;
    glDrawArrays(GL_QUADS, 0, 4);
    VERIFY_NO_ERROR;

    // Disable 2D textures.
    glDisable(GL_TEXTURE_2D);
    VERIFY_NO_ERROR;

    if (_isTransparent) {
        // Disable alpha blending.
        glDisable(GL_BLEND);
        VERIFY_NO_ERROR;
    }

    // Draw a rectangle around the update region.
    if (_showDirtyRect && update_rect_.size() > 0) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        VERIFY_NO_ERROR
        glMatrixMode(GL_PROJECTION);
        VERIFY_NO_ERROR;
        glPushMatrix();
        VERIFY_NO_ERROR;
        glLoadIdentity();
        VERIFY_NO_ERROR;
        glOrtho(0, _width, _height, 0, 0, 1);
        VERIFY_NO_ERROR;

        glLineWidth(1);
        VERIFY_NO_ERROR;
        glColor3f(1.0f, 0.0f, 0.0f);
        VERIFY_NO_ERROR;
        for (int i = 0 ; i < update_rect_.size() ; i++) {
            int left = update_rect_[i].x;
            int right = update_rect_[i].x + update_rect_[i].width;
            int top = update_rect_[i].y;
            int bottom = update_rect_[i].y + update_rect_[i].height;

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

GLuint RenderHandler::getTex() const {
	return (this->_tex);
}

void RenderHandler::Cleanup() {
    if (_tex != 0)
        glDeleteTextures(1, &_tex);
}

void RenderHandler::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) {
    if (!show) {
        // Clear the popup rectangle.
        ClearPopupRects();
    }
}

void RenderHandler::OnPopupSize(CefRefPtr<CefBrowser> browser,
                              const CefRect& rect) {
    if (rect.width <= 0 || rect.height <= 0)
        return;
    original_popup_rect_ = rect;
    popup_rect_ = GetPopupRectInWebView(original_popup_rect_);
}

CefRect RenderHandler::GetPopupRectInWebView(const CefRect& original_rect) {
    CefRect rc(original_rect);
    // if x or y are negative, move them to 0.
    if (rc.x < 0)
        rc.x = 0;
    if (rc.y < 0)
        rc.y = 0;
    // if popup goes outside the view, try to reposition origin
    if (rc.x + rc.width > _width)
        rc.x = _width - rc.width;
    if (rc.y + rc.height > _height)
        rc.y = _height - rc.height;
    // if x or y became negative, move them to 0 again.
    if (rc.x < 0)
        rc.x = 0;
    if (rc.y < 0)
        rc.y = 0;
    return rc;
}

void RenderHandler::ClearPopupRects() {
    popup_rect_.Set(0, 0, 0, 0);
    original_popup_rect_.Set(0, 0, 0, 0);
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
    rect = CefRect(0, 0, this->_width, this->_height);
    return true;
}

void RenderHandler::loadBgTexture() {
    this->_bgTexture = 0;
    glGenTextures(1, &this->_bgTexture);
    glBindTexture(GL_TEXTURE_2D, this->_bgTexture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width;
    int height;
    int nrChannels;
    unsigned char *data = stbi_load("../resources/html/img/bg.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void RenderHandler::loadBgGridTexture() { // todo refactor
    this->_bgGrid = 0;
    glGenTextures(1, &this->_bgGrid);
    glBindTexture(GL_TEXTURE_2D, this->_bgGrid);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // load and generate the texture
    int width;
    int height;
    int nrChannels;
    unsigned char *data = stbi_load("../resources/html/img/gridbg-glow2.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
