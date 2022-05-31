#include "ui/login.h"

#include "net/auth.h"

namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Login, wxPanel)
        EVT_BUTTON(ID_LoginBtn, Login::OnLogin)
    wxEND_EVENT_TABLE()

    Login::Login(wxWindow *parent):wxPanel(parent)
    {
        constexpr int width = 400;
        wxSize inputSize = wxDefaultSize;
        inputSize.SetWidth(400);

        wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText *txt = new wxStaticText(this, wxID_ANY, wxString::FromUTF8("Digite as informações para fazer login"));
        m_server   = new wxTextCtrl(this, wxID_ANY, "rocket-chat.alpha.com.vc", wxDefaultPosition, inputSize);
        m_username = new wxTextCtrl(this, wxID_ANY, "",                         wxDefaultPosition, inputSize);
        m_password = new wxTextCtrl(this, wxID_ANY, "",                         wxDefaultPosition, inputSize, wxTE_PASSWORD);

        wxStaticText *serverLabel = new wxStaticText(this, wxID_ANY, "Servidor", wxDefaultPosition, wxSize(width,20));
        wxStaticText *userLabel   = new wxStaticText(this, wxID_ANY, wxString::FromUTF8("Usuário"), wxDefaultPosition, wxSize(width,20));
        wxStaticText *passLabel   = new wxStaticText(this, wxID_ANY, "Senha", wxDefaultPosition, wxSize(width,20));

        wxButton *btn = new wxButton(this, ID_LoginBtn, "Login");

        boxSizer->AddStretchSpacer();
        boxSizer->Add(txt,        0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(serverLabel, 0, wxCENTER);
        boxSizer->Add(m_server,    0, wxCENTER);
        boxSizer->AddSpacer(15);

        boxSizer->Add(userLabel,  0, wxCENTER);
        boxSizer->Add(m_username, 0, wxCENTER);
        boxSizer->AddSpacer(5);
        boxSizer->Add(passLabel,  0, wxCENTER);
        boxSizer->Add(m_password, 0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(btn,        0, wxCENTER);
        boxSizer->AddStretchSpacer();

        SetSizerAndFit(boxSizer);
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