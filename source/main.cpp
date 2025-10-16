#include "context.hpp"

int main() {
    Context context;

    View top_view(context.get_top().get_resolution() / 2.0f);

    context.run([&]() {
        context.submit(Display::TOP,
            top_view,
            Circle(),
            View(),
            Circle(0.0f, 0.0f, 10.0f)
        );
    });
}
