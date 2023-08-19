#include <wx/wx.h>
#include <wx/image.h>

#include <memory>
#include "ui/journymainframe.h"

#include "journal/databasemanager.h"

class MyApp: public wxApp {
public:
    bool OnInit() override;
private:
    //std::unique_ptr<todo::DatabaseManager> p_Db;
    todo::DatabaseManager* p_Db;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    //p_Db = std::make_unique<todo::DatabaseManager>(R"(C:\Projects\cpp\journy2\todo.db)");
    p_Db = new todo::DatabaseManager(R"(C:\Projects\cpp\journy2\resources\todo.db)");

    todo::JournalEntry j( wxDateTime(1, wxDateTime::Month::Jan, 2023), "Hello World!" );
    p_Db->AddNewJournalEntry(j);

    //wxLogMessage("Created entry with id: " + wxString::Format(wxT("%i"), j.getId()));

    wxInitAllImageHandlers();
    auto* frame = new JournyMainFrame(nullptr, wxID_ANY, wxEmptyString);
    frame->SetUpUi();

    SetTopWindow(frame);
    frame->Center();
    frame->Show();
    return true;
}