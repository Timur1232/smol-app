#pragma once

#include <functional>

#include "Events/CoreEvents.h"
#include "CollisionStrategy.h"

namespace CW {

    class Button
    {
    public:
        Button() = default;
        Button(Shared<ICollisionStrategy> collisionChecker);
        Button(Shared<ICollisionStrategy> collisionChecker,
            const std::function<bool(MouseButtonPressed&)>& onClickCallback,
            const std::function<bool(MouseMoved&)>& onEnterCallback,
            const std::function<bool(MouseMoved&)>& onExitCallback);
        virtual ~Button() = default;

        void OnEvent(Event& event);

        void SetCollisionChecker(Shared<ICollisionStrategy> checker) { m_CollisionChecker = checker; }
        Shared<ICollisionStrategy> GetCollisionChecker() const { return m_CollisionChecker; }

        void SetOnClickCallback(const std::function<bool(MouseButtonPressed&)>& callback) { m_OnClickCallback = callback; }
        void SetOnEnterCallback(const std::function<bool(MouseMoved&)>& callback) { m_OnEnterCallback = callback; }
        void SetOnExitCallback(const std::function<bool(MouseMoved&)>& callback) { m_OnExitCallback = callback; }

    private:
        Shared<ICollisionStrategy> m_CollisionChecker;
        std::function<bool(MouseButtonPressed&)> m_OnClickCallback{ [](MouseButtonPressed&) { return false; } };
        std::function<bool(MouseMoved&)> m_OnEnterCallback{ [](MouseMoved&) { return false; } };
        std::function<bool(MouseMoved&)> m_OnExitCallback{ [](MouseMoved&) { return false; } };
        bool m_Entered = false;
    };

} // CW
