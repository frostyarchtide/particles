#pragma once

#include <vector>

#include "context.hpp"
#include "math.hpp"

struct Particle {
    Vec2 position;
    Vec2 velocity;
    float mass;

    Particle(Vec2 position = Vec2(), Vec2 velocity = Vec2(), float mass = 1.0f)
        : position(position),
        velocity(velocity),
        mass(mass)
    {}

    Particle(float px, float py = 0.0f, float vx = 0.0f, float vy = 0.0f, float mass = 1.0f)
        : Particle(Vec2(px, py), Vec2(vx, vy), mass)
    {}

    float get_radius() const;
};

class Universe {
public:
    Universe() {}

    void add_particle(Particle particle);
    const std::vector<Particle>& get_particles() const;
    void update();
    void submit(Display display, Context& context) const;
    void submit(Context& context) const;

private:
    std::vector<Particle> particles;
};
