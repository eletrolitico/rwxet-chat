#include "ui/main.h"
#include "ctrl/cfg.h"
#include "net/chat.h"

namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Main, wxPanel)
    wxEND_EVENT_TABLE()

    Main::Main(wxWindow *parent) : wxPanel(parent)
    {
        rwxet_ctrl::cfg_data const &cfg = rwxet_ctrl::Cfg::Get()->GetConfig();
        auto topSizer = new wxBoxSizer(wxHORIZONTAL);

        auto leftSizer = new wxBoxSizer(wxVERTICAL);
        auto rightSizer = new wxBoxSizer(wxVERTICAL);

        topSizer->Add(leftSizer);
        topSizer->Add(rightSizer);

        auto txt = new wxStaticText(this, wxID_ANY, wxT("Olá " + cfg.name));
        leftSizer->Add(txt);

        try
        {
            auto friends = rwxet_net::get_friends();

            for (auto f : friends)
                leftSizer->Add(new wxStaticText(this, wxID_ANY, f));
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }

        SetSizerAndFit(topSizer);
    }

}