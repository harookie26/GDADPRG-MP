#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>


class SFXManager
{
public:
    static SFXManager* getInstance();
    void loadAll();
    void loadSound(const std::string& key, const std::string& path);
    void playSound(const std::string& key);

private:
    SFXManager() = default;
    std::string getFilePath(const std::string& key);

    static SFXManager* sharedInstance;
    std::unordered_map<std::string, std::string> soundMap;
    //std::vector<sf::Sound> activeSounds; 
    std::vector<std::unique_ptr<sf::Sound>> activeSounds;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    
};

