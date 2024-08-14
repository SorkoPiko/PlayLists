#include "NextLevel.hpp"

using namespace geode::prelude;

void NextLevel::setCallback(const std::function<void(GJGameLevel*, bool)>& callback) {
    m_callback = callback;
}

void NextLevel::levelDownloadFinished(GJGameLevel *level) {
    m_callback(level, true);
}

void NextLevel::levelDownloadFailed(int id) {
    m_callback(nullptr, false);
}