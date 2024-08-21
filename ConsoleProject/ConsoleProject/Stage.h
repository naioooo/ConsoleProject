#pragma once
#include "library.h"
#include "Player.h"
#include "Monster.h"

class Stage
{
private:

public:
    virtual ~Stage() = default;
    virtual void Enter(int currentStageIndex) = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Exit() = 0;
    virtual bool IsStageComplete(int level) = 0; // 조건 체크 메서드
};

