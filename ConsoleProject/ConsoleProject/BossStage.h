#pragma once
#include "Stage.h"
class BossStage :
    public Stage
{
private:
    int m_spawnTick;

public:
    void Enter(int currentStageIndex) override;
    void Update(float elapsedTime) override;
    void Exit() override;
    bool IsStageComplete(int level)override;

    // 적과 장애물 생성 메서드     
    void GenerateEnemies(vector<vector<shared_ptr<Object>>>& gameObjects);
    void GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameObjects);
    void SpawnItems(vector<vector<shared_ptr<Object>>>& gameObjects);
    bool CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameObjects);
};

