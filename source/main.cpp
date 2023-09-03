#include <wx/wx.h>
#include <wx/config.h>

#include <memory>
#include "ui/journymainframe.h"

#include "journal/entry.h"
#include "journal/databasemanager.h"

class MyApp: public wxApp {
public:
    bool OnInit() override;
private:
    //std::unique_ptr<todo::DatabaseManager> p_Db;
    std::shared_ptr<todo::DatabaseManager> p_Db;
    std::shared_ptr<wxConfig> config;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    config = std::make_shared<wxConfig>("journy");

    // Temporary solution during initial development
#ifdef WIN32
    p_Db = std::shared_ptr<todo::DatabaseManager>(R"(C:\Projects\cpp\journy2\resources\todo.db)");
#else
    p_Db = std::make_shared<todo::DatabaseManager>(R"(/home/niclas/projects/cpp/journy2/resources/todo.db)");
#endif

    wxInitAllImageHandlers();
    auto* frame = new JournyMainFrame(p_Db, nullptr, wxID_ANY, wxEmptyString);
    frame->SetUpUi();

    SetTopWindow(frame);
    frame->Center();
    frame->Show();
    return true;
}
