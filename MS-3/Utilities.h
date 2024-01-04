#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
#include <string>
#include<fstream>

namespace sdds
{
	class Utilities
	{
        size_t m_widthField;
        static char m_delimiter;
        std::string trim(const std::string& str) const;

    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(const char delimiter);
        static const char getDelimiter();
	};
}
#endif