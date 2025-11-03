#include <stdlib.h>

#include "context.hpp"
#include "defines.hpp"
#include "universe.hpp"

int main() {
    Context context;
    Universe universe;

    View bottom_view(Vec2(), 1.0f / 100.0f);

    for (size_t i = 0; i < 100; i++) {
        Vec2 position = Vec2((float) rand() / (float) RAND_MAX - 0.5f, (float) rand() / (float) RAND_MAX - 0.5f) * 100.0f;
        Vec2 velocity = Vec2((float) rand() / (float) RAND_MAX - 0.5f, (float) rand() / (float) RAND_MAX - 0.5f);

        universe.add_particle(Particle(
            position,
            velocity,
            1.0f
        ));
    }

    context.run([&]() {
        hidScanInput();

        circlePosition circle_position;
        hidCircleRead(&circle_position);
        bottom_view.offset += Vec2(circle_position.dx, -circle_position.dy) * DELTA * bottom_view.scale;

        u32 keys = hidKeysHeld();
        if (keys & KEY_DUP) {
            bottom_view.scale *= 1.0f + (1.0f * DELTA);
        }
        if (keys & KEY_DDOWN) {
            bottom_view.scale *= 1.0f - (0.5f * DELTA);
        }

        universe.update();

        Vec2 center_of_mass;
        float total_mass = 0.0f;

        for (const Particle& particle : universe.get_particles()) {
            total_mass += particle.mass;
        }

        for (const Particle& particle : universe.get_particles()) {
            center_of_mass += particle.position * particle.mass;
        }

        center_of_mass /= total_mass;

        context.submit(Display::TOP,
            TOP_PROJECTION,
            View(center_of_mass / 100.0f, 1.0f / 100.0f)
        );

        context.submit(Display::BOTTOM,
            BOTTOM_PROJECTION,
            bottom_view
        );

        universe.submit(context);
    });
}
