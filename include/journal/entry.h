#pragma once

#include "wx/string.h"
#include "wx/datetime.h"

namespace todo {
    class JournalEntry
    {
    public:

        JournalEntry() = default;
        JournalEntry(JournalEntry const& rhs);
        JournalEntry(JournalEntry&& rhs) noexcept;
        JournalEntry(wxDateTime date, wxString const& content);
        JournalEntry(int id, wxDateTime date, wxString const& content);

        JournalEntry& operator=(todo::JournalEntry const& other) = default;

        [[nodiscard]] long long getId() const;
        void setId(long long newId);

        [[nodiscard]] wxDateTime getDate() const;
        void setDate(wxDateTime const& newDate);

        [[nodiscard]] wxString getContent() const;
        void setContent(wxString const& newContent);

        [[nodiscard]] wxString toString() const;
    private:

        long long Id { };
        wxDateTime Date { };
        wxString Content { };
    };
}
