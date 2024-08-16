#pragma once
#include "Stage.h"
class BossStage :
    public Stage
{
public:
    void Enter() override;
    void Update(float elapsedTime) override;
    void Exit() override;
    bool IsStageComplete(int level) override; // ���� üũ �޼���

    // ���� ��ֹ� ���� �޼���
    void SpawnEnemies();
    void GenerateObstacles();
};

