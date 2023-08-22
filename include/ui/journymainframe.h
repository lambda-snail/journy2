#pragma once

#include "journal/databasemanager.h"

#include <wx/wx.h>
#include <wx/image.h>

#include <wx/calctrl.h>
#include <wx/listctrl.h>
#include <memory>
#include <utility>


class JournyMainFrame: public wxFrame {
public:
    JournyMainFrame(todo::DatabaseManager* db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

    void SetUpUi();

    void InitListData();

protected:
    wxMenuBar* frame_menubar;
    wxListCtrl* journal_entry_list;
    wxCalendarCtrl* calendar_ctrl_1;
    class wxWebView* webview;

    std::vector<todo::JournalEntry> entries;

private:
    std::shared_ptr<todo::DatabaseManager> p_Db;

    void OnListSelectedHandler(wxListEvent& event);
};

