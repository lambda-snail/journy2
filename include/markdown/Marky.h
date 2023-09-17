#pragma once

#include <string>

namespace marky {
    class MarkdownListener;

    class Marky {
    public:
        void process_markdown(MarkdownListener* backend, std::string_view markdown) const;
    };
}