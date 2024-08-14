#include "LastList.hpp"

std::vector<int> LastList::m_lastList = {};

void LastList::setLastList(const std::vector<int> &list) {
    m_lastList = list;
}

bool LastList::isEmpty() {
    return m_lastList.empty();
}

int LastList::getNextLevel(const int id) {
    if (const auto it = std::find(m_lastList.begin(), m_lastList.end(), id); it != m_lastList.end() && std::next(it) != m_lastList.end()) {
        return *std::next(it);
    }
    return -1;
}

