#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

static bool s_sent = false;

static void blockTarget() {
    if (s_sent) return;
    int id = static_cast<int>(Mod::get()->getSettingValue<int64_t>("target-id"));
    if (id <= 0) return;
    GameLevelManager::get()->blockUser(id);
    s_sent = true;
}

class $modify(AutoBlockPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        PlayLayer::destroyPlayer(player, object);
        if (Mod::get()->getSettingValue<bool>("on-death")) {
            blockTarget();
        }
    }
};

class $modify(AutoBlockPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();
        if (Mod::get()->getSettingValue<bool>("on-pause")) {
            blockTarget();
        }
    }
};
