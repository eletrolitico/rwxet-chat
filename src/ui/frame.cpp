#include "ui/frame.h"
#include "ctrl/cfg.h"

namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Frame, wxFrame)
        EVT_MENU(ID_Hello,   Frame::OnHello)
        EVT_MENU(wxID_EXIT,  Frame::OnExit)
        EVT_MENU(wxID_ABOUT, Frame::OnAbout)
    wxEND_EVENT_TABLE()

    Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Rwxet Chat", wxPoint(50, 50), wxSize(450, 340))
    {
        auto menuFile = new wxMenu;
        menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        auto menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        auto menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuHelp, "&Help");

        auto cfg = rwxet_ctrl::Cfg::Get();
        if(cfg->HasConfig()){
            main = new Main(this);
            main->Show(true);
        } else {
            login = new Login(this);
            login->Show(true);
        }

        SetMenuBar(menuBar);
    }

    void Frame::OnExit(wxCommandEvent &)
    {
        Close(true);
    }

    void Frame::OnAbout(wxCommandEvent &)
    {
        wxMessageBox("This is a Rocket Chat client", "About Rwxet Chat", wxOK | wxICON_INFORMATION);
    }

    void Frame::OnHello(wxCommandEvent &)
    {
        wxLogMessage("Hello world from wxWidgets!");
    }

} // namespace rwxet_ui
