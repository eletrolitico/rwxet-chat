#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <wx/wx.h>

namespace rwxet_ui
{
    class Main : public wxPanel
    {
    public:
        Main(wxWindow *parent);

    private:
        wxDECLARE_EVENT_TABLE();
    };

}

#endif