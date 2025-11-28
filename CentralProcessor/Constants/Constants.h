#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <regex>

namespace colours {
    const std::string RESET       = "\033[0m";   // Reset
    const std::string BLACK       = "\033[30m";  // Black
    const std::string RED         = "\033[31m";  // Red
    const std::string GREEN       = "\033[32m";  // Green
    const std::string YELLOW      = "\033[33m";  // Yellow
    const std::string BLUE        = "\033[34m";  // Blue
    const std::string MAGENTA     = "\033[35m";  // Magenta
    const std::string CYAN        = "\033[36m";  // Cyan
    const std::string WHITE       = "\033[37m";  // White

    // Bright Text Colors
    const std::string BRIGHT_BLACK = "\033[90m"; // Bright Black (Gray)
    const std::string BRIGHT_RED   = "\033[91m"; // Bright Red
    const std::string BRIGHT_GREEN = "\033[92m"; // Bright Green
    const std::string BRIGHT_YELLOW= "\033[93m"; // Bright Yellow
    const std::string BRIGHT_BLUE  = "\033[94m"; // Bright Blue
    const std::string BRIGHT_MAGENTA= "\033[95m"; // Bright Magenta
    const std::string BRIGHT_CYAN  = "\033[96m"; // Bright Cyan
    const std::string BRIGHT_WHITE = "\033[97m"; // Bright White

    // Background Colors
    const std::string BG_BLACK     = "\033[40m";  // Black Background
    const std::string BG_RED       = "\033[41m";  // Red Background
    const std::string BG_GREEN     = "\033[42m";  // Green Background
    const std::string BG_YELLOW    = "\033[43m";  // Yellow Background
    const std::string BG_BLUE      = "\033[44m";  // Blue Background
    const std::string BG_MAGENTA   = "\033[45m";  // Magenta Background
    const std::string BG_CYAN      = "\033[46m";  // Cyan Background
    const std::string BG_WHITE     = "\033[47m";  // White Background

    // Bright Background Colors
    const std::string BG_BRIGHT_BLACK = "\033[100m"; // Bright Black (Gray) Background
    const std::string BG_BRIGHT_RED   = "\033[101m"; // Bright Red Background
    const std::string BG_BRIGHT_GREEN = "\033[102m"; // Bright Green Background
    const std::string BG_BRIGHT_YELLOW= "\033[103m"; // Bright Yellow Background
    const std::string BG_BRIGHT_BLUE  = "\033[104m"; // Bright Blue Background
    const std::string BG_BRIGHT_MAGENTA= "\033[105m"; // Bright Magenta Background
    const std::string BG_BRIGHT_CYAN  = "\033[106m"; // Bright Cyan Background
    const std::string BG_BRIGHT_WHITE = "\033[107m"; // Bright White Background

    // Text Attributes
    const std::string BOLD        = "\033[1m";   // Bold
    const std::string UNDERLINE   = "\033[4m";   // Underline
    const std::string REVERSED    = "\033[7m";   // Reversed
}

namespace patterns {
    const std::regex spaceLinePattern("(^\\s*$)");
    const std::regex filenamePattern(".*\\.s$");
    const std::regex variableLinePattern("(^\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s+db\\s+(-?\\d+(\\.\\d+)?)\\s*$)");
    const std::regex sectionPattern("^section +\\.[a-z]+\\s*$");
    const std::regex lablePattern("^[a-z]+:\\s*$");
    const std::regex commandPattern("^\\s*(mov|mult|jmp|add) +([a-zA-Z_][a-zA-Z0-9_]*) *, *(\\d+(\\.\\d+)?|[a-zA-Z_][a-zA-Z0-9_]*\\s*)$");
    const std::regex sectionDataPattern("(^\\s*section\\s+\\.data\\s*$)");
    const std::regex startPattern("(^\\s*_start:\\s*$)");
}

#endif