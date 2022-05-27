#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <wx/wx.h>

namespace rwxet_ui
{
    class Login : public wxPanel
    {
    public:
        Login(wxWindow *parent);
    private:
        wxDECLARE_EVENT_TABLE();
        void OnLogin(wxCommandEvent &event);

        wxTextCtrl *m_server;
        wxTextCtrl *m_username;
        wxTextCtrl *m_password;
    };

    enum {
        ID_LoginBtn = 100
    };
}

#endif