#pragma once

#include <wx/wx.h>
#include <wx/image.h>

// begin wxGlade: ::dependencies
#include <wx/calctrl.h>
#include <wx/listctrl.h>
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade


class JournyMainFrame: public wxFrame {
public:
    // begin wxGlade: JournyMainFrame::ids
    // end wxGlade

    JournyMainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

    void SetUpUi();

protected:
    // begin wxGlade: JournyMainFrame::attributes
    wxMenuBar* frame_menubar;
    wxListCtrl* list_ctrl_1;
    wxCalendarCtrl* calendar_ctrl_1;
    wxPanel* panel_1;
    // end wxGlade
};

