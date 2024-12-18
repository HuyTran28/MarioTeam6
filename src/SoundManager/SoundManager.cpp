#include "SoundManager.h"

std::shared_ptr<SoundManager> SoundManager::instance = nullptr;
std::mutex SoundManager::instanceMutex;

void SoundManager::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		UpdateMusicStream(backgroundMusic);
	}
    else if (event->getType() == "State Change Event")
    {
        if (GameData::getInstance().getLastState() == "Pause")
        {
            PlayMusicStream(backgroundMusic);
			SeekMusicStream(backgroundMusic, GetMusicTimePlayed(backgroundMusic));
        }
        auto stateChangeEvent = std::dynamic_pointer_cast<StateChangeEvent>(event);
        if (stateChangeEvent->getNewState() == "Pause")
        {
            PlaySoundEffect("Pause");
			PauseMusicStream(backgroundMusic); 
        }
    }
    else if (event->getType() == "Back Event")
    {
        if (GameData::getInstance().getLastState() == "Pause")
        {
			PlayMusicStream(backgroundMusic);
            SeekMusicStream(backgroundMusic, GetMusicTimePlayed(backgroundMusic));
        }
    }
    else if (event->getType() == "Jump Event")
    {
        PlaySoundEffect("Jump");
    }
	else if (event->getType() == "Item Touched Event")
	{
		auto itemTouchedEvent = std::dynamic_pointer_cast<ItemTouchedEvent>(event);
		if (itemTouchedEvent->getObjectType() == "Item-Coin")
		{
			PlaySoundEffect("Coin");
		}
		else if (itemTouchedEvent->getObjectType() == "Item-RedMushroom")
		{
			PlaySoundEffect("Power Up");
		}
	}
	else if (event->getType() == "Block Change Event")
	{
		auto blockChangeEvent = std::dynamic_pointer_cast<BlockChangeEvent>(event);
		if (blockChangeEvent->getNew() == nullptr)
		{
			PlaySoundEffect("Block Break");
		}
        if (blockChangeEvent->getPreType() == "Block-Question")
		{
			PlaySoundEffect("ItemAppear");
		}
	}
	else if (event->getType() == "Die Event")
	{
		PlaySoundEffect("Die");
	}
	else if (event->getType() == "Vine Event")
	{
		PlaySoundEffect("Vine");
	}
	else if (event->getType() == "Warp Event")
	{
		PlaySoundEffect("Warp");
	}
	else if (event->getType() == "Regenerate Event")
	{
		PlaySoundEffect("Regerate");
	}

}

void SoundManager::LoadSoundFile(const std::string& id, const std::string& filepath) {
    Sound sound = LoadSound(filepath.c_str());
    sounds[id] = sound;
}

SoundManager::SoundManager()
{
	volume = 1.0f; //Full volume

    InitAudioDevice();
    LoadBackgroundMusic("../../Assets/Sounds/music.mp3");
	PlayMusicStream(backgroundMusic);

    LoadSoundFile("Coin", "../../Assets/Sounds/Coin.wav");
    LoadSoundFile("Pause", "../../Assets/Sounds/Pause.wav");
    LoadSoundFile("Jump", "../../Assets/Sounds/Jump.wav");
	LoadSoundFile("Block Break", "../../Assets/Sounds/Break.wav");
	LoadSoundFile("Power Up", "../../Assets/Sounds/PowerUp.mp3");
	LoadSoundFile("Die", "../../Assets/Sounds/Die.wav");
	LoadSoundFile("Vine", "../../Assets/Sounds/Vine.wav");
	LoadSoundFile("Warp", "../../Assets/Sounds/Warp.wav");
	LoadSoundFile("ItemAppear", "../../Assets/Sounds/Item.wav");
	LoadSoundFile("Regerate", "../../Assets/Sounds/1up.wav");
}

std::shared_ptr<SoundManager> SoundManager::getInstance()
{
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance) {
        instance = std::shared_ptr<SoundManager>(new SoundManager());
        EventManager::getInstance().addObserver(instance);
    }
    return instance;
}

SoundManager::~SoundManager() {
    for (auto& sound : sounds) {
        UnloadSound(sound.second);
    }
    UnloadMusicStream(backgroundMusic);
}

void SoundManager::LoadBackgroundMusic(const std::string& filepath)
{
    backgroundMusic = LoadMusicStream(filepath.c_str());
}

void SoundManager::PlaySoundEffect(const std::string& id)
{
    if (sounds.find(id) != sounds.end())
    {
        PlaySound(sounds[id]);
    }
}

void SoundManager::PlayBackgroundMusic()
{
    PlayMusicStream(backgroundMusic);
}

void SoundManager::StopBackgroundMusic()
{
    StopMusicStream(backgroundMusic);
}

void SoundManager::IncreaseVolume(float amount)
{
    volume += amount;
    if (volume > 1.0f) volume = 1.0f;
    SetVolume(volume);
}

void SoundManager::DecreaseVolume(float amount)
{
    volume -= amount;
    if (volume < 0.0f) volume = 0.0f;
    SetVolume(volume);
}

void SoundManager::SetVolume(float newVolume)
{
    volume = newVolume;
    for (auto& sound : sounds) {
        SetSoundVolume(sound.second, volume);
    }
    SetMusicVolume(backgroundMusic, volume);
}

float SoundManager::GetVolume() const
{
    return volume;
}