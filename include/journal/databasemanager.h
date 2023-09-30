#pragma once

#include "journal/entry.h"

#include <memory>
#include <sqlite3.h>
#include <string>
#include <chrono>

namespace todo {
    class DatabaseManager
    {
    public:
        explicit DatabaseManager(std::string const& path, bool shouldInitDb = false);
        ~DatabaseManager();

        bool AddNewJournalEntry(JournalEntry& entry) const;
        void UpdateJournalEntryContent(JournalEntry const& entry) const;
        bool DeleteJournalEntry(JournalEntry const& entry) const;
//
//        void GetAllJournalEntries();

        [[nodiscard]] std::vector<int> GetListOfJournalYears() const;

        [[nodiscard]] std::vector<JournalEntry>
        GetAllJournalEntriesBetween(std::chrono::year_month_day min, std::chrono::year_month_day max);

        static const std::string config_last_db_location;
    private:
        sqlite3* p_Db;

        sqlite3_stmt* p_CreateJournalEntiresQuery;
        sqlite3_stmt* p_GetEntriesBetweenDatesQuery;
        sqlite3_stmt* p_UpdateEntryContentQuery;
        sqlite3_stmt* p_DeleteEntry;

        void InitQueries();
        void ClearQueries();

        std::string database_path;
    };
}
