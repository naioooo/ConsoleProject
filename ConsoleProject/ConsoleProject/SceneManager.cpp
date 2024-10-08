#include "SceneManager.h"


SceneManager::SceneManager()
{
    AddScene("Title", std::make_shared<TitleScene>());
    AddScene("Game", std::make_shared<GameScene>());
    AddScene("Ending", std::make_shared<EndingScene>());

    ChangeScene("Title");
}

SceneManager& SceneManager::Instance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::AddScene(const string& name, shared_ptr<Scene> scene)
{
    scenes[name] = scene;
}

void SceneManager::ChangeScene(const string& name)
{
    if (scenes.find(name) != scenes.end())
    {
        if (currentScene)
        {
            currentScene->Exit();
        }
        currentScene = scenes[name];
        currentScene->Enter();
    }
    else 
    {
        std::cout << "Scene not found: " << name << std::endl;
    }
}

// �� ������Ʈ
void SceneManager::Update(float elapsedTime)
{
    if (currentScene) 
    {
        currentScene->Update(elapsedTime);
    }
}