#include "StageManager.h"

StageManager::StageManager() : currentStageIndex(0)
{
    stages.push_back(std::make_unique<NormalStage>());
    stages.push_back(std::make_unique<NormalStage>());
    stages.push_back(std::make_unique<NormalStage>());
    stages.push_back(std::make_unique<BossStage>());  
}

void StageManager::EnterStage()
{
    if (currentStageIndex < stages.size()) 
    {
        stages[currentStageIndex]->Enter();
    }
}

void StageManager::UpdateStage(float elapsedTime)
{
    if (currentStageIndex < stages.size())
    {
        stages[currentStageIndex]->Update(elapsedTime);
        if (stages[currentStageIndex]->IsStageComplete(currentStageIndex + 1))
        {
            NextStage();
        }
    }
}

void StageManager::ExitStage()
{
    if (currentStageIndex < stages.size())
    {
        stages[currentStageIndex]->Exit();
    }
}

void StageManager::NextStage()
{
    if (currentStageIndex < stages.size())
    {
        ExitStage();
        currentStageIndex++;
        EnterStage();
    }
}

Stage* StageManager::GetCurrentStage()
{
    if (currentStageIndex < stages.size()) 
    {
        return stages[currentStageIndex].get();
    }
    return nullptr;
}

size_t StageManager::GetCurrentStageIndex() const
{
    return currentStageIndex;
}

size_t StageManager::GetStagesSize()  const
{
    return stages.size();
}
