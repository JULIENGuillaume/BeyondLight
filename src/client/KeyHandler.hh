//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_KEYHANDLER_HH
#define CEFOFFSCREEN_KEYHANDLER_HH


#include <windows.h>
#include <ime.h>

class KeyHandler {


// Represents a native child window hosting a single off-screen browser
// instance. The methods of this class must be called on the main thread unless
// otherwise indicated.
    /*class BrowserWindowOsrGtk : public BrowserWindow,
                                public ClientHandlerOsr::OsrDelegate {
    public:
        // Constructor may be called on any thread.
        // |delegate| must outlive this object.
        BrowserWindowOsrGtk(BrowserWindow::Delegate* delegate,
                            const std::string& startup_url,
                            const OsrRenderer::Settings& settings);

        // BrowserWindow methods.
        // ClientHandlerOsr::OsrDelegate methods.
        void OnCursorChange(CefRefPtr<CefBrowser> browser,
                            CefCursorHandle cursor,
                            CefRenderHandler::CursorType type,
                            const CefCursorInfo& custom_cursor_info) OVERRIDE;
        bool StartDragging(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefDragData> drag_data,
                           CefRenderHandler::DragOperationsMask allowed_ops,
                           int x, int y) OVERRIDE;
        void UpdateDragCursor(CefRefPtr<CefBrowser> browser,
                              CefRenderHandler::DragOperation operation) OVERRIDE;
        void OnImeCompositionRangeChanged(
                CefRefPtr<CefBrowser> browser,
                const CefRange& selection_range,
                const CefRenderHandler::RectList& character_bounds) OVERRIDE;

    private:
        static gint ClickEvent(GtkWidget* widget,
                               GdkEventButton* event,
                               BrowserWindowOsrGtk* self);
        static gint KeyEvent(GtkWidget* widget,
                             GdkEventKey* event,
                             BrowserWindowOsrGtk* self);
        static gint MoveEvent(GtkWidget* widget,
                              GdkEventMotion* event,
                              BrowserWindowOsrGtk* self);
        static gint ScrollEvent(GtkWidget* widget,
                                GdkEventScroll* event,
                                BrowserWindowOsrGtk* self);
    };*/

 // namespace client

};


#endif //CEFOFFSCREEN_KEYHANDLER_HH
