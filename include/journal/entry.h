#pragma once

#include <string>
#include <chrono>

namespace todo {
    class JournalEntry
    {
    public:

        JournalEntry() = default;
        JournalEntry(JournalEntry const& rhs);
        JournalEntry(JournalEntry&& rhs) noexcept;
        JournalEntry(std::chrono::year_month_day date, std::string const& content);
        JournalEntry(long long id, std::chrono::year_month_day date, std::string const& content);

        JournalEntry& operator=(todo::JournalEntry const& other) = default;

        [[nodiscard]] long long getId() const;
        void setId(long long newId);

        [[nodiscard]] std::chrono::year_month_day getDate() const;
        void setDate(std::chrono::year_month_day const& newDate);

        [[nodiscard]] std::string getContent() const;
        void setContent(std::string const& newContent);

        [[nodiscard]] std::string toString() const;
    private:

        long long Id { };
        std::chrono::year_month_day Date { };
        std::string Content { };
    };
}
