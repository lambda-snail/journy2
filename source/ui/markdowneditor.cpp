#include "imgui.h"

#include "ui/markdowneditor.h"

void journy::ui::MarkdownEditor::BuildUi() {

    ImGui::Begin(entry->toString().c_str());

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

