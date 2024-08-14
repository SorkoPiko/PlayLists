#include <Geode/modify/PauseLayer.hpp>
#include "../delegates/NextLevel.hpp"
#include "../managers/LastList.hpp"

using namespace geode::prelude;

class $modify(PLPauseLayer, PauseLayer) {
    struct Fields {
        CCMenuItemSpriteExtra* m_button;
        GJGameLevel* m_level;
        NextLevel m_nextLevelDelegate;
        int m_nextLevelID;
    };

    void customSetup() {
        PauseLayer::customSetup();
        m_fields->m_level = GameManager::get()->getPlayLayer()->m_level;
        if (!LastList::isEmpty() && !m_fields->m_level->m_gauntletLevel) {
            const auto glm = GameLevelManager::sharedState();
            m_fields->m_nextLevelDelegate.setCallback([this](GJGameLevel* level, const bool success) {
                if (success) levelDownloadFinished(level);
            });
            glm->m_levelDownloadDelegate = &m_fields->m_nextLevelDelegate;
            createButton();
        }
    }

    void createButton() {
        const auto sideMenu = getChildByID("left-button-menu");
        if (!sideMenu) return;

        const auto nextLevel = LastList::getNextLevel(m_fields->m_level->m_levelID);
        if (nextLevel == -1) return;

        m_fields->m_nextLevelID = nextLevel;

        const auto s = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
        const auto s2 = CCSprite::createWithSpriteFrameName("edit_rightBtn2_001.png");
        s2->setPosition(s->getContentSize() / 2);
        s->addChild(s2);
        s->setScale(0.75f);
        m_fields->m_button = CCMenuItemSpriteExtra::create(
            s,
            this,
            menu_selector(PLPauseLayer::nextLevel)
        );
        m_fields->m_button->setID("next"_spr);
        sideMenu->addChild(m_fields->m_button);
        sideMenu->updateLayout();
    }

    void nextLevel(CCObject* sender) {
        if (m_fields->m_nextLevelID != -1) GameLevelManager::sharedState()->downloadLevel(m_fields->m_nextLevelID, false);
    }

    void levelDownloadFinished(GJGameLevel* level) {
        assert(level->m_levelID.value() == m_fields->m_nextLevelID);
        const auto scene = Mod::get()->getSettingValue<bool>("levelInfo") ? LevelInfoLayer::scene(level, false) : PlayLayer::scene(level, false, false);
        CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, scene));
    }
};