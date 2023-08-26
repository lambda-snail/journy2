#include <wx/wx.h>
#include <wx/webview.h>

#include <iostream>

#include "ui/journymainframe.h"

JournyMainFrame::JournyMainFrame(todo::DatabaseManager* db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE), p_Db(db)
{
    Bind( wxEVT_LIST_ITEM_SELECTED, &JournyMainFrame::OnListSelectedHandler, this );
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

    journal_entry_list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES | wxLC_REPORT | wxLC_VRULES);
    journal_entry_list->AppendColumn(wxT("Journal Entries"), wxLIST_FORMAT_LEFT, -1);
    left_menu_sizer->Add(journal_entry_list, 1, wxEXPAND, 0);
    InitListData();

    calendar_ctrl_1 = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime);
    left_menu_sizer->Add(calendar_ctrl_1, 0, 0, 0);

    auto* sizer_4 = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(sizer_4, 6, wxEXPAND, 0);

    webview = wxWebView::New();
    webview->Create(this, wxID_ANY);
    sizer_4->Add(webview, 1, wxEXPAND, 0);

    SetSizer(main_divider);
    Layout();
}

void JournyMainFrame::InitListData() {
    wxDateTime min, max;
    min.ParseDate("2023-01-01");
    max.ParseDate("2023-12-31");

    entries.clear();
    entries = p_Db->GetAllJournalEntriesBetween(min, max);
    for(int i = 0; i < entries.size(); ++i)
    {
        todo::JournalEntry& entry = entries[i];

        wxListItem item;
        item.SetId(static_cast<long>(entry.getId()));
        item.SetColumn(0);
        item.SetText(entry.getDate().FormatISODate());
        item.SetData(&entry);

        journal_entry_list->InsertItem(item);
    }
}

void JournyMainFrame::OnListSelectedHandler(wxListEvent &event) {
    auto const& item = event.GetItem();
    auto const* entry = reinterpret_cast<todo::JournalEntry const*>(item.GetData());
    webview->SetPage(entry->getContent(), "/");
}

