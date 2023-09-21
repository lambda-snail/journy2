#include "ui/themes.h"
#include "ui/markdowneditor.h"
#include "ui/font/iconsmaterialdesign.h"
#include "markdown/Marky.h"
#include "markdown/markdowntovector.h"

#include "imgui.h"
#include "imgui_stdlib.h"

void journy::ui::MarkdownEditor::BuildUi( std::function<void(todo::JournalEntry const&)> const& saveEntry ) {

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

    static auto const& clear_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];
    static auto const& frameBackground = static_cast<ImVec4>(themes::PrimaryColor_100);
    static float const command_bar_height = 32.f;

    ImGui::Begin(entry->toString().c_str(), &bIsOpen, flags);
        ImGui::BeginChild("Command", {0.f, command_bar_height }, false);
            ImVec2 buttonSize = { command_bar_height, command_bar_height };
            // https://github.com/ocornut/imgui/issues/565
            if(ImGui::Button(ICON_MD_EDIT_NOTE, buttonSize)) bEditMode = true;

            ImGui::SameLine();
            if(ImGui::Button(ICON_MD_BOOK, buttonSize))  bEditMode = false;

            ImGui::SameLine();
            if(ImGui::Button(ICON_MD_SAVE, buttonSize))
            {
                saveEntry(*entry);
                bIsDirty = false;
            }
        ImGui::EndChild();

        ImGui::Separator();

        if(bEditMode)
        {
            float width = ImGui::GetWindowWidth() * .5f;

            ImGui::PushStyleColor(ImGuiCol_FrameBg, frameBackground); // Removes red tint of input text
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

        ImGui::BeginChild("Reader", {}, bEditMode);

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

