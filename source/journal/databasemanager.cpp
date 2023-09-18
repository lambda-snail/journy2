#include <chrono>
#include <iostream>
#include <cassert>

#include "journal/databasemanager.h"
#include "journal/entry.h"

todo::DatabaseManager::DatabaseManager(const std::string &path, bool shouldInitDb)
{
    if( SQLITE_OK != sqlite3_open(path.c_str(), &p_Db))
    {
        //wxLogError("Unable to open database on path: " + path);
    }

    if(shouldInitDb)
    {
        char const* error;
        int status = sqlite3_exec(
            p_Db,
            "create table journalentries(id integer primary key, date text, content text);",
            nullptr,
            nullptr,
            nullptr);

        if(status != SQLITE_OK)
        {
            //wxLogError("Unable to initialize database at " + path + ". exec returned with code " + std::to_string(status));
        }
    }

    database_path = path;
    InitQueries();
}

todo::DatabaseManager::~DatabaseManager() {
    ClearQueries();
    sqlite3_close(p_Db);
}

bool todo::DatabaseManager::AddNewJournalEntry(JournalEntry &entry) const
{
    sqlite3_stmt* sql = p_CreateJournalEntiresQuery;

    sqlite3_bind_text(sql, 1, entry.getContent().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(sql, 2, entry.toString().c_str(), -1, SQLITE_TRANSIENT);

    int status = sqlite3_step( sql );
    switch(status)
    {
        case SQLITE_DONE:
            entry.setId( sqlite3_last_insert_rowid(p_Db) );
            break;
        default:
            //wxLogError("Unhandled status code in sql query: " + wxString::Format(wxT("%i"), status));
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

    //wxLogError(error_message);
    return {};
}

std::vector<todo::JournalEntry>
todo::DatabaseManager::GetAllJournalEntriesBetween(std::chrono::year_month_day min, std::chrono::year_month_day max)
{
    assert(min < max);

    auto* sql = p_GetEntriesBetweenDatesQuery;
    sqlite3_bind_text(sql, 1, std::format("{:%F}", min).c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(sql, 2, std::format("{:%F}", max).c_str(), -1, SQLITE_TRANSIENT);

    std::vector<JournalEntry> entries;
    int status = sqlite3_step( sql );
    while(status == SQLITE_ROW)
    {
        long long id = sqlite3_column_int64(sql, 0);
        unsigned char const* date_str = sqlite3_column_text(sql, 1);
        unsigned char const* content_str = sqlite3_column_text(sql, 2);

        std::stringstream s(reinterpret_cast<char const*>(date_str));
        std::chrono::year_month_day ymd{};
        std::chrono::from_stream(s , "%F", ymd);

        entries.emplace_back(id, ymd, reinterpret_cast<char const*>(content_str));

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
        //wxLogError(sqlite3_errmsg(p_Db));
        std::cout << sqlite3_errmsg(p_Db) << std::endl;
        return {};
    }
}

void todo::DatabaseManager::UpdateJournalEntryContent(JournalEntry const& entry) const
{
    auto* sql = p_UpdateEntryContentQuery;
    sqlite3_bind_text(sql, 1, entry.getContent().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(sql, 2, static_cast<int>(entry.getId()));

    int status = sqlite3_step( sql );
    if(status != SQLITE_DONE)
    {
        //wxLogError(sqlite3_errmsg(p_Db));
    }

    sqlite3_clear_bindings( sql );
    sqlite3_reset( sql );
}

bool todo::DatabaseManager::DeleteJournalEntry(JournalEntry const& entry) const
{
    auto* sql = p_DeleteEntry;
    sqlite3_bind_int(sql, 1, static_cast<int>(entry.getId()));

    int status = sqlite3_step( sql );
    if(status != SQLITE_DONE)
    {
        //wxLogError(sqlite3_errmsg(p_Db));
        return false;
    }

    sqlite3_clear_bindings( sql );
    sqlite3_reset( sql );
    return true;
}

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

    sqlite3_prepare_v2(
            p_Db,
            "update journalentries set content = (:content) where id = (:id)",
            -1,
            &p_UpdateEntryContentQuery,
            nullptr
    );

    sqlite3_prepare_v2(
            p_Db,
            "delete from journalentries where id = (:id)",
            -1,
            &p_DeleteEntry,
            nullptr
    );
}

void todo::DatabaseManager::ClearQueries() {
    sqlite3_finalize(p_CreateJournalEntiresQuery);
    sqlite3_finalize(p_GetEntriesBetweenDatesQuery);
    sqlite3_finalize(p_UpdateEntryContentQuery);
    sqlite3_finalize(p_DeleteEntry);
}
