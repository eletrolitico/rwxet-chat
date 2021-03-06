#ifndef UI_FRAME_H
#define UI_FRAME_H

#include <wx/wx.h>

#include "ui/login.h"
#include "ui/main.h"

namespace rwxet_ui
{
    class Frame : public wxFrame
    {
    public:
        Frame();

    private:
        void OnHello(wxCommandEvent &event);
        void OnExit(wxCommandEvent &event);
        void OnAbout(wxCommandEvent &event);
        wxDECLARE_EVENT_TABLE();

        Login *login;
        Main *main;
    };

    enum
    {
        ID_Hello = 1
    };
}

#endif