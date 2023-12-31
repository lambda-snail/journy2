#pragma once

#include <functional>

#include "journal/entry.h"

namespace journy::ui
{
    class MarkdownEditor
    {
    public:
        explicit MarkdownEditor(todo::JournalEntry* e, ImGuiID dock);

        void SetOpen(bool isOpen);
        [[nodiscard]] bool IsOpen() const;

        void SetFocusNextPass();
        [[nodiscard]] std::string GetName() const;

        void BuildUi( std::function<void(todo::JournalEntry const&)> const& saveEntry );
    private:
        todo::JournalEntry* entry;

        bool bIsDirty { false };
        bool bEditMode { false };
        bool bOutlineMode { false };
        bool bIsOpen { true };
        bool bShouldFocusNextPass { false };

        bool bIsDockingInitialized { false };
        ImGuiID entryDock;
    };
}