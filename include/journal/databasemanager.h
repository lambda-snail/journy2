#pragma once

#include "journal/entry.h"

#include <memory>
#include <sqlite3.h>
#include <wx/datetime.h>

namespace todo {
    class DatabaseManager
    {
    public:
        explicit DatabaseManager(wxString const& path);
        ~DatabaseManager();

        bool AddNewJournalEntry(JournalEntry& entry) const;
        void UpdateJournalEntryContent(JournalEntry const& entry) const;
//        bool DeleteJournalEntry(JournalEntry const& entry) const;
//
//        void GetAllJournalEntries();

        [[nodiscard]] std::vector<int> GetListOfJournalYears() const;

        [[nodiscard]] std::vector<JournalEntry>
        GetAllJournalEntriesBetween(wxDateTime min, wxDateTime max);

    private:
        sqlite3* p_Db;

        sqlite3_stmt* p_CreateJournalEntiresQuery;
        sqlite3_stmt* p_GetEntriesBetweenDatesQuery;
        sqlite3_stmt* p_UpdateEntryContentQuery;

        void InitQueries();
        void ClearQueries();
    };
}
