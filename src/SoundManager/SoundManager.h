#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>
#include <mutex>
#include "../Observer/IObserver.h"
#include "../Event/EventManager.h"
#include "../Event/StateChangeEvent.h"
#include "../Event/BackEvent.h"
#include "../Model/GameData.h"
#include "../Model/Item/ItemData.h"
#include "../Event/ItemTouchedEvent.h"
#include "../Event/BlockChangeEvent.h"

class SoundManager : public IObserver, public std::enable_shared_from_this<SoundManager>
{
private:
    static std::shared_ptr<SoundManager> instance;
    static std::mutex instanceMutex;

    std::unordered_map<std::string, Sound> sounds;
    Music backgroundMusic;
    float volume;

    SoundManager();

public:
    ~SoundManager();

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static std::shared_ptr<SoundManager> getInstance();

    void update(std::shared_ptr<Event> event) override;

    void Init();
    void Update();

    void LoadSoundFile(const std::string& id, const std::string& filepath);
    void LoadBackgroundMusic(const std::string& filepath);

    void PlaySoundEffect(const std::string& id);
    void PlayBackgroundMusic();
    void StopBackgroundMusic();

    void IncreaseVolume(float amount);
    void DecreaseVolume(float amount);
    void SetVolume(float newVolume);
    float GetVolume() const;
};