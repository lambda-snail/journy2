#include "ui/themes.h"
#include "ui/markdowneditor.h"
#include "ui/font/iconsmaterialdesign.h"
#include "markdown/Marky.h"
#include "markdown/markdowntovector.h"

#include "imgui.h"
#include "imgui_stdlib.h"

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

    auto const& clear_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];
    float const command_bar_height = 32.f;

    ImGui::Begin(entry->toString().c_str(), &bIsOpen, flags);

        ImGui::BeginChild("Command", {0.f, command_bar_height }, false);
            // https://github.com/ocornut/imgui/issues/565
            if(ImGui::Button(ICON_MD_EDIT_NOTE)) bEditMode = true;

            ImGui::SameLine();

            if(ImGui::Button("Read"))  bEditMode = false;
        ImGui::EndChild();

        if(bEditMode)
        {
            float width = ImGui::GetWindowWidth() * .5f;

            ImGui::PushStyleColor(ImGuiCol_FrameBg, static_cast<ImVec4>(themes::PrimaryColor_100)); // Removes red tint of input text
            ImGui::BeginChild("Writer", { width, 0.f }, true);

            // If content is dirty, do not reset when no further change
            bIsDirty |= ImGui::InputTextMultiline("Markdown",
                                      &entry->getContent(),
                                      { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y },
                                      ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackAlways
                                  );

            ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::SameLine();
        }

        ImGui::BeginChild("Reader", {}, true);

            ImDrawList* draw = ImGui::GetWindowDrawList();

            journy::markdown::MarkdownToVector backend(draw, clear_color);

            marky::Marky marky;
            marky.process_markdown(&backend, entry->getContent());

        ImGui::EndChild();


    ImGui::End();
}

journy::ui::MarkdownEditor::MarkdownEditor(todo::JournalEntry *e) : entry { e }{}

bool journy::ui::MarkdownEditor::IsOpen() const {
    return bIsOpen;
}

void journy::ui::MarkdownEditor::SetOpen(bool isOpen) {
    bIsOpen = isOpen;
}

void journy::ui::MarkdownEditor::SetFocusNextPass() {
    bShouldFocusNextPass = true;
}

