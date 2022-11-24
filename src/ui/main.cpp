#include "ui/main.h"
#include "ctrl/cfg.h"

namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Main, wxPanel)
    wxEND_EVENT_TABLE()

    Main::Main(wxWindow *parent) : wxPanel(parent)
    {
        rwxet_ctrl::cfg_data const &cfg = rwxet_ctrl::Cfg::Get()->GetConfig();
        wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);

        auto txt = new wxStaticText(this, wxID_ANY, wxT("Olá " + cfg.name));
        topSizer->Add(txt);

        SetSizerAndFit(topSizer);
    }

}