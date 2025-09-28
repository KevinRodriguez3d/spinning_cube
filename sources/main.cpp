#include "raylib.h"
#include "rlgl.h"

#define RAYGUI_IMPLEMENTATION // define once
#include "raygui.h"

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  SetConfigFlags(FLAG_VSYNC_HINT);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_MSAA_4X_HINT); // anti-aliasing
  const int screenWidth = 1200;
  const int screenHeight = 900;
  SetTargetFPS(60);
  InitWindow(screenWidth, screenHeight, "Spinning_Cube");

  // Camera set up
  Camera3D camera = {0};
  camera.position = (Vector3){0, 10, 10};
  camera.target = (Vector3){0, 0, 0};
  camera.up = (Vector3){0, 1, 0};
  camera.fovy = 60.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // cube parameters
  Vector3 cubePosition = {0, 0, 0};
  float cubeRotation = {0.0};
  float rotationSpeed = {0};

  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    //----------------------------------------------------------------------------------
    cubeRotation += (5.0 * rotationSpeed);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

        rlPushMatrix();
            rlRotatef(cubeRotation, 0, 1, 0);
            DrawCube(cubePosition, 2, 2, 2, GRAY);
            DrawCubeWires(cubePosition, 2, 2, 2, BLACK);
        rlPopMatrix();

        DrawGrid(10, 1);

    EndMode3D();

    DrawFPS(10, 10);

    // slider
    GuiSlider((Rectangle){(float)(GetScreenWidth()/2.0)-150, ((float)GetScreenHeight()-60), 300, 10}, "0", "5", &rotationSpeed, 0.0, 5.0);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();
  //--------------------------------------------------------------------------------------
  return 0;
}
