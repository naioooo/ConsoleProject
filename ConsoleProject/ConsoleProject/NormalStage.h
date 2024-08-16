#pragma once
#include "Stage.h"
class NormalStage :
    public Stage
{
private:
    int m_spawn_tick;

public:
    void Enter() override;
    void Update(float elapsedTime) override;
    void Exit() override;

    // 적과 장애물 생성 메서드
    void SpawnEnemies(vector<vector<shared_ptr<Object>>>& gameobjects);
    void GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameobjects);
    bool CollisionObject(Point point, vector<vector<shared_ptr<Object>>>& gameobjects);
    bool IsStageComplete(int level)override;
};

