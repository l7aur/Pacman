#ifndef PAC_WOMAN_H
#define PAC_WOMAN_H

#include "BaseCharacter.h"

class PacWoman : public BaseCharacter
{
public:
    PacWoman();
    ~PacWoman();
    virtual void updateFrame(const float deltaTime) override;
private:
};

#endif