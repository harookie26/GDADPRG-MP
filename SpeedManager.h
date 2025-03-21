#pragma once

class SpeedManager
{
public:
    static SpeedManager* getInstance();
    void update(float deltaTime);
    float getSpeedMultiplier() const;

private:
    SpeedManager();
    static SpeedManager* instance;
    float speedMultiplier;
    float incrementRate;
};
