#include "raylib.h"
#include "raymath.h"

struct ball {
  int radius;  // in pixels
  Vector2 pos; // in pixels
  Vector2 vel; // in pixels per second
  Color color;
};

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  float dt = 0.01;

  int screenWidth = 800;
  int screenHeight = 450;

  float ringRadius = 100.0;                    // in pixels
  Vector2 ringPos = {.x = screenWidth / 2.0,   // in pixels
                     .y = screenHeight / 2.0}; // in pixels
  float gravity = 400;                         // in pixels per second squared

  struct ball purpleBall = {
      .pos = {.x = ringPos.x, .y = ringPos.y - ringRadius},
      .vel = {20, 0},
      .radius = 10.0,
      .color = DARKPURPLE};
  struct ball greenBall = {.pos = {.x = ringPos.x, .y = ringPos.y - ringRadius},
                           .vel = {10, 0},
                           .radius = 10.0,
                           .color = DARKGREEN};
  struct ball redBall = {.pos = {.x = ringPos.x, .y = ringPos.y - ringRadius},
                         .vel = {30, 0},
                         .radius = 10.0,
                         .color = RED};
  struct ball balls[3] = {purpleBall, greenBall, redBall};
  int ballAmount = 3;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    for (int i = 0; i < ballAmount; i++) {
      Vector2 initialPos = balls[i].pos;

      // Apply gravity
      balls[i].vel.y += gravity * dt;
      balls[i].pos.y += balls[i].vel.y * dt;
      balls[i].pos.x += balls[i].vel.x * dt;

      // Satisfy ball-on-ring constraint
      Vector2 ballPosRingPosVec = Vector2Subtract(balls[i].pos, ringPos);
      Vector2 normalizedballPosRingPosVec = Vector2Normalize(ballPosRingPosVec);
      Vector2 newBallPos = Vector2Add(
          ringPos, Vector2Scale(normalizedballPosRingPosVec, ringRadius));

      balls[i].pos = newBallPos;
      balls[i].vel =
          Vector2Scale(Vector2Subtract(newBallPos, initialPos), 1.0f / dt);
    }

    // ** Collision detection SECTION** //
    // Iterate over all ball pairs and check if they collide, and if they do
    // update their velocities accordingly.
    for (int i = 0; i < ballAmount; i++) {
      for (int j = 0; j < ballAmount; i++) {
        if (i == j)
          break;
        // get the distance of the two balls from their centers
        float ballsDistance = Vector2Distance(balls[i].pos, balls[j].pos);
        if (ballsDistance <= (balls[i].radius + balls[j].radius)) {
          // TODO: Implement this stuff

          // push balls away from each other
          // first get the direction vector with subtraction

          // then take the dot product of the direction vector and
          // the velocity vector of the balls to find  the velocity vector
          // of both balls in the direction of each other

          // plug the resulting velocity vectors into the 1d collision
          // equation from classical mechanics

          // finally update the velocities of the balls with that equations
          // output
        }
      }
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < ballAmount; i++) {
      DrawCircle(balls[i].pos.x, balls[i].pos.y, balls[i].radius,
                 balls[i].color);
    }

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
