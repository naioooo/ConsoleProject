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

    //�̱��� ����
    static SceneManager& Instance();

    // �� �߰�
    void AddScene(const string& name, shared_ptr<Scene> scene);

    // �� ��ȯ
    void ChangeScene(const std::string& name);

    // �� ������Ʈ
    void Update(float elapsedTime);
};