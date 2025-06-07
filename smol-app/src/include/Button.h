#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

#include "Events/CoreEvents.h"
#include "CollisionStrategy.h"

namespace CW {

    class Renderer;

    class Button
    {
    public:
        Button() = default;
        Button(Unique<ICollisionStrategy> collisionChecker);
        Button(Unique<ICollisionStrategy> collisionChecker, Unique<sf::Drawable> visual);

        void OnEvent(Event& event);
        void Draw(Renderer& render);

        void SetCollisionChecker(Unique<ICollisionStrategy> checker) { m_CollisionChecker = std::move(checker); }
        ICollisionStrategy& GetCollisionChecker() const { return *m_CollisionChecker; }

        void SetVisual(Unique<sf::Drawable> visual) { m_Visual = std::move(visual); }
        sf::Drawable& GetVisual() const { return *m_Visual; }

        void SetOnClickCallback(const std::function<bool(MouseButtonPressed&)>& callback) { m_OnClickCallback = callback; }
        void SetOnEnterCallback(const std::function<bool(MouseMoved&)>& callback) { m_OnEnterCallback = callback; }
        void SetOnExitCallback(const std::function<bool(MouseMoved&)>& callback) { m_OnExitCallback = callback; }

    private:
        Unique<ICollisionStrategy> m_CollisionChecker;
        Unique<sf::Drawable> m_Visual;
        std::function<bool(MouseButtonPressed&)> m_OnClickCallback{ [](MouseButtonPressed&) { return false; } };
        std::function<bool(MouseMoved&)> m_OnEnterCallback{ [](MouseMoved&) { return false; } };
        std::function<bool(MouseMoved&)> m_OnExitCallback{ [](MouseMoved&) { return false; } };
        bool m_Entered = false;
    };

} // CW
