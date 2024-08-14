#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/modify/GJDropDownLayer.hpp>
#include "../delegates/NextLevel.hpp"
#include "../managers/LastList.hpp"

using namespace geode::prelude;

class $modify(PLGJDropDownLayer, GJDropDownLayer) {
    void exitLayer(CCObject* sender) {
        GameLevelManager::sharedState()->m_levelDownloadDelegate = nullptr;
        GJDropDownLayer::exitLayer(sender);
    }
};

class $modify(PLEndLevelLayer, EndLevelLayer) {
    struct Fields {
        CCMenuItemSpriteExtra* m_button;
        NextLevel m_nextLevelDelegate;
        int m_nextLevelID;
    };

    void customSetup() {
        EndLevelLayer::customSetup();

        if (!LastList::isEmpty() && !m_playLayer->m_level->m_gauntletLevel) {
            const auto glm = GameLevelManager::sharedState();
            m_fields->m_nextLevelDelegate.setCallback([this](GJGameLevel* level, const bool success) {
                if (success) levelDownloadFinished(level);
            });
            glm->m_levelDownloadDelegate = &m_fields->m_nextLevelDelegate;
            createButton();
        }
    }

    void createButton() {
        const auto nextLevel = LastList::getNextLevel(m_playLayer->m_level->m_levelID);
        if (nextLevel == -1) return;

        m_fields->m_nextLevelID = nextLevel;

        const auto s = CCSprite::createWithSpriteFrameName("GJ_plainBtn_001.png");
        const auto s2 = CCSprite::createWithSpriteFrameName("edit_rightBtn2_001.png");
        s2->setPosition(s->getContentSize() / 2);
        s->addChild(s2);
        m_fields->m_button = CCMenuItemSpriteExtra::create(
            s,
            this,
            menu_selector(PLEndLevelLayer::nextLevel)
        );
        m_fields->m_button->setID("next"_spr);
        m_fields->m_button->setPosition({180, -125});
        m_mainLayer->getChildByID("button-menu")->addChild(m_fields->m_button);
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