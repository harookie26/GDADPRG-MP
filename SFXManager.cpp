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
    loadSound("explosion", "Media/Textures/explosion_sound.wav"); // source: https://creatorassets.com/a/8bit-explosion-sound-effects
    loadSound("firing", "Media/Textures/projectile_sfx.wav"); // source: https://creatorassets.com/a/8-bit-powerup-sound-effects

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
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path))
    {
        soundBuffers[key] = buffer;
    }
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
    /*std::string path = getFilePath(key);
    if (path.empty())
    {
        std::cout << "Sound not found: " << key << std::endl;
        return;
    }*/

    /*sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path))
    {
        std::cout << "Failed to load sound: " << path << std::endl;
        return;
    }*/

    /*sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();*/

    auto bufferIt = soundBuffers.find(key);
    if (bufferIt == soundBuffers.end())
    {
        std::cout << "Sound not found: " << key << std::endl;
        return;
    }
    //std::string activeSoundKey = key + std::to_string(activeSounds.size());  
   
    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(bufferIt->second);
    sound->play();
    
    activeSounds.push_back(std::move(sound));

    

    /*activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(), [](const sf::Sound& s) {
            return s.getStatus() == sf::Sound::Stopped;
            }),
        activeSounds.end()
    );*/
}
