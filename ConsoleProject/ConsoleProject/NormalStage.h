#pragma once
#include "Stage.h"
class NormalStage :
    public Stage
{
private:
    int m_spawnTick;

public:
    void Enter() override;
    void Update(float elapsedTime) override;
    void Exit() override; 
    bool IsStageComplete(int level) override;

    // ���� ��ֹ� ���� �޼���
    void SpawnEnemies(vector<vector<shared_ptr<Object>>>& gameobjects);
    void GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameobjects);
    bool CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameobjects);
};

