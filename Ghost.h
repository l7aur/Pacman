#ifndef GHOST_H
#define GHOST_H

#include "BaseCharacter.h"

class Ghost : public BaseCharacter
{
public:
    Ghost();
    ~Ghost();
    virtual void updateFrame(const float deltaTime) override;
    Vector2 createRandomDisplacement();
private:
};

#endif