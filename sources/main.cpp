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
  Color cubeColor = GRAY;

  //UI parameters
  int activeDropDown {0};
  bool dropEdit {false};

  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    //----------------------------------------------------------------------------------
    cubeRotation += (5.0 * rotationSpeed);

    switch (activeDropDown) {
        case 0:
            cubeColor = GRAY;
            break;
        case 1:
            cubeColor = RED;
            break;
        case 2:
            cubeColor = GREEN;
            break;
        case 3:
            cubeColor = BLUE;
            break;
        case 4:
            cubeColor = PURPLE;
            break;
        case 5:
            cubeColor = BEIGE;
            break;
        case 6:
            cubeColor = BROWN;
            break;
        case 7:
            cubeColor = VIOLET;
            break;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

        rlPushMatrix();
            rlRotatef(cubeRotation, 0, 1, 0);
            DrawCube(cubePosition, 2, 2, 2, cubeColor);
            DrawCubeWires(cubePosition, 2, 2, 2, BLACK);
        rlPopMatrix();

        DrawGrid(10, 1);

    EndMode3D();

    DrawFPS(10, 10);

    // slider
    GuiSlider((Rectangle){(float)(GetScreenWidth()/2.0)-150, ((float)GetScreenHeight()-60), 300, 10}, "0", "5", &rotationSpeed, 0.0, 5.0);

    GuiSetStyle(DROPDOWNBOX, TEXT_SIZE, 30);
    if(GuiDropdownBox({(float)(GetScreenWidth()/2.0)+250,50,200,30}, "Gray;Red;Green;Blue;Purple;Beige;Brown;Violet", &activeDropDown, dropEdit)) dropEdit = !dropEdit;

    EndDrawing();
    //----------------------------------------------------------------------------------

  }
  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();
  //--------------------------------------------------------------------------------------
  return 0;
}
