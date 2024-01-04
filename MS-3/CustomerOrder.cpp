#include "CustomerOrder.h"

#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities utility;
        size_t npos{};
        bool more{ true };

        m_name = utility.extractToken(str, npos, more);
        m_product = utility.extractToken(str, npos, more);
        m_cntItem = count(str.begin(), str.end(), Utilities::getDelimiter()) - 1;

        std::vector<Item*> itemsList;
        do {
            itemsList.push_back(new Item(utility.extractToken(str, npos, more)));
        } while (more);

        m_lstItem = new Item * [m_cntItem];

        size_t i{};
        std::for_each(itemsList.begin(), itemsList.end(), [&](Item* item) {
            m_lstItem[i] = item;
            i++;
            });

        m_widthField = std::max(utility.getFieldWidth(), m_widthField);
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_cntItem = 0;
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept : CustomerOrder() {
        *this = std::move(other);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_cntItem; i++) delete m_lstItem[i];
            delete[] m_lstItem;
            m_name = other.m_name;
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_name = "";
            other.m_product = "";
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }

        return *this;
    }

    bool CustomerOrder::isOrderFilled() const {
        return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [](const Item* item) {
            return item->m_isFilled;
            });
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](Item* it) {
            if (it->m_itemName == itemName) return (it->m_isFilled);

            return true;
            });
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](Item* item) {
            os << "[" << std::setfill('0') << std::setw(6) << std::right << item->m_serialNumber << "] " << setfill(' ') << std::setw(m_widthField) << std::left <<item->m_itemName
                << " - ";
            if (item->m_isFilled)
                os << "FILLED";
            else
                os << "TO BE FILLED";
            os << std::endl;
            });
    }
}