#include "imgui.h"

#include "ui/markdowneditor.h"
#include "markdown/Marky.h"
#include "markdown/markdowntovector.h"

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

        ImGui::BeginChild("Command", { 0.f, 32.f }, false);
            if(ImGui::Button("Edit")) bEditMode = true;

            ImGui::SameLine();

            if(ImGui::Button("Read"))  bEditMode = false;
        ImGui::EndChild();

        if(bEditMode)
        {
            ImGui::BeginChild("Writer", { ImGui::GetWindowWidth() * .5f, 0.f }, true);
            ImGui::TextUnformatted("Writing some stuff!");
            ImGui::EndChild();

            ImGui::SameLine();
        }

        ImGui::BeginChild("Reader", {}, true);

            ImDrawList* draw = ImGui::GetWindowDrawList();

            auto const& clear_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];

            journy::markdown::MarkdownToVector backend(draw, clear_color);

            marky::Marky marky;
            marky.process_markdown(&backend, entry->getContent());

            //ImGui::TextUnformatted(entry->getContent().c_str());

        ImGui::EndChild();


    ImGui::End();
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

