#include <marky/Marky.h>
#include <marky/backend/html_backend.h>

#include <wx/wx.h>
#include "wx/splitter.h"
#include <wx/webview.h>

#include "ui/journymainframe.h"
#include "ui/icons.h"

#include <iostream>
#include <utility>


JournyMainFrame::JournyMainFrame(std::shared_ptr<todo::DatabaseManager> db, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE), p_Db(std::move(db))
{
    Bind(wxEVT_LIST_ITEM_SELECTED, &JournyMainFrame::OnListSelected, this );
}

void JournyMainFrame::SetUpUi() {
    SetSize(wxSize(640, 480));
    SetTitle(wxT("Journy"));

    create_menu();

    main_divider = new wxBoxSizer(wxHORIZONTAL);
    auto* left_menu_sizer = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(left_menu_sizer, 0, wxEXPAND | wxRIGHT, 4);

    journal_entry_list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    journal_entry_list->AppendColumn(wxT("Journal Entries"), wxLIST_FORMAT_LEFT, 200);
    left_menu_sizer->Add(journal_entry_list, 1, wxEXPAND, 0);
    InitListData();

    calendar_ctrl = create_calendar();
    left_menu_sizer->Add(calendar_ctrl, 0, 0, 0);

    create_editor_area();

    SetSizer(main_divider);
    Layout();

    create_toolbar();
}

void JournyMainFrame::InitListData(int year)
{
    wxDateTime min(1, wxDateTime::Month::Jan, year), max(31, wxDateTime::Month::Dec, year);
    InitListData(min, max);
    currentDisplayYear = year;
}

void JournyMainFrame::InitListData(wxDateTime min, wxDateTime max)
{
    assert(min <= max);

    entries.clear();
    journal_entry_list->DeleteAllItems();
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

void JournyMainFrame::OnListSelected(wxListEvent &event) {
    auto const& item = event.GetItem();
    auto const* entry = reinterpret_cast<todo::JournalEntry const*>(item.GetData());

    SetWebViewContent(entry->getContent());

    markdown_editor->ChangeValue(entry->getContent());
}

void JournyMainFrame::SetWebViewContent(wxString const& markdown) {
    marky::Marky marky;                             // TODO: Move to member variable
    marky::backend::html::MarkdownToHtml backend;   // TODO: Move to member variable

    marky.process_markdown(&backend, markdown.utf8_string());
    auto html = backend.get_html();

    webview->SetPage(html, "/");
}

void JournyMainFrame::create_toolbar() {
    wxBitmapBundle toolBarBitmaps[4];
    toolBarBitmaps[0] = wxBitmapBundle::FromSVG(svg_body_text, wxSize(16, 16));
    toolBarBitmaps[1] = wxBitmapBundle::FromSVG(svg_layout_split, wxSize(16, 16));
    toolBarBitmaps[2] = wxBitmapBundle::FromSVG(svg_pencil_square, wxSize(16, 16));
    toolBarBitmaps[3] = wxBitmapBundle::FromSVG(svg_box_arrow_down, wxSize(16, 16));

    long style = 0;
    style |= wxTB_RIGHT;
    style &= ~wxTB_NO_TOOLTIPS;

    auto reading_mode_id = wxWindow::NewControlId();
    auto split_edit_mode_id = wxWindow::NewControlId();
    auto save_entry = wxWindow::NewControlId();

    toolbar = CreateToolBar(style);
    toolbar->AddTool(reading_mode_id, wxT("Reading Mode"), toolBarBitmaps[0]);
    toolbar->AddTool(split_edit_mode_id, wxT("Edit Mode"), toolBarBitmaps[1]);
    toolbar->AddSeparator();
    toolbar->AddTool(save_entry, wxT("Save"), toolBarBitmaps[3]);
    toolbar->Realize();

    Connect(reading_mode_id, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(JournyMainFrame::OnEnterReadingMode));
    Connect(split_edit_mode_id, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(JournyMainFrame::OnEnterSplitEditMode));
    Connect(save_entry, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(JournyMainFrame::OnSave));
}

void JournyMainFrame::create_editor_area()
{
    auto* sizer_4 = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(sizer_4, 6, wxEXPAND, 0);

    editor_splitter = new wxSplitterWindow(this, -1, wxPoint(0, 0), wxSize(400, 400));

    webview = wxWebView::New();
    webview->Create(editor_splitter, wxID_ANY);

    markdown_editor = new wxTextCtrl(editor_splitter, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    markdown_editor->Show(false);
    markdown_editor->Bind(wxEVT_TEXT, &JournyMainFrame::OnTextChange, this);

    sizer_4->Add(editor_splitter, 1, wxEXPAND, 0);
    editor_splitter->Initialize(webview);
}

// Todo: add setting for having text editor to the right?
void JournyMainFrame::OnEnterSplitEditMode(wxCommandEvent& WXUNUSED(event))
{
    if ( editor_splitter->IsSplit() )
        editor_splitter->Unsplit();
    webview->Show(true);
    markdown_editor->Show(true);

    if(bSplitVertically)
    {
        editor_splitter->SplitVertically( markdown_editor, webview );
    }
    else
    {
        editor_splitter->SplitHorizontally( markdown_editor, webview );
    }

    EditState = JournalEntryUiState::SplitEditMode;
}

void JournyMainFrame::OnTextChange(wxCommandEvent &event)
{
    SetWebViewContent(markdown_editor->GetValue());

    long selected = journal_entry_list->GetFocusedItem();
    if(selected >= 0) {
        auto* entry = reinterpret_cast<todo::JournalEntry*>(journal_entry_list->GetItemData(selected));
        entry->setContent(markdown_editor->GetValue());
    }
}

void JournyMainFrame::OnSave(wxCommandEvent &event) {
    //markdown_editor->GetValue()
    long selected = journal_entry_list->GetFocusedItem();
    if(selected >= 0)
    {
        auto const* entry = reinterpret_cast<todo::JournalEntry*>(journal_entry_list->GetItemData(selected));
        p_Db->UpdateJournalEntryContent(*entry);
    }
}

void JournyMainFrame::create_menu() {
    frame_menubar = new wxMenuBar();

    auto* file_menu = new wxMenu();
    file_menu->Append(wxID_NEW, _T("New Entry"));
    file_menu->Append(wxID_SAVE, _T("Save"));
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT, _T("&Quit"));

    auto const readingModeId = wxWindow::NewControlId();
    auto const splitEditModeId = wxWindow::NewControlId();
    auto* edit_menu = new wxMenu();
    edit_menu->Append(readingModeId, _T("Reading Mode"));
    edit_menu->Append(splitEditModeId, _T("Edit Mode"));

    frame_menubar->Append(file_menu, wxT("File"));
    frame_menubar->Append(edit_menu, wxT("Edit"));
    SetMenuBar(frame_menubar);

    Bind(wxEVT_MENU, &JournyMainFrame::OnNewEntry, this, wxID_NEW);
    Bind(wxEVT_MENU, &JournyMainFrame::OnEnterSplitEditMode, this, splitEditModeId);
    Bind(wxEVT_MENU, &JournyMainFrame::OnEnterReadingMode, this, readingModeId);
}

void JournyMainFrame::OnEnterReadingMode(wxCommandEvent &event)
{
    if ( editor_splitter->IsSplit() )
    {
        editor_splitter->Unsplit(markdown_editor);
    }

    editor_splitter->Initialize(webview);
    EditState = JournalEntryUiState::ReadingMode;
}

wxCalendarCtrl* JournyMainFrame::create_calendar()
{
    auto* calendar = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_WEEK_NUMBERS);

    calendar->Bind(wxEVT_CALENDAR_SEL_CHANGED, &JournyMainFrame::OnCalendarSelectionChange, this);

    return calendar;
}

void JournyMainFrame::OnCalendarSelectionChange(wxCalendarEvent& event) {
    if(currentDisplayYear == event.GetDate().GetYear())
    {
        return;
    }

    InitListData(event.GetDate().GetYear());
}

void JournyMainFrame::OnNewEntry(wxCommandEvent &event)
{
    auto selectedDate = calendar_ctrl->GetDate();
    todo::JournalEntry newEntry(selectedDate, "");
    p_Db->AddNewJournalEntry(newEntry);

    if(selectedDate.GetYear() == currentDisplayYear)
    {
        InitListData(); // For simplicity, we just reload everything in this case
    }

    wxMessageBox("Journal entry has been created!", "Entry Created", wxOK);
}
