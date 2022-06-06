#include "ui/main.h"


namespace rwxet_ui
{
    wxBEGIN_EVENT_TABLE(Main, wxPanel)
    wxEND_EVENT_TABLE()

    Main::Main(wxWindow *parent):wxPanel(parent)
    {
        wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);




        SetSizerAndFit(topSizer);
    }


}