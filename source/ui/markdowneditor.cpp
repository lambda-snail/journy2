#include "imgui.h"

#include "ui/markdowneditor.h"

void journy::ui::MarkdownEditor::BuildUi() {

    if(not bIsOpen)
    {
        return;
    }

    int flags = ImGuiWindowFlags_None;
    if(bIsDirty)
    {
        flags = flags | ImGuiWindowFlags_UnsavedDocument;
    }

    if(bShouldFocusNextPass)
    {
        ImGui::SetNextWindowFocus();
        bShouldFocusNextPass = false;
    }

    ImGui::Begin(entry->toString().c_str(), &bIsOpen, flags);

        ImGui::BeginChild("Reader");

            ImGui::TextUnformatted(entry->getContent().c_str());

        ImGui::EndChild();

    ImGui::End();

    if(bEditMode)
    {
        ImGui::SameLine();
    }
}

journy::ui::MarkdownEditor::MarkdownEditor(todo::JournalEntry *e) : entry { e } {}

bool journy::ui::MarkdownEditor::IsOpen() const {
    return bIsOpen;
}

void journy::ui::MarkdownEditor::SetOpen(bool isOpen) {
    bIsOpen = isOpen;
}

void journy::ui::MarkdownEditor::SetFocusNextPass() {
    bShouldFocusNextPass = true;
}

