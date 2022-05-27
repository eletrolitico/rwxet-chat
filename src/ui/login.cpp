#include "ui/login.h"

#include "net/auth.h"

namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Login, wxPanel)
        EVT_BUTTON(ID_LoginBtn,Login::OnLogin)
    wxEND_EVENT_TABLE()

    Login::Login(wxWindow *parent):wxPanel(parent)
    {
        wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
        wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText *txt = new wxStaticText(this, wxID_ANY, wxString::FromUTF8("Digite as informações para fazer login"));
        m_server   = new wxTextCtrl(this, wxID_ANY, "rocket-chat.alpha.com.vc", wxDefaultPosition, {400,40});
        m_username = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, {400,40});
        m_password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, {400,40}, wxTE_PASSWORD);

        m_server->SetHint("URL do servidor");
        m_username->SetHint(wxString::FromUTF8("Usuário"));
        m_password->SetHint("Senha");

        wxButton *btn = new wxButton(this, ID_LoginBtn, "Login");

        boxSizer->Add(txt,        0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(m_server,   0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(m_username, 0, wxCENTER);
        boxSizer->Add(m_password, 0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(btn,        0, wxCENTER);

        boxSizer->SetDimension({0,0}, {400,300});

        topSizer->Add(boxSizer, 1, wxALIGN_CENTER_VERTICAL|wxALL);

        SetSizerAndFit(topSizer);
    }

    void Login::OnLogin(wxCommandEvent &evt){
        std::string server = m_server->GetValue().ToStdString();
        std::string user = m_username->GetValue().ToStdString();
        std::string pass = m_password->GetValue().ToStdString();

        try{
            std::string resp = rwxet_net::login(server, user, pass);
            std::cout << "Resposta: "<< resp << std::endl;
        }catch(const std::exception& e){
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

}