#pragma once
#include "BossStage.h"
#include "NormalStage.h"

class StageManager
{
private:
    std::vector<std::unique_ptr<Stage>> stages;
    size_t currentStageIndex;

public:
    StageManager();

    void EnterStage();
    void UpdateStage(float elapsedTime);
    void ExitStage();
    void NextStage();

    size_t GetCurrentStageIndex() const;
    size_t GetStagesSize() const;
};

