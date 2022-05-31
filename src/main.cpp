// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "ui/frame.h"
#include "net/ctrl.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if(!rwxet_net::check_user_cfg()){
        return false;
    }

    rwxet_ui::Frame *frame = new rwxet_ui::Frame;
    frame->Show(true);
    return true;
}
