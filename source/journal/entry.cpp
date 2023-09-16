#include "journal/entry.h"

todo::JournalEntry::JournalEntry(const JournalEntry &rhs)
{
    Id = rhs.Id;
    Date = rhs.Date;
    Content = rhs.Content;
}

todo::JournalEntry::JournalEntry(JournalEntry&& rhs) noexcept
{
    Id = rhs.Id;
    Date = rhs.Date;
    Content = rhs.Content;
}

todo::JournalEntry::JournalEntry(long long id, std::chrono::year_month_day date, std::string const& content) : Id{id}, Date{date}, Content(content) {}

todo::JournalEntry::JournalEntry(std::chrono::year_month_day date, std::string const& content) : Id{-1}, Date{date}, Content(content) {}

std::chrono::year_month_day todo::JournalEntry::getDate() const
{
    return Date;
}

void todo::JournalEntry::setDate(std::chrono::year_month_day const& newDate)
{
    if (Date == newDate)
        return;
    Date = newDate;
}

std::string todo::JournalEntry::getContent() const
{
    return Content;
}

void todo::JournalEntry::setContent(std::string const& newContent)
{
    if (Content == newContent)
        return;
    Content = newContent;
}

std::string todo::JournalEntry::toString() const
{
    return std::format("{}", Date);
}

long long todo::JournalEntry::getId() const
{
    return Id;
}


void todo::JournalEntry::setId(long long newId)
{
    if (Id == newId)
        return;
    Id = newId;
}

