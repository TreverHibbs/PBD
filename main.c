#include "raylib.h"
#include "raymath.h"

// Helper Functions
//----------------------------------------------------------------------------------------------------
float elasticityConstant = 1;
float oneDimentionalCollisionEquation(float mass1, float velocity1, float mass2,
                                      float velocity2);

/**
 * takes in a pair of ball masses and velocities and outputs the velocity of
 * mass1 after a 1d collision
 * @param mass1 the mass in kg of the ball that you want the resulting velocity
 * of
 * @param velocity1 the velocity in pixels/second of the ball that you want the
 * resulting velocity of
 * @param mass2 the mass in kg of the ball that you don't want the resulting
 * velocity of
 * @param velocity2 the velocity in pixels/second of the ball that you don't
 * want the resulting velocity of
 * @return the velocity of the mass1 after the collision
 */
float oneDimentionalCollisionEquation(float mass1, float velocity1, float mass2,
                                      float velocity2) {
  return ((mass1 * velocity1 + mass2 * velocity2 -
           mass2 * (velocity1 - velocity2) * elasticityConstant) /
          (mass1 + mass2));
}

// Structs
//--------------------------------------------------------------------------------------
struct ball {
  int radius;  // in pixels
  Vector2 pos; // in pixels
  Vector2 vel; // in pixels per second
  Color color;
  float mass;
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
      .color = DARKPURPLE,
      .mass = 2};
  struct ball greenBall = {.pos = {.x = ringPos.x, .y = ringPos.y - ringRadius},
                           .vel = {10, 0},
                           .radius = 10.0,
                           .color = DARKGREEN,
                           .mass = 5};
  struct ball redBall = {.pos = {.x = ringPos.x, .y = ringPos.y - ringRadius},
                         .vel = {30, 0},
                         .radius = 10.0,
                         .color = RED,
                         .mass = 10};
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
      for (int j = 0; j < i; j++) {
        float ballsDistance = Vector2Distance(balls[i].pos, balls[j].pos);
        if (ballsDistance <= (balls[i].radius + balls[j].radius) &&
            ballsDistance != 0) {
          /// A normalized vector pointing from ball i to ball j.
          Vector2 dir =
              Vector2Normalize(Vector2Subtract(balls[i].pos, balls[j].pos));

          float dist =
              (balls[i].radius + balls[j].radius - ballsDistance) / 2.0;
          /// A vector scaled by the balls distance from each other
          /// pointing from ball i to ball j.
          Vector2 posCorrectionDistanceVec = Vector2Scale(dir, dist);
          balls[i].pos.x += posCorrectionDistanceVec.x;
          balls[i].pos.y += posCorrectionDistanceVec.y;
          balls[j].pos.x += -posCorrectionDistanceVec.x;
          balls[j].pos.y += -posCorrectionDistanceVec.y;

          float ball1CollVel = Vector2DotProduct(dir, balls[i].vel);
          float ball2CollVel = Vector2DotProduct(dir, balls[j].vel);

          float ball1AfterCollVel = oneDimentionalCollisionEquation(
              balls[i].mass, ball1CollVel, balls[j].mass, ball2CollVel);
          float ball2AfterCollVel = oneDimentionalCollisionEquation(
              balls[j].mass, ball2CollVel, balls[i].mass, ball1CollVel);

          balls[i].vel =
              Vector2Add(balls[i].vel,
                         Vector2Scale(dir, ball1AfterCollVel - ball1CollVel));
          balls[j].vel =
              Vector2Add(balls[j].vel,
                         Vector2Scale(dir, ball2AfterCollVel - ball2CollVel));
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
