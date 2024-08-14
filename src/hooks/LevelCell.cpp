#include <Geode/modify/LevelCell.hpp>
#include "../managers/LastList.hpp"

using namespace geode::prelude;

class $modify(PLLevelCell, LevelCell) {
    void onClick(CCObject* sender) {
        for (const auto children = CCArrayExt<CCNode*>(CCScene::get()->getChildren()); const auto child: children) {
            if (const auto layer = typeinfo_cast<LevelListLayer*>(child)) {
                LastList::setLastList(layer->m_levelList->m_levels);
                break;
            }
            LastList::setLastList({});
        }
        LevelCell::onClick(sender);
    }
};