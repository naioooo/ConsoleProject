#pragma once
#include "Library.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndingScene.h"

class SceneManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene;

public: 
    SceneManager();

    //ΩÃ±€≈Ê ∆–≈œ
    static SceneManager& Instance();
    void AddScene(const string& name, shared_ptr<Scene> scene);
    void ChangeScene(const std::string& name);
    void Update(float elapsedTime);
};