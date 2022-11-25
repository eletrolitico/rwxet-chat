#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "ui/frame.h"
#include "ctrl/cfg.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if (!rwxet_ctrl::Cfg::Get()->Init())
        return false;

    auto *frame = new rwxet_ui::Frame;
    frame->Show(true);
    return true;
}
