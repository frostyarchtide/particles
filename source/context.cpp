#include "context.hpp"
#include "defines.hpp"

void ResetView::execute() {
    C2D_ViewReset();
}

void View::execute() {
    C2D_ViewTranslate(-offset.x, -offset.y);
    C2D_ViewScale(scale, scale);
};

void Circle::execute() {
    C2D_DrawCircleSolid(
        position.x,
        position.y,
        0.0f,
        radius,
        C2D_Color32f(color.x, color.y, color.z, color.w)
    );
}

Screen::Screen(Display display)
    : display(display)
{
    gfxScreen_t screen = (gfxScreen_t) 0;
    switch (display) {
        case Display::TOP:
            screen = GFX_TOP;
            break;
        case Display::BOTTOM:
            screen = GFX_BOTTOM;
            break;
    }

    target = std::unique_ptr<C3D_RenderTarget>(C2D_CreateScreenTarget(screen, GFX_LEFT));
}

void Screen::execute() {
    C2D_TargetClear(target.get(), C2D_Color32f(0.1f, 0.1f, 0.1f, 1.0f));
    C2D_SceneBegin(target.get());
    C2D_ViewReset();

    for (auto& command : commands) {
        command->execute();
    }

    commands.clear();
}

Vec2 Screen::get_resolution() const {
    Vec2 resolution;
    switch (display) {
        case Display::TOP:
            resolution = Vec2(TOP_WIDTH, SCREEN_HEIGHT);
            break;
        case Display::BOTTOM:
            resolution = Vec2(BOTTOM_WIDTH, SCREEN_HEIGHT);
            break;
    }

    return resolution;
}

Context::Context() {
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    cfguInit();

    top = std::unique_ptr<Screen>(new Screen(Display::TOP));
    bottom = std::unique_ptr<Screen>(new Screen(Display::BOTTOM));
}

Context::~Context() {
    cfguExit();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();
}

void Context::execute() {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        top->execute();
        bottom->execute();
    C3D_FrameEnd(0);
}
