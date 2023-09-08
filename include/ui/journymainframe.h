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
    SplitEditMode
};

class JournyMainFrame: public wxFrame {
public:
    JournyMainFrame(std::shared_ptr<todo::DatabaseManager> db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

    void SetUpUi();

    void InitListData(int year = wxDateTime::Today().GetYear());
    void InitListData(wxDateTime min, wxDateTime max);

protected:
    class wxConfig* config;
    wxMenuBar* frame_menubar;
    wxListView* journal_entry_list;
    wxCalendarCtrl* calendar_ctrl;
    class wxToolBar* toolbar;

    class wxBoxSizer* main_divider;
    class wxSplitterWindow* editor_splitter;
    bool bSplitVertically { true };

    class wxWebView* webview;
    class wxTextCtrl* markdown_editor;

    JournalEntryUiState EditState { JournalEntryUiState::ReadingMode };
    std::vector<todo::JournalEntry> entries;

    void create_menu();
    void create_editor_area();
    void create_toolbar();

    int currentDisplayYear { 0 };
    wxCalendarCtrl* create_calendar();
private:
    std::shared_ptr<todo::DatabaseManager> p_Db;

    void OnListSelected(wxListEvent& event);
    void OnEnterReadingMode(wxCommandEvent& event);
    void OnEnterSplitEditMode(wxCommandEvent& event);
    void OnTextChange(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);

    void OnCalendarSelectionChange(wxCalendarEvent& event);

    void SetWebViewContent(wxString const& markdown);

    void OnNewEntry(wxCommandEvent& event);
    void OnDeleteEntry(wxCommandEvent& event);

    void OnDisplayVersion(wxCommandEvent& event);
};

