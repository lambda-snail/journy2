#pragma once

#include "journal/entry.h"

namespace journy::ui
{
    class MarkdownEditor
    {
    public:
        explicit MarkdownEditor(todo::JournalEntry* e);

        void SetOpen(bool isOpen);
        [[nodiscard]] bool IsOpen() const;

        void SetFocusNextPass();

        void BuildUi();
    private:
        todo::JournalEntry* entry;

        bool bIsDirty { false };
        bool bEditMode { false };
        bool bIsOpen { true };
        bool bShouldFocusNextPass { false };
    };
}