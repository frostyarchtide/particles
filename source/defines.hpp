#pragma once

#define TOP_WIDTH              400
#define BOTTOM_WIDTH           320
#define SCREEN_HEIGHT          240
#define TOP_PROJECTION         View(-Vec2(TOP_WIDTH, SCREEN_HEIGHT) / 2.0f, SCREEN_HEIGHT)
#define BOTTOM_PROJECTION      View(-Vec2(BOTTOM_WIDTH, SCREEN_HEIGHT) / 2.0f, SCREEN_HEIGHT)
#define DELTA                  1.0f / 60.0f
#define GRAVITATIONAL_CONSTANT 1.0e+2
