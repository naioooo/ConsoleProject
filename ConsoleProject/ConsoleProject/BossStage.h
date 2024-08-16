#pragma once
#include "Stage.h"
class BossStage :
    public Stage
{
public:
    void Enter() override;
    void Update(float elapsedTime) override;
    void Exit() override;
    bool IsStageComplete(int level) override; // 조건 체크 메서드

    // 적과 장애물 생성 메서드
    void SpawnEnemies();
    void GenerateObstacles();
};

