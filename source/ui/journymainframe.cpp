#include <wx/wx.h>
#include "ui/journymainframe.h"

JournyMainFrame::JournyMainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{

}

void JournyMainFrame::SetUpUi() {
    SetSize(wxSize(640, 480));
    SetTitle(wxT("Journy"));

    frame_menubar = new wxMenuBar();
    wxMenu *wxglade_tmp_menu;
    wxglade_tmp_menu = new wxMenu();
    frame_menubar->Append(wxglade_tmp_menu, wxT("File"));
    SetMenuBar(frame_menubar);
    auto* main_divider = new wxBoxSizer(wxHORIZONTAL);
    auto* left_menu_sizer = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(left_menu_sizer, 0, wxEXPAND | wxRIGHT, 4);

    list_ctrl_1 = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_VRULES);
    list_ctrl_1->AppendColumn(wxT("A"), wxLIST_FORMAT_LEFT, -1);
    left_menu_sizer->Add(list_ctrl_1, 1, wxEXPAND, 0);

    calendar_ctrl_1 = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime);
    left_menu_sizer->Add(calendar_ctrl_1, 0, 0, 0);

    auto* sizer_4 = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(sizer_4, 6, wxEXPAND, 0);

    panel_1 = new wxPanel(this, wxID_ANY);
    sizer_4->Add(panel_1, 1, wxEXPAND, 0);

    SetSizer(main_divider);
    Layout();
}

