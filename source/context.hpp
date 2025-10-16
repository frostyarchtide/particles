#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <memory>
#include <vector>

#include "math.hpp"

enum class Display {
    TOP,
    BOTTOM,
};

class Screen;

struct Command {
    virtual ~Command() = default;

    virtual void execute() = 0;
};

struct View : Command {
    Vec2 offset;

    View(Vec2 offset = Vec2())
        : offset(offset)
    {}

    View(float x, float y = 0.0f)
        : View(Vec2(x, y))
    {}

    void execute() override;
};

struct Circle : Command {
    Vec2 position;
    float radius;
    Vec4 color;

    Circle(Vec2 position = Vec2(), float radius = 50.0f, Vec4 color = Vec4(1.0f))
        : position(position),
        radius(radius),
        color(color)
    {}

    Circle(float x, float y = 0.0f, float radius = 50.0f, Vec4 color = Vec4(1.0f))
        : Circle(Vec2(x, y), radius, color)
    {}

    void execute() override;
};

class Screen {
public:

    template <typename... Ts>
    void submit(Ts&&... commands) {
        static_assert((std::is_base_of_v<Command, std::decay_t<Ts>> && ...), "All Ts must derive from Command");

        (this->commands.emplace_back(std::make_unique<std::decay_t<Ts>>(std::forward<Ts>(commands))), ...);
    }

    void execute();
    Vec2 get_resolution() const;

private:
    friend class Context;

    Display display;
    std::unique_ptr<C3D_RenderTarget> target;
    std::vector<std::unique_ptr<Command>> commands;

    Screen(Display display);
};

class Context {
public:
    Context();
    ~Context();

    template <typename F>
    void run(F&& function) {
        while (aptMainLoop()) {
            function();
            execute();
        }
    }

    template <typename... Ts>
    void submit(Display display, Ts&&... commands) {
        switch (display) {
            case Display::TOP:
                top->submit(commands...);
                break;
            case Display::BOTTOM:
                bottom->submit(commands...);
                break;
        }
    }

    Screen& get_top();
    Screen& get_bottom();

private:
    std::unique_ptr<Screen> top;
    std::unique_ptr<Screen> bottom;

    void execute();
};
