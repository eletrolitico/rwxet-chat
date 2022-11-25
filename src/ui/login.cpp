#include "ui/login.h"

#include "net/auth.h"
#include "ctrl/cfg.h"

namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Login, wxPanel)
        EVT_BUTTON(ID_LoginBtn, Login::OnLogin)
        EVT_TEXT_ENTER(wxID_ANY, Login::OnLogin)
    wxEND_EVENT_TABLE()

    Login::Login(wxWindow *parent) : wxPanel(parent)
    {
        constexpr int width = 400;
        wxSize inputSize = wxDefaultSize;
        inputSize.SetWidth(400);

        wxBoxSizer *boxSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText *txt = new wxStaticText(this, wxID_ANY, wxT("Digite as informações para fazer login"));
        m_server = new wxTextCtrl(this, wxID_ANY, "https://rocket-chat.alpha.com.vc", wxDefaultPosition, inputSize);
        m_username = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, inputSize);
        m_password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, inputSize, wxTE_PASSWORD);

        auto serverLabel = new wxStaticText(this, wxID_ANY, wxT("Servidor"), wxDefaultPosition, wxSize(width, -1));
        auto userLabel = new wxStaticText(this, wxID_ANY, wxT("Usuário"), wxDefaultPosition, wxSize(width, -1));
        auto passLabel = new wxStaticText(this, wxID_ANY, wxT("Senha"), wxDefaultPosition, wxSize(width, -1));

        wxButton *btn = new wxButton(this, ID_LoginBtn, wxT("Login"));

        boxSizer->AddStretchSpacer();
        boxSizer->Add(txt, 0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(serverLabel, 0, wxCENTER);
        boxSizer->Add(m_server, 0, wxCENTER);
        boxSizer->AddSpacer(15);

        boxSizer->Add(userLabel, 0, wxCENTER);
        boxSizer->Add(m_username, 0, wxCENTER);
        boxSizer->AddSpacer(5);
        boxSizer->Add(passLabel, 0, wxCENTER);
        boxSizer->Add(m_password, 0, wxCENTER);
        boxSizer->AddSpacer(10);

        boxSizer->Add(btn, 0, wxCENTER);
        boxSizer->AddStretchSpacer();

        SetSizerAndFit(boxSizer);

        m_username->SetFocus();
    }

    void Login::OnLogin(wxCommandEvent &evt)
    {
        std::string server = m_server->GetValue().ToStdString();
        std::string user = m_username->GetValue().ToStdString();
        std::string pass = m_password->GetValue().ToStdString();

        try
        {
            if (rwxet_net::login(server, user, pass))
                return;

            auto dlg = new wxTextEntryDialog(this, wxT("Digite o código de autenticação"));
            if (dlg->ShowModal() != wxID_OK)
                return;

            auto cfg = rwxet_ctrl::Cfg::Get();
            cfg->set2FAToken(dlg->GetValue().ToStdString());

            if (!rwxet_net::login(server, user, pass))
                wxMessageBox(wxT("Não foi possível realizar o login no momento"), "Erro no login", wxOK | wxICON_ERROR);
        }
        catch (const std::exception &e)
        {
            wxMessageBox(e.what(), "Erro no login", wxOK | wxICON_ERROR);
        }
        catch (const char *e)
        {
            wxMessageBox(wxString(e), "Erro no login", wxOK | wxICON_ERROR);
        }
    }
}