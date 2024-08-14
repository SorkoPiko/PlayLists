#ifndef NEXTLEVEL_HPP
#define NEXTLEVEL_HPP

using namespace geode::prelude;

class NextLevel : public LevelDownloadDelegate {
public:
    void setCallback(const std::function<void(GJGameLevel*, bool)>& callback);

private:
    void levelDownloadFinished(GJGameLevel *level) override;
    void levelDownloadFailed(int id) override;

    std::function<void(GJGameLevel*, bool)> m_callback;
};

#endif
