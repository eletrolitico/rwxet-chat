#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <wx/wx.h>

namespace rwxet_ui
{
    class Login : public wxPanel
    {
    public:
        explicit Login(wxWindow *parent);

    private:
        void OnLogin(wxCommandEvent &event);

        wxTextCtrl *m_server;
        wxTextCtrl *m_username;
        wxTextCtrl *m_password;

        wxDECLARE_EVENT_TABLE();
    };

    enum
    {
        ID_LoginBtn = 100
    };
}

#endif