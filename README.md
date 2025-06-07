# smol-app (WIP)
Simple library for creating small graphical apps, that i created for university assesstments.
I took it from my [coursework project](https://github.com/Timur1232/coursework-2) for 4-th semester on OOP class.

# Used dependencies
- SFML 3.0.0: https://www.sfml-dev.org
- imgui: https://github.com/ocornut/imgui
- imgui-sfml: https://github.com/SFML/imgui-sfml
- FastNoise2: https://github.com/Auburn/FastNoise2

# Building
1. After cloning open VS solution and build in Release or Debug. Final lib will be in `x64/<Configuration>`.
2. Download [SFML](https://www.sfml-dev.org/download/) and follow [tutorial](https://www.sfml-dev.org/tutorials/3.0/getting-started/visual-studio/) to set it up.
3. Link `smol-app.lib` and add `src/include` and `dependencies/imgui` folders to include path.

ImGui library with sfml adapter compiles within `smol-app.lib`, so you dont have to manualy link it.

# Usage
## Application
First, include `EntryPoint.h` file - it contains main function, thus must be included only once in only one file.
Then create main application class, diriving from `CW::Application`
```cpp
class MyApp : public CW::Application
{/*...*/};
```

In constructor call base class constructor to pass window size and title:
```cpp
MyApp() : Application(800, 600, "hello")
{/*...*/}
```

There is 4 main virtual methods that can be overriten (see example project in solution):
1. `void Update(float deltaTime)` - main updating function
2. `void Draw(Renderer& render)` - main rendering function
3. `void OnEvent(Event& e)` - function for recieving and dispatching events
4. `void PausedUpdate(float deltaTime)` - function for updating logic on pause

And lastly, implement `create_program` function defined in `EntryPoint.h`, that enables to pass your app class to work with it.
It also allows to handle command line arguments.

Simply copy function signature and implement its body where your app class is:
```cpp
std::unique_ptr<CW::Application> create_program(int argc, const char** argv)
{
  // handaling argc and argv
  return std::make_unique<MyApp>();
}
```
## Layers
Additionaly, there is layer system to separating logic into different modules and also helps creating interfaces.

First, create layer class, deriving from `CW::Layer`.
```cpp
class MyLayer : public CW::Layer
{/*...*/};
```

Similarly to `Application` class, it has same 4 virtual methods to override.
Use `PushLayer`, `InsertLayer`, `PopLayer` and `EraseLayer` in `CW::Application` class to manipulate your layers.
Layers can interact through the event system.

## Events
### Using events
Event system inspired by [Hazel Engine](https://github.com/TheCherno/Hazel) by TheCherno.

To dispatch events create dispatcher object inside `OnEvent` function.
Then use `Dispatch` function with needed event type to dispatch it to corresponding function.
Use `CW_BUILD_EVENT_FUNC` macro to easely create and pass callback.
```cpp
CW::EventDispatcher dispatcher(event);
dispatcher.Dispach<CW::KeyPressed>(CW_BUILD_EVENT_FUNC(OnKeyPressed));
```

`Dispatch` function returns true if event is handled.

The function that should recieve event must return `bool` and accept event reference.
Returning `true` meaning that this event is handled and shouldn't propagate forward. Returning `false` meaning the opposite.
That allows to properly handling events, for example, in interface.
```cpp
bool OnKeyPressed(CW::KeyPressed& e)
{
	// do stuff
	return false; // or true if handled
}
```

See `Events/CoreEvents.h` file for list of events.

To get better understanding of main loop pipeline see `void ProgramCore::Run()` function in `ProgramCore.cpp`.

### Creating custom events
Custom events must be deriver from `Event` class defined in `Event.h` and defined inside `CW` namespace in `CW_CustomEvents.h`.
Use `CW_BUILD_EVENT_TYPE` macro to add needed methods for it to work.
After creating event type it must be listed on `CW_CUSTOM_EVENTS_LIST` macro in `CW_EventConfig.h`.

Example:
```cpp
class MessegeToUser
  : public Event
{
public:
  std::string Messege;
  MessegeToUser(const char* messege) : Messege(messege) {}
  CW_BULD_EVENT_TYPE(MessegeToUser)
};
```

To send event use `CW::EventHandler` singleton:
```cpp
CW::EventHandler::Get().SendEvent(MessegeToUser{"Hello!"});
```

## Rendering
In `Draw` function you recieve `CW::Renderer` ref that allows to render primitives by specifying parameters with function chaining:
```cpp
render.BeginRectangleShape().DefaultAfterDraw()
	.Position(m_Rect.position)
	.Size(m_Rect.size)
	.Color(sf::Color::Red)
	.Draw();
```
* see `Renderer.h` file for all methods.

List of primitives:
- Circle shape
- Rectangle shape
- Line
- Dot
- Convex shape wrapper (needs `sf::ConvexShape` object)

For other cases use `Draw` function in `CW::Renderer` with sfml `sf::Drawable` objects.

You should always call `DefaultAfterDraw` or `SetDefault` because renderer object is shared to all objects and keeping the last state.

## Other stuff
### Camera2D
To use camera, create instace of it in your app or layer class, pass events to it and bind it to the context:
```cpp
m_Camera.OnEvent(event);
```

Default behaivour is moving by holding `RMB` (can be changed in `Camera2D.h`) and dragging, and `scroll wheel` to zoom.
You can change it by modifing `CW::Camera2D` class.

To bind camera view use `SetView` in `CW::Renderer` class or directly on sfml render target (window) that you can access in your app class.
```cpp
renderer.SetView(m_Camera.GetView());
// or other way
m_Window.setView(m_Camera.GetView());
```

To set default view use `SetDefaultView` in `CW::Renderer` or directly on sfml render target
```cpp
renderer.SetDefaultView();
// or other way
m_Window.setView(m_Window.getDefaultView());
```

### Button
First, create `CW::Button` instance.

Set needed callbacks:
- `SetOnClickCallback` - when clicked
- `SetOnEnterCallback` - when mouse enters button collision
- `SetOnExitCallback` - when mouse exits button collision

Set collision strategy:
- `RectCollision`
- `CircleCollision`

Set object that will be drawn (sprite or mesh).

Then pass events to it and call `Draw` to render.
