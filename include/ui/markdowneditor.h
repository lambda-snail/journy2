#pragma once

#include "journal/entry.h"

namespace journy::ui
{
    class MarkdownEditor
    {
    public:
        explicit MarkdownEditor(todo::JournalEntry* e);

        void BuildUi();
    private:
        todo::JournalEntry* entry;

        bool bIsDirty { false };
        bool bEditMode { false };
    };
}