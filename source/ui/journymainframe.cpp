#include <wx/wx.h>
#include "ui/journymainframe.h"

JournyMainFrame::JournyMainFrame(todo::DatabaseManager* db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE), p_Db(db)
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

    journal_entry_list = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES | wxLC_REPORT | wxLC_VRULES);
    journal_entry_list->AppendColumn(wxT("Journal Entries"), wxLIST_FORMAT_LEFT, -1);
    left_menu_sizer->Add(journal_entry_list, 1, wxEXPAND, 0);
    InitListData();

    calendar_ctrl_1 = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime);
    left_menu_sizer->Add(calendar_ctrl_1, 0, 0, 0);

    auto* sizer_4 = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(sizer_4, 6, wxEXPAND, 0);

    panel_1 = new wxPanel(this, wxID_ANY);
    sizer_4->Add(panel_1, 1, wxEXPAND, 0);

    SetSizer(main_divider);
    Layout();
}

void JournyMainFrame::InitListData() {
    //journal_entry_list
    wxDateTime min, max;
    min.ParseDate("2023-01-01");
    max.ParseDate("2023-12-31");

    auto entries = p_Db->GetAllJournalEntriesBetween(min, max);
    for(auto const& entry : entries)
    {
        long itemIndex = journal_entry_list->InsertItem(0, entry.getDate().FormatISODate()); //want this for col. 1
        //WxListCtrl1->SetItem(itemIndex, 1, "18:00"); //want this for col. 2
    }
}

