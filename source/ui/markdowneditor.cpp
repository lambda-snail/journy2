#include "ui/themes.h"
#include "ui/markdowneditor.h"
#include "ui/font/iconsmaterialdesign.h"
#include "markdown/Marky.h"
#include "markdown/markdowntovector.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "ui/imguiextensions.h"

void journy::ui::MarkdownEditor::BuildUi(std::function<void(todo::JournalEntry const &)> const &saveEntry) {

    if (not bIsOpen) {
        return;
    }

    int flags = ImGuiWindowFlags_None;
    if (bIsDirty) {
        flags = flags | ImGuiWindowFlags_UnsavedDocument;
    }

    if (bShouldFocusNextPass) {
        ImGui::SetNextWindowFocus();
        bShouldFocusNextPass = false;
    }

    std::vector<journy::markdown::MarkdownOutlineDescriptor> const *outline = nullptr;

    auto scale = journy::ui::GetDpiScaleFactor();
    static auto const &clear_color = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];
    static auto const &frameBackground = static_cast<ImVec4>(themes::PrimaryColor_100);
    static float const command_bar_height = 32.f * scale;

    // Dock in the center of the viewport when first opening the window.
    if (not bIsDockingInitialized) {
        ImGui::SetNextWindowDockID(entryDock, ImGuiCond_Always);
        bIsDockingInitialized = true;
    }

    ImGui::Begin(GetName().c_str(), &bIsOpen, flags);
    ImGui::BeginChild("Command", {0.f, command_bar_height}, false);
    ImVec2 buttonSize = {command_bar_height, command_bar_height};
    // https://github.com/ocornut/imgui/issues/565
    if (ImGui::Button(ICON_MD_EDIT_NOTE, buttonSize)) {
        bEditMode = true;
        bOutlineMode = false;
    }
    journy::ui::AddTooltipWithDelay("Enter edit mode to make changes to your entry", journy::ui::TooltipDelay::Normal);

    ImGui::SameLine();
    if (ImGui::Button(ICON_MD_BOOK, buttonSize)) {
        bEditMode = false;
    }
    journy::ui::AddTooltipWithDelay("Enter read mode to focus on the content of your entry",
                                    journy::ui::TooltipDelay::Normal);

    ImGui::SameLine();
    if (ImGui::Button(ICON_MD_SAVE, buttonSize)) {
        saveEntry(*entry);
        bIsDirty = false;
    }
    journy::ui::AddTooltipWithDelay("Save the entry content to the database", journy::ui::TooltipDelay::Normal);

    ImGui::SameLine();
    if (ImGui::Button(ICON_MD_FORMAT_LIST_NUMBERED, buttonSize)) {
        bOutlineMode = not bOutlineMode;
    }
    journy::ui::AddTooltipWithDelay("Show an outline of the entire entry", journy::ui::TooltipDelay::Normal);
    ImGui::EndChild();

    ImGui::Separator();

    if (bEditMode) {
        float width = ImGui::GetWindowWidth() * .5f;

        ImGui::PushStyleColor(ImGuiCol_FrameBg, frameBackground); // Removes red tint of input text
        ImGui::BeginChild("Writer", {width, 0.f}, true);

        // If content is dirty, do not reset when no further change
        bIsDirty |= ImGui::InputTextMultiline("Markdown",
                                              &entry->getContent(),
                                              {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y},
                                              ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackAlways
        );

        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::SameLine();
    }

    ImGui::BeginChild("Reader", {}, bEditMode);

    ImDrawList *draw = ImGui::GetWindowDrawList();

    journy::markdown::MarkdownToVector backend(draw, clear_color);

    marky::Marky marky;
    marky.process_markdown(&backend, entry->getContent());

    outline = backend.GetOutline();
    ImGui::EndChild();
    ImGui::End();

    if (bOutlineMode) {
        ImGui::Begin("Outline", &bOutlineMode);
        if (ImGui::TreeNode(entry->toString().c_str())) {
            // This can probably be done more efficiently ...
            static int space_per_indent = 4;
            for (auto const &header: *outline) {
                auto indent = std::string(header.level * space_per_indent, ' ');
                ImGui::Text("%s %s", indent.c_str(), header.header.c_str());
            }
            ImGui::TreePop();
        }
        ImGui::End();
    }
}

journy::ui::MarkdownEditor::MarkdownEditor(todo::JournalEntry *e, ImGuiID dock) : entry{e}, entryDock{dock} {}

bool journy::ui::MarkdownEditor::IsOpen() const {
    return bIsOpen;
}

void journy::ui::MarkdownEditor::SetOpen(bool isOpen) {
    bIsOpen = isOpen;
}

void journy::ui::MarkdownEditor::SetFocusNextPass() {
    bShouldFocusNextPass = true;
}

std::string journy::ui::MarkdownEditor::GetName() const {
    return entry->toString();
}

