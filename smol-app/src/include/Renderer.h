#pragma once

#include "debug_utils/LineShape.h"
#include "debug_utils/DotShape.h"
#include <SFML/Graphics.hpp>

namespace CW {

    class RCircleShapeBuilder
    {
    public:
        using Self = RCircleShapeBuilder;
    public:
        RCircleShapeBuilder() { SetDefault(); }

        void SetRenderTarget(sf::RenderTarget* render) { m_RenderTarget = render; }

        Self& SetDefault();
        Self& DefaultAfterDraw() { m_Default = true; return *this; }

        Self& Position(sf::Vector2f position) { m_CirlceMesh.setPosition(position); return *this; }
        Self& Radius(float radius) { m_CirlceMesh.setRadius(radius); m_CirlceMesh.setOrigin(m_CirlceMesh.getGeometricCenter()); return *this; }
        Self& Color(sf::Color color) { m_CirlceMesh.setFillColor(color); return *this; }
        Self& Rotation(sf::Angle angle) { m_CirlceMesh.setRotation(angle); return *this; }
        Self& Scale(sf::Vector2f scale) { m_CirlceMesh.setScale(scale); return *this; }
        Self& OutlineColor(sf::Color color) { m_CirlceMesh.setOutlineColor(color); return *this; }
        Self& OutlineThickness(float thickness) { m_CirlceMesh.setOutlineThickness(thickness); return *this; }
        Self& PointCount(size_t count) { m_CirlceMesh.setPointCount(count); return *this; }
        Self& Texture(const sf::Texture* texture, bool resetRect = false) { m_CirlceMesh.setTexture(texture, resetRect); return *this; }
        Self& TextureRect(sf::IntRect rect) { m_CirlceMesh.setTextureRect(rect); return *this; }
        Self& Shader(const sf::Shader* shader) { m_Shader = shader; return *this; }

        Self& Draw();

    private:
        sf::RenderTarget* m_RenderTarget = nullptr;
        sf::CircleShape m_CirlceMesh;
        bool m_Default = false;
        const sf::Shader* m_Shader = nullptr;
    };

    class RRectangleShapeBuilder
    {
    public:
        using Self = RRectangleShapeBuilder;
    public:
        RRectangleShapeBuilder() { SetDefault(); }

        void SetRenderTarget(sf::RenderTarget* render) { m_RenderTarget = render; }

        Self& SetDefault();
        Self& DefaultAfterDraw() { m_Default = true; return *this; }

        Self& Position(sf::Vector2f position) { m_RectangleMesh.setPosition(position); return *this; }
        Self& Color(sf::Color color) { m_RectangleMesh.setFillColor(color); return *this; }
        Self& Rotation(sf::Angle angle) { m_RectangleMesh.setRotation(angle); return *this; }
        Self& Size(sf::Vector2f size) { m_RectangleMesh.setSize(size); return *this; }
        Self& Scale(sf::Vector2f scale) { m_RectangleMesh.setScale(scale); return *this; }
        Self& OutlineColor(sf::Color color) { m_RectangleMesh.setOutlineColor(color); return *this; }
        Self& OutlineThickness(float thickness) { m_RectangleMesh.setOutlineThickness(thickness); return *this; }
        Self& Texture(const sf::Texture* texture, bool resetRect = false) { m_RectangleMesh.setTexture(texture, resetRect); return *this; }
        Self& TextureRect(sf::IntRect rect) { m_RectangleMesh.setTextureRect(rect); return *this; }
        Self& Shader(const sf::Shader* shader) { m_Shader = shader; return *this; }

        Self& Draw();

    private:
        sf::RenderTarget* m_RenderTarget = nullptr;
        sf::RectangleShape m_RectangleMesh;
        bool m_Default = false;
        const sf::Shader* m_Shader = nullptr;
    };

    class RLineShapeBuilder
    {
    public:
        using Self = RLineShapeBuilder;
    public:
        RLineShapeBuilder() { SetDefault(); }

        void SetRenderTarget(sf::RenderTarget* render) { m_RenderTarget = render; }

        Self& SetDefault();
        Self& DefaultAfterDraw() { m_Default = true; return *this; }

        Self& P1Position(sf::Vector2f position) { m_LineMesh.SetPoint1(position); return *this; }
        Self& P2Position(sf::Vector2f position) { m_LineMesh.SetPoint2(position); return *this; }
        Self& Position(sf::Vector2f position) { m_LineMesh.SetPosition(position); return *this; }
        Self& Color(sf::Color color) { m_LineMesh.SetColor(color); return *this; }
        Self& P1Color(sf::Color color) { m_LineMesh.SetPoint1Color(color); return *this; }
        Self& P2Color(sf::Color color) { m_LineMesh.SetPoint2Color(color); return *this; }
        Self& SetRotationByP1(sf::Angle angle) { m_LineMesh.SetRotationByPoint1(angle); return *this; }
        Self& SetRotationByP2(sf::Angle angle) { m_LineMesh.SetRotationByPoint2(angle); return *this; }
        Self& RotateByP1(sf::Angle angle) { m_LineMesh.RotateByPoint1(angle); return *this; }
        Self& RotateByP2(sf::Angle angle) { m_LineMesh.RotateByPoint2(angle); return *this; }
        Self& Length(float length) { m_LineMesh.SetLength(length); return *this; }

        Self& Draw();

    private:
        sf::RenderTarget* m_RenderTarget = nullptr;
        LineShape m_LineMesh;
        bool m_Default = false;
    };

    class RConvexShapeSetter
    {
    public:
        using Self = RConvexShapeSetter;
    public:
        RConvexShapeSetter(sf::ConvexShape& mesh)
            : m_ConvexMesh(mesh) { }

        void SetRenderTarget(sf::RenderTarget* render) { m_RenderTarget = render; }

        Self& Position(sf::Vector2f position) { m_ConvexMesh.setPosition(position); return *this; }
        Self& Color(sf::Color color) { m_ConvexMesh.setFillColor(color); return *this; }
        Self& Rotation(sf::Angle angle) { m_ConvexMesh.setRotation(angle); return *this; }
        Self& Scale(sf::Vector2f scale) { m_ConvexMesh.setScale(scale); return *this; }
        Self& OutlineColor(sf::Color color) { m_ConvexMesh.setOutlineColor(color); return *this; }
        Self& OutlineThickness(float thickness) { m_ConvexMesh.setOutlineThickness(thickness); return *this; }
        Self& Texture(const sf::Texture* texture, bool resetRect = false) { m_ConvexMesh.setTexture(texture, resetRect); return *this; }
        Self& TextureRect(sf::IntRect rect) { m_ConvexMesh.setTextureRect(rect); return *this; }
        Self& Shader(const sf::Shader* shader) { m_Shader = shader; return *this; }

        Self& Draw();

    private:
        sf::RenderTarget* m_RenderTarget = nullptr;
        sf::ConvexShape& m_ConvexMesh;
        const sf::Shader* m_Shader = nullptr;
    };

    class RDotBuilder
    {
    public:
        using Self = RDotBuilder;
    public:
        RDotBuilder() { SetDefault(); }
        
        void SetRenderTarget(sf::RenderTarget* render) { m_RenderTarget = render; }

        Self& SetDefault();
        Self& DefaultAfterDraw() { m_Default = true; return *this; }

        Self& Position(sf::Vector2f position) { m_Dot.SetPosition(position); return *this; }
        Self& Color(sf::Color color) { m_Dot.SetColor(color); return *this; }

        Self& Draw();

    private:
        sf::RenderTarget* m_RenderTarget = nullptr;
        DotShape m_Dot;
        bool m_Default = false;
    };


    class Renderer
    {
    public:
        Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;

        void SetRenderTarget(sf::RenderTarget* target) { m_RenderTarget = target; m_DefaultView = target->getView(); }
        const sf::RenderTarget& GetRenderTarget() const { return *m_RenderTarget; }
        void ReleaseRenderTarget() { m_RenderTarget = nullptr; }
        void Draw(const sf::Drawable& target, const sf::RenderStates& states = sf::RenderStates::Default);
        void SetView(const sf::View& view) { m_RenderTarget->setView(view); }
        void ApplyDefaultView() { m_RenderTarget->setView(m_DefaultView); }
        void SetDefaultView(const sf::View& view) { m_DefaultView = view; }
        void SetDefaultViewSize(sf::Vector2f size) { m_DefaultView.setSize(size); }
        void SetDefaultViewCenter(sf::Vector2f center) { m_DefaultView.setCenter(center); }

        RCircleShapeBuilder& BeginCircleShape() { m_CircleShapeBuilde.SetRenderTarget(m_RenderTarget); return m_CircleShapeBuilde; }
        RRectangleShapeBuilder& BeginRectangleShape() { m_RectangleShapeBuilder.SetRenderTarget(m_RenderTarget); return m_RectangleShapeBuilder; }
        RLineShapeBuilder& BeginLineShape() { m_LineShapeBuilder.SetRenderTarget(m_RenderTarget); return m_LineShapeBuilder; }
        RConvexShapeSetter BeginConvexShapeSetting(sf::ConvexShape& mesh) 
        { 
            RConvexShapeSetter convexSetter(mesh); convexSetter.SetRenderTarget(m_RenderTarget); return convexSetter;
        }
        RDotBuilder& BeginDotShape() { m_DotBuilder.SetRenderTarget(m_RenderTarget); return m_DotBuilder; }

        sf::Vector2f GetWindowSize() const { return (sf::Vector2f) m_RenderTarget->getSize(); }

    private:
        sf::RenderTarget* m_RenderTarget = nullptr;
        sf::View m_DefaultView;

        RCircleShapeBuilder m_CircleShapeBuilde;
        RRectangleShapeBuilder m_RectangleShapeBuilder;
        RLineShapeBuilder m_LineShapeBuilder;
        RDotBuilder m_DotBuilder;
    };

} // CW