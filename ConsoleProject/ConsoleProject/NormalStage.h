#pragma once
#include "Stage.h"
class NormalStage :
    public Stage
{
private:
    int m_spawnTick;
    int m_level;

public:
    void Enter(int currentStageIndex) override;
    void Update(float elapsedTime) override;
    void Exit() override; 
    bool IsStageComplete(int level) override;

    void SpawnEnemies(vector<vector<shared_ptr<Object>>>& gameObjects);
    void GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameObjects);
    bool CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameObjects);
};

