#include "Station.h"
#include "Utilities.h"
#include <iomanip>

using namespace std;

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

    Station::Station(const string& str) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_id = ++id_generator;
        m_itemName = util.extractToken(str, next_pos, more);
        m_serialNumber = stoul(util.extractToken(str, next_pos, more));
        m_quantity = stoul(util.extractToken(str, next_pos, more));

        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }

        m_description = util.extractToken(str, next_pos, more);
    }

    const string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            m_quantity--;
        }
    }
    
    void Station::display(ostream& os, bool full) const {
        os << setfill('0') << setw(3) << m_id << setfill(' ') << " | " << left << setw(m_widthField)
            << m_itemName << " | " << setw(6) << right << setfill('0') << m_serialNumber << " | ";

        if (full) {
            os << setw(4) << right << setfill(' ') << m_quantity << " | " << m_description;
        }

        os << endl;
    }
}