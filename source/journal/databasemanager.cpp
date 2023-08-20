#include "journal/databasemanager.h"
#include "journal/entry.h"
#include "wx/log.h"
#include "wx/intl.h"

todo::DatabaseManager::DatabaseManager(const wxString &path)
{
    if( SQLITE_OK != sqlite3_open(path.c_str(), &p_Db))
    {
        wxLogError("Unable to open database on path: " + path);
    }

    InitQueries();
}

todo::DatabaseManager::~DatabaseManager() {
    ClearQueries();
    sqlite3_close(p_Db);
}

bool todo::DatabaseManager::AddNewJournalEntry(JournalEntry &entry) const
{
    sqlite3_stmt* sql = p_CreateJournalEntiresQuery;

    wxCharBuffer strStringValue = entry.getContent().ToUTF8();
    const char* localStringValue = strStringValue;

    wxCharBuffer dateStringValue = entry.getDate().FormatISODate().ToUTF8();
    const char* localDateValue = dateStringValue;

    sqlite3_bind_text(sql, 1, localStringValue, -1, SQLITE_STATIC);
    sqlite3_bind_text(sql, 2, localDateValue, -1, SQLITE_STATIC);

    int status = sqlite3_step( sql );
    switch(status)
    {
        case SQLITE_DONE:
            entry.setId( sqlite3_last_insert_rowid(p_Db) );
            break;
        default:
            wxLogError("Unhandled status code in sql query: " + wxString::Format(wxT("%i"), status));
            break;
    }

    //return false;
    sqlite3_clear_bindings( sql );
    sqlite3_reset( sql );
    return status == SQLITE_DONE;
}

std::vector<int> todo::DatabaseManager::GetListOfJournalYears() const
{
    char* error_message;
    std::vector<int> years_vector;
    int status = sqlite3_exec(
        p_Db,
        "select distinct SUBSTRING(date, 0, 5) from journalentries",
        [](void* vector_ptr, int argc, char** data, char** azColName) // https://stackoverflow.com/questions/31146713/sqlite3-exec-callback-function-clarification
        {
            auto years_vector = static_cast<std::vector<int>*>(vector_ptr);
            years_vector->push_back( std::stoi( data[0] ));
            return SQLITE_OK;
        },
        &years_vector, &error_message);

    if(status == SQLITE_OK)
    {
        return years_vector;
    }

    wxLogError(error_message);
    return {};
}

//bool todo::DatabaseManager::DeleteJournalEntry(JournalEntry const& entry) const
//{
//    QSqlQuery query;
//    query.prepare("delete from journalentries where id = (:id)");
//    query.bindValue(":id", entry.getId());
//
//    if(query.exec())
//    {
//        qDebug() << "Deleted journalentry with id" << entry.getId();
//        return true;
//    }
//
//    qDebug() << "Unable to delete journal entry: " << query.lastError();
//    return false;
//}
//

//
//std::unique_ptr<std::vector<todo::JournalEntry>>
//todo::DatabaseManager::GetAllJournalEntriesBetween(QDate min, QDate max)
//{
//    QSqlQuery query("select id, date, content from journalentries where date >= '2022-01-01' and date <= '2024-01-01'");
//    //query.prepare("select id, date, content from journalentries where date >= :min and date <= :max");
//    //query.prepare("select id, date, content from journalentries where date >= '2022-01-01' and date <= '2024-01-01'");
//    //query.bindValue(":min", min.toString("yyyy-MM-dd"));
//    //query.bindValue(":max", max.toString("yyyy-MM-dd"));
//
//    if(query.exec())
//    {
//        qDebug() << query.lastQuery();
//
//        if(query.next())
//        {
//            std::unique_ptr<std::vector<JournalEntry>> entries = std::unique_ptr<std::vector<JournalEntry>>(
//                    new std::vector<JournalEntry>()
//            );
//
//            do
//            {
//                entries->push_back(JournalEntry(query.value(0).toInt(), query.value(1).toDate(), query.value(2).toString()));
//            }
//            while(query.next());
//
//            qDebug() << "Fetched " << entries->size() << " journal entries between" << min << " and " << max;
//            return std::move(entries);
//        }
//    }
//
//    qDebug() << "Unable to fetch journal entries: " << query.lastError();
//    return nullptr;
//}
//
//void todo::DatabaseManager::UpdateJournalEntryContent(QString const& entryContent, int entryId) const
//{
//    QSqlQuery query;
//    query.prepare("update journalentries set content = (:content) where id = (:id)");
//    query.bindValue(":content", entryContent);
//    query.bindValue(":id", entryId);
//
//    if(query.exec())
//    {
//        qDebug() << query.lastQuery();
//        return;
//    }
//
//    qDebug() << "Unable to update journal entry: " << query.lastError();
//}

void todo::DatabaseManager::InitQueries() {
    int status = sqlite3_prepare_v2(
            p_Db,
            "insert into journalentries (content, date) values (:content, :date)",
            -1,
            &p_CreateJournalEntiresQuery,
            nullptr
    );

    wxLogMessage("Status for prepared statement: " + wxString::Format(wxT("%i"), status));
}

void todo::DatabaseManager::ClearQueries() {
    sqlite3_finalize(p_CreateJournalEntiresQuery);
}

//wxString data;
//const char* dbdata;
//
//For unicode build, simply do:
//
//dbdata = data.mb_str(wxConvUTF8);
//data = wxString(dbdata,wxConvUTF8);