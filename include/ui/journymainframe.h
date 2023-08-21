#pragma once

#include "journal/databasemanager.h"

#include <wx/wx.h>
#include <wx/image.h>

// begin wxGlade: ::dependencies
#include <wx/calctrl.h>
#include <wx/listctrl.h>
#include <memory>
#include <utility>
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade

struct EntryListData
{
    EntryListData(todo::JournalEntry e, long i) : entry(std::move(e)), index(i) { }
    todo::JournalEntry entry;
    long index;
};

class JournyMainFrame: public wxFrame {
public:
    // begin wxGlade: JournyMainFrame::ids
    // end wxGlade

    JournyMainFrame(todo::DatabaseManager* db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

    void SetUpUi();

    void InitListData();

protected:
    wxMenuBar* frame_menubar;
    wxListCtrl* journal_entry_list;
    wxCalendarCtrl* calendar_ctrl_1;
    class wxWebView* webview;

    std::vector<EntryListData> entries;
    //wxPanel* panel_1;

private:
    std::shared_ptr<todo::DatabaseManager> p_Db;

    void OnListSelectedHandler(wxListEvent& event);
};

