#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

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
};

