#pragma once

namespace CW {

    class Event;
    class Renderer;

    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void Update(float) {}
        virtual void PausedUpdate(float) {}
        virtual void OnEvent(Event&) {}
        virtual void Draw(Renderer& render) {}

        bool IsUpdateActive() const { return m_UpdateActive; }
        bool IsDrawActive() const { return m_DrawActive; }
        bool IsEventsActive() const { return m_EventsActive; }

        void SetUpdateActive(bool b) { m_UpdateActive = b; }
        void SetDrawActive(bool b) { m_DrawActive = b; }
        void SetEventsActive(bool b) { m_EventsActive = b; }

        void SetIndex(size_t index) { m_Index = index; }
        size_t GetIndex() const { return m_Index; }

    protected:
        size_t m_Index = 0;
        bool m_UpdateActive = true;
        bool m_DrawActive = true;
        bool m_EventsActive = true;
    };

} // CW