#include "ui/journymainframe.h"
#include "ui/icons.h"
#include "wx/splitter.h"
#include <marky/Marky.h>
#include <marky/backend/html_backend.h>

#include <wx/wx.h>
#include <wx/webview.h>

#include <iostream>


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
    main_divider = new wxBoxSizer(wxHORIZONTAL);
    auto* left_menu_sizer = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(left_menu_sizer, 0, wxEXPAND | wxRIGHT, 4);

    journal_entry_list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES | wxLC_REPORT | wxLC_VRULES);
    journal_entry_list->AppendColumn(wxT("Journal Entries"), wxLIST_FORMAT_LEFT, -1);
    left_menu_sizer->Add(journal_entry_list, 1, wxEXPAND, 0);
    InitListData();

    calendar_ctrl_1 = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime);
    left_menu_sizer->Add(calendar_ctrl_1, 0, 0, 0);

    create_editor_area();

    SetSizer(main_divider);
    Layout();

    create_toolbar();
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

    marky::Marky marky;
    marky::backend::html::MarkdownToHtml backend;

    marky.process_markdown(&backend, entry->getContent().utf8_string());
    auto html = backend.get_html();

    webview->SetPage(html, "/");
}

void JournyMainFrame::create_toolbar() {
    wxBitmapBundle toolBarBitmaps[3];
    toolBarBitmaps[0] = wxBitmapBundle::FromSVG(svg_body_text, wxSize(16, 16));
    toolBarBitmaps[1] = wxBitmapBundle::FromSVG(svg_layout_split, wxSize(16, 16));
    toolBarBitmaps[2] = wxBitmapBundle::FromSVG(svg_pencil_square, wxSize(16, 16));

    long style = 0;
    style |= wxTB_RIGHT;
    style &= ~wxTB_NO_TOOLTIPS;

    auto reading_mode_id = wxWindow::NewControlId();
    auto split_edit_mode_id = wxWindow::NewControlId();
    auto exclusive_edit_mode_id = wxWindow::NewControlId();

    toolbar = CreateToolBar(style);
    toolbar->AddTool(reading_mode_id, wxT("Reading Mode"), toolBarBitmaps[0]);
    toolbar->AddTool(split_edit_mode_id, wxT("Split Edit Mode"), toolBarBitmaps[1]);
    toolbar->AddTool(exclusive_edit_mode_id, wxT("Exclusive Edit Mode"), toolBarBitmaps[2]);
    toolbar->AddSeparator();
    toolbar->Realize();

    Connect(split_edit_mode_id, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(JournyMainFrame::OnEnterSplitEditMode));
}

void JournyMainFrame::create_editor_area()
{
    auto* sizer_4 = new wxBoxSizer(wxVERTICAL);
    main_divider->Add(sizer_4, 6, wxEXPAND, 0);

    editor_splitter = new wxSplitterWindow(this, -1, wxPoint(0, 0), wxSize(400, 400));

    webview = wxWebView::New();
    webview->Create(editor_splitter, wxID_ANY);

    markdown_editor = new wxTextCtrl(editor_splitter, wxID_ANY);
    markdown_editor->Show(false);

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
