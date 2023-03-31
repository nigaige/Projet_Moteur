#pragma once

class Player : public Component
{

public:

    float z = 0.f;
    
    float roll = 0.f;
    
    Player();
    ~Player();

    void update();
};
