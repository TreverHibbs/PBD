#include "raylib.h"

struct ball {
  int radius;
  Vector2 pos;
  Vector2 vel;
};

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 800;
  int screenHeight = 450;

  float gravity = 9.81;
  struct ball purpleBall = {
      .pos = {.x = screenWidth / 2.0, .y = screenHeight / 2.0},
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

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
