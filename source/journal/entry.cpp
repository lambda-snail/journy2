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

todo::JournalEntry::JournalEntry(int id, wxDateTime date, wxString const& content) : Id{id}, Date{date}, Content(content) {}

todo::JournalEntry::JournalEntry(wxDateTime date, wxString const& content) : Id{-1}, Date{date}, Content(content) {}

wxDateTime todo::JournalEntry::getDate() const
{
    return Date;
}

void todo::JournalEntry::setDate(wxDateTime const& newDate)
{
    if (Date == newDate)
        return;
    Date = newDate;
}

wxString todo::JournalEntry::getContent() const
{
    return Content;
}

void todo::JournalEntry::setContent(wxString const& newContent)
{
    if (Content == newContent)
        return;
    Content = newContent;
}

wxString todo::JournalEntry::toString() const
{
    return Date.FormatDate();
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

