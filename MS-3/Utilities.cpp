#include "Utilities.h"

using namespace std;

namespace sdds
{
    char Utilities::m_delimiter = ',';

    Utilities::Utilities() : m_widthField(1) {}

    std::string Utilities::trim(const std::string& str) const {
        size_t firstNonSpace = str.find_first_not_of(" \t");
        size_t lastNonSpace = str.find_last_not_of(" \t");
        if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
            return str.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        }
        return "";
    }

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    void Utilities::setDelimiter(const char delimiter) {
        m_delimiter = delimiter;
    }

    const char Utilities::getDelimiter() {
        return m_delimiter;
    }

    const string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        string token = "";
        size_t startPos = next_pos;
        size_t endPos = str.find(m_delimiter, next_pos);

        if (endPos == next_pos) {
            more = false;
            throw "Delimiter found at next_pos.";
        }
        
        if (endPos == string::npos) {
            token = str.substr(startPos);
            next_pos = str.length();
            more = false;
        }
        else {
            token = str.substr(startPos, endPos - startPos);
            next_pos = endPos + 1;
            more = true;
        }
        token = trim(token);
        if (token.length() > m_widthField) {
            setFieldWidth(token.length());
        }

        return token;
    }
}