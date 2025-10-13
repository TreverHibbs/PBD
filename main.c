#include "raylib.h"

struct ball {
  int radius;  // in pixels
  Vector2 pos; // in pixels
  Vector2 vel; // in pixels per second
};

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 800;
  int screenHeight = 450;

  float ringRadius = 100.0;                    // in pixels
  Vector2 ringPos = {.x = screenWidth / 2.0,   // in pixels
                     .y = screenHeight / 2.0}; // in pixels
  float gravity = 400;                         // in pixels per second squared
  struct ball purpleBall = {
      .pos = {.x = ringPos.x, .y = ringPos.y - ringRadius},
      .vel = {0, 0},
      .radius = 10.0};

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: create a simulation of a ball falling using symplectic euler method
    float dt = GetFrameTime();

    purpleBall.vel.y += gravity * dt;
    purpleBall.pos.y += purpleBall.vel.y * dt;
    purpleBall.pos.x += purpleBall.vel.x * dt;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawCircle(purpleBall.pos.x, purpleBall.pos.y, purpleBall.radius,
               DARKPURPLE);
    DrawCircleLines(ringPos.x, ringPos.y, ringRadius, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
