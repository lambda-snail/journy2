#include "journal/databasemanager.h"
#include "journal/entry.h"
#include "wx/log.h"

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

    sqlite3_bind_text64(sql, 1, entry.getContent().c_str(), -1, SQLITE_STATIC, SQLITE_UTF8);
    sqlite3_bind_text64(sql, 2, entry.getDate().FormatDate(), -1, SQLITE_STATIC, SQLITE_UTF8);

    int status = sqlite3_step( sql );
    switch(status)
    {
        case SQLITE_DONE:
            sqlite3_exec(
                p_Db,
                "select last_insert_rowid()",
                [](void* entry, int argc, char** data, char** azColName) // https://stackoverflow.com/questions/31146713/sqlite3-exec-callback-function-clarification
                {
                    auto entry_ptr = static_cast<JournalEntry*>(entry);
                    entry_ptr->setId( std::stoi( data[0] ));
                    return 5;
                },
                &entry, nullptr);
            break;
        default:
            wxLogError("Unhandled status code in sql query: " + wxString::Format(wxT("%i"), status));
            break;
    }

    sqlite3_clear_bindings( sql );
    sqlite3_reset( sql );
    return status == SQLITE_DONE;
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
//QList<int> todo::DatabaseManager::GetListOfJournalYears() const
//{
//    QSqlQuery query;
//    query.prepare("select distinct SUBSTRING(date, 0, 5) from journalentries");
//
//    QList<int> yearList;
//    if(query.exec())
//    {
//        qDebug() << query.lastQuery();
//
//        if(query.next())
//        {
//            do
//            {
//                yearList.append(query.value(0).toInt());
//            }
//            while(query.next());
//
//            qDebug() << "Fetched " << yearList.size() << " entry years";
//            return yearList;
//        }
//    }
//
//    qDebug() << "Unable to fetch list of entry years: " << query.lastError();
//    return yearList;
//}
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
    sqlite3_prepare_v2(
            p_Db,
            "insert into journalentries (content, date) values (:content, :date)",
            -1,
            &p_CreateJournalEntiresQuery,
            nullptr
    );
}

void todo::DatabaseManager::ClearQueries() {
    sqlite3_finalize(p_CreateJournalEntiresQuery);
}
