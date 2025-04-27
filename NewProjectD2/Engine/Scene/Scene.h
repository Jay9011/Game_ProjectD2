#pragma once
#include "GameObjects/GameObject.h"

namespace Engine
{
    class Scene
    {
    public:
        Scene();
        virtual ~Scene();

    public:
        void Update(float deltaTime);
        void Render();

    public:
        GameObject* SpawnGameObject(unique_ptr<GameObject> gameObject);

    private:
        bool isPaused;
        float timeDilation;

        vector<unique_ptr<GameObject>> gameObjects;
        

    ///////////////////////////////////////////////////////////////
    /// Getter & Setter
    ///////////////////////////////////////////////////////////////
    public:
        bool IsPaused() const { return isPaused; }
        void SetPaused(bool paused) { isPaused = paused; }

        float GetTimeDilation() const { return timeDilation; }
        void SetTimeDilation(float timeDilation) { this->timeDilation = timeDilation; }
    };
}

