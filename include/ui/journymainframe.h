#pragma once

#include "journal/databasemanager.h"

#include <wx/wx.h>
#include <wx/image.h>

#include <wx/calctrl.h>
#include <wx/listctrl.h>
#include <memory>
#include <utility>

enum class JournalEntryUiState
{
    ReadingMode,
    SplitEditMode,
    ExclusiveEditMode
};

class JournyMainFrame: public wxFrame {
public:
    JournyMainFrame(todo::DatabaseManager* db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

    void SetUpUi();

    void InitListData();

protected:
    wxMenuBar* frame_menubar;
    wxListView* journal_entry_list;
    wxCalendarCtrl* calendar_ctrl_1;
    class wxToolBar* toolbar;

    class wxBoxSizer* main_divider;
    class wxSplitterWindow* editor_splitter;
    bool bSplitVertically { true };

    class wxWebView* webview;
    class wxTextCtrl* markdown_editor;

    JournalEntryUiState EditState {JournalEntryUiState::ReadingMode };
    std::vector<todo::JournalEntry> entries;

    void create_editor_area();
    void create_toolbar();
private:
    std::shared_ptr<todo::DatabaseManager> p_Db;

    void OnListSelectedHandler(wxListEvent& event);
    void OnEnterSplitEditMode(wxCommandEvent& event);
};

