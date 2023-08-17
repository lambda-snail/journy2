#include <wx/wx.h>
#include <wx/image.h>
#include "ui/journymainframe.h"

class MyApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    auto* frame = new JournyMainFrame(nullptr, wxID_ANY, wxEmptyString);
    frame->SetUpUi();

    SetTopWindow(frame);
    frame->Center();
    frame->Show();
    return true;
}