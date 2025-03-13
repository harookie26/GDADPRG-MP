#include <iostream>
#include "SFXManager.h"

SFXManager* SFXManager::sharedInstance = nullptr;

/**
 * @brief Get the singleton instance of SFXManager
 *
 * @return SFXManager* The singleton instance
 */
SFXManager* SFXManager::getInstance()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new SFXManager();
    }
    return sharedInstance;
}

/**
 * @brief Load all sound effects
 *
 * Loads a predefined set of sound effects.
 */
void SFXManager::loadAll()
{
    loadSound("effect_1", "Media/Texture/EnemyGunfire.wav");
    loadSound("effect_2", "Media/Texture/Explosion1.wav");
    loadSound("effect_3", "Media/Texture/Explosion2.wav");
    loadSound("effect_4", "Media/Texture/LaunchMissile.wav");
}

/**
 * @brief Load a sound effect from file
 *
 * @param key The key to identify the sound effect
 * @param path The file path to the sound effect
 */
void SFXManager::loadSound(const std::string& key, const std::string& path)
{
    soundMap[key] = path;
}

/**
 * @brief Get the file path for a given sound key
 *
 * @param key The key to identify the sound effect
 * @return std::string The file path associated with the key
 */
std::string SFXManager::getFilePath(const std::string& key)
{
    auto it = soundMap.find(key);
    if (it != soundMap.end())
    {
        return it->second;
    }
    return "";
}

/**
 * @brief Play a sound effect by key
 *
 * @param key The key to identify the sound effect
 */
void SFXManager::playSound(const std::string& key)
{
    std::string path = getFilePath(key);
    if (path.empty())
    {
        std::cout << "Sound not found: " << key << std::endl;
        return;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path))
    {
        std::cout << "Failed to load sound: " << path << std::endl;
        return;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Wait until the sound is finished playing
    while (sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::milliseconds(5));
    }
}
