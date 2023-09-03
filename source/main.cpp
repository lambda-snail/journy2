#include <wx/wx.h>
#include <wx/config.h>
#include <wx/stdpaths.h>

#include <memory>
#include "ui/journymainframe.h"

#include "config_strings.h"
#include "journal/entry.h"
#include "journal/databasemanager.h"

class MyApp: public wxApp {
public:
    bool OnInit() override;
private:
    std::shared_ptr<todo::DatabaseManager> p_Db;
    std::shared_ptr<wxConfig> config;

    void ensure_exists_initial_db_path(wxString& outPath, bool& shouldInitializeDb);
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    config = std::make_shared<wxConfig>(App::name);

    bool shouldInitDb { false };
    wxString db_path;
    ensure_exists_initial_db_path(db_path, shouldInitDb);

    p_Db = std::make_shared<todo::DatabaseManager>(db_path, shouldInitDb);

    wxInitAllImageHandlers();
    auto* frame = new JournyMainFrame(p_Db, nullptr, wxID_ANY, wxEmptyString);
    frame->SetUpUi();

    SetTopWindow(frame);
    frame->Center();
    frame->Show();
    return true;
}

void MyApp::ensure_exists_initial_db_path(wxString& outPath, bool& shouldInitializeDb) {
    if ( not config->Read(Config::last_db_location, &outPath) ) {
        wxFileName path;
        auto const& standardPaths = wxStandardPaths::Get();

        path.AssignDir(standardPaths.GetUserDataDir());
        if(not path.DirExists())
        {
            path.Mkdir(wxPOSIX_USER_EXECUTE | wxPOSIX_USER_READ | wxPOSIX_USER_WRITE, wxPATH_MKDIR_FULL);
        }

        path.SetName(Config::db_name);
        shouldInitializeDb = not path.FileExists();

        outPath = path.GetFullPath();
        config->Write(Config::last_db_location, outPath);
    }
}
