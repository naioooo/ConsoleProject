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

    SceneManager() = default;
public: 

    //ΩÃ±€≈Ê ∆–≈œ
    static SceneManager& Instance();

    // æ¿ √ﬂ∞°
    void AddScene(const string& name, shared_ptr<Scene> scene);

    // æ¿ ¿¸»Ø
    void ChangeScene(const std::string& name);

    // æ¿ æ˜µ•¿Ã∆Æ
    void Update(float elapsedTime);
};