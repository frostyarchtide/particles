#include "defines.hpp"
#include "universe.hpp"

float Particle::get_radius() const {
    return sqrtf(mass);
}

void Universe::add_particle(Particle particle) {
    particles.push_back(particle);
}

const std::vector<Particle>& Universe::get_particles() const {
    return particles;
}

void Universe::update() {
    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            float distance = (particles[j].position - particles[i].position).length();

            if (distance < particles[i].get_radius() + particles[j].get_radius()) {
                float total_mass = particles[i].mass + particles[j].mass;
                float i_ratio = particles[i].mass / total_mass;
                float j_ratio = 1.0f - i_ratio;

                particles[i] = Particle(
                    particles[i].position * i_ratio + particles[j].position * j_ratio,
                    particles[i].velocity * i_ratio + particles[j].velocity * j_ratio,
                    total_mass
                );

                std::swap(particles[j], particles[particles.size() - 1]);
                particles.pop_back();
                j--;
            }
        }
    }

    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            Vec2 delta = particles[j].position - particles[i].position;
            float distance_squared = delta.x * delta.x + delta.y * delta.y;

            if (distance_squared > 0.0f) {
                Vec2 direction = delta.normalized();
                Vec2 force = direction * GRAVITATIONAL_CONSTANT / distance_squared;

                particles[i].velocity += force * DELTA;
                particles[j].velocity -= force * DELTA;
            }
        }
    }

    for (Particle& particle : particles) {
        particle.position += particle.velocity * DELTA;
    }
}

void Universe::submit(Display display, Context& context) const {
    for (const Particle& particle : particles) {
        context.submit(display, Circle(
            particle.position,
            particle.get_radius()
        ));
    }
}

void Universe::submit(Context& context) const {
    submit(Display::TOP, context);
    submit(Display::BOTTOM, context);
}
