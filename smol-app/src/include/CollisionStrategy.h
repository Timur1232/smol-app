#pragma once

#include "Types.h"

namespace CW {

    class Renderer;

    class ICollisionStrategy
    {
    public:
        ICollisionStrategy() = default;
        virtual ~ICollisionStrategy() = default;
        virtual bool CheckCollision(Vec2f point) const = 0;
    };


    class RectCollision
        : public ICollisionStrategy
    {
    public:
        RectCollision() = default;
        RectCollision(Vec2f position, Vec2f size)
            : m_Rect(position, size)
        {
        }

        bool CheckCollision(Vec2f point) const override { return m_Rect.contains(point); }

        sf::FloatRect GetRect() const { return m_Rect; }
        Vec2f GetSize() const { return m_Rect.size; }
        Vec2f GetPos() const { return m_Rect.position; }

        void SetRect(sf::FloatRect rect) { m_Rect = rect; }
        void SetSize(Vec2f size) { m_Rect.size = size; }
        void SetPos(Vec2f position) { m_Rect.position = position; }

    private:
        sf::FloatRect m_Rect;
    };


    class CircleCollision
        : public ICollisionStrategy
    {
    public:
        CircleCollision() = default;
        CircleCollision(Vec2f position, float radius = 1.0f)
            : m_Position(position),
              m_Radius(radius) { }

        bool CheckCollision(Vec2f point) const override { return (point - m_Position).lengthSquared() <= m_Radius * m_Radius; }

        float GetRadius() const { return m_Radius; }
        void SetRadius(float radius) { m_Radius = radius; }

        Vec2f GetPos() const { return m_Position; }
        void SetPos(Vec2f position) { m_Position = position; }

    private:
        Vec2f m_Position;
        float m_Radius = 1.0f;
    };

} // CW
