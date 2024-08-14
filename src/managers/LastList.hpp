#ifndef LASTLIST_HPP
#define LASTLIST_HPP

using namespace geode::prelude;

class LastList {
protected:
    static std::vector<int> m_lastList;

public:
    static void setLastList(const std::vector<int> &);
    static bool isEmpty();
    static int getNextLevel(int id);
};

#endif
