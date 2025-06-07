#include "Button.h"

#include "debug_utils/Log.h"
#include "Renderer.h"

namespace CW {

    Button::Button(Unique<ICollisionStrategy> collisionChecker)
        : m_CollisionChecker(std::move(collisionChecker))
    {
    }

    Button::Button(Unique<ICollisionStrategy> collisionChecker, Unique<sf::Drawable> visual)
        : m_CollisionChecker(std::move(collisionChecker)),
          m_Visual(std::move(visual))
    {
    }

    void Button::OnEvent(Event& event)
    {
        if (!m_CollisionChecker)
        {
            CW_ERROR("Need to provide collision detection strategy!");
            return;
        }

        EventDispatcher dispatcher(event);
        if (dispatcher.Dispach<MouseButtonPressed>(
            [this](MouseButtonPressed& e) {
                if (m_CollisionChecker->CheckCollision(static_cast<sf::Vector2f>(e.Data.position)))
                    return m_OnClickCallback(e);
                return false;
            }))
        {
            return;
        }
        dispatcher.Dispach<MouseMoved>(
            [this](MouseMoved& e) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(e.Data.position);
                if (!m_Entered && m_CollisionChecker->CheckCollision(mousePos))
                {
                    m_Entered = true;
                    return m_OnEnterCallback(e);
                }
                if (m_Entered && !m_CollisionChecker->CheckCollision(mousePos))
                {
                    m_Entered = false;
                    return m_OnExitCallback(e);
                }
                return false;
            });
    }

    void Button::Draw(Renderer& render)
    {
        if (!m_Visual)
        {
            CW_ERROR("Need drawable object for rendering!");
            return;
        }
        render.Draw(*m_Visual);
    }

} // CW