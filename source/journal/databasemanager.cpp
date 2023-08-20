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

std::vector<todo::JournalEntry>
todo::DatabaseManager::GetAllJournalEntriesBetween(wxDateTime min, wxDateTime max)
{
    wxCharBuffer minValueBuffer = min.FormatISODate().ToUTF8();
    const char* minValueString = minValueBuffer;

    wxCharBuffer maxValueBuffer = max.FormatISODate().ToUTF8();
    const char* maxValueString = maxValueBuffer;

    auto* sql = p_GetEntriesBetweenDatesQuery;
    sqlite3_bind_text(sql, 1, minValueString, -1, SQLITE_STATIC);
    sqlite3_bind_text(sql, 2, maxValueString, -1, SQLITE_STATIC);

    std::vector<JournalEntry> entries;
    int status = sqlite3_step( sql );
    while(status == SQLITE_ROW)
    {
        long long id = sqlite3_column_int64(sql, 0);
        unsigned char const* date_str = sqlite3_column_text(sql, 1);
        unsigned char const* content_str = sqlite3_column_text(sql, 2);

        wxDateTime date; date.ParseDate(date_str);
        entries.emplace_back(id, date, content_str);

        status = sqlite3_step( sql );
    }

    sqlite3_clear_bindings( sql );
    sqlite3_reset( sql );

    if(status == SQLITE_DONE)
    {
        return entries;
    }
    else
    {
        wxLogError(sqlite3_errmsg(p_Db));
        return {};
    }
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
    sqlite3_prepare_v2(
            p_Db,
            "insert into journalentries (content, date) values (:content, :date)",
            -1,
            &p_CreateJournalEntiresQuery,
            nullptr
    );

    sqlite3_prepare_v2(
            p_Db,
            "select id, date, content from journalentries where date >= :min and date <= :max",
            -1,
            &p_GetEntriesBetweenDatesQuery,
            nullptr
    );
}

void todo::DatabaseManager::ClearQueries() {
    sqlite3_finalize(p_CreateJournalEntiresQuery);
    sqlite3_finalize(p_GetEntriesBetweenDatesQuery);
}
