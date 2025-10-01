#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION // define once
#include "raygui.h"

int main(void) {
  //------------------------------------------------------------------------------
  // Initialization
  //------------------------------------------------------------------------------
  const int screenWidth = 1920/2;
  const int screenHeight = 1080/2;
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Spinning Cube");
  SetTargetFPS(120);

  // Camera setup
  Camera3D camera = {0};
  camera.position = (Vector3){0, 10, 10};
  camera.target = (Vector3){0, 0, 0};
  camera.up = (Vector3){0, 1, 0};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // Cube parameters
  Vector3 cubePosition = {0, 0, 0};
  Vector3 cubeRotAxis = {0,0,0};
  float cubeRotation = {0.0};
  float rotationSpeed = {0};
  Color cubeColor = GRAY;
  Color cubeAxisColor = BLACK;

  // UI parameters
  int activeDropDown {0};
  bool dropEdit {false};
  bool xAxis, yAxis, zAxis {false};
  int axis {0};

  GuiSetStyle(DROPDOWNBOX, TEXT_SIZE, 30);
  GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL,ColorToInt(WHITE));
  GuiSetStyle(CHECKBOX, TEXT_COLOR_FOCUSED,ColorToInt(WHITE));

  //------------------------------------------------------------------------------
  // Main game loop
  //------------------------------------------------------------------------------
  while (!WindowShouldClose()) {
    // Update
    //------------------------------------------------------------------------------
    cubeRotation += rotationSpeed * GetFrameTime();

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

    switch (axis) {
        case 0:
            cubeRotAxis = {1,0,0};
            cubeAxisColor = RED;
            break;
        case 1:
            cubeRotAxis = {0,1,0};
            cubeAxisColor = GREEN;
            break;
        case 2:
            cubeRotAxis = {0,0,1};
            cubeAxisColor = BLUE;
            break;
    }
    //------------------------------------------------------------------------------

    // Draw
    //------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    //Draw Background
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), GRAY, DARKGRAY);

    // Slider control
    BeginMode3D(camera);

        rlPushMatrix();
            rlRotatef(cubeRotation, cubeRotAxis.x, cubeRotAxis.y, cubeRotAxis.z );
            DrawCube(cubePosition, 2, 2, 2, cubeColor);
            DrawCubeWires(cubePosition, 2, 2, 2, BLACK);
        rlPopMatrix();

        DrawGrid(10, 1);

        DrawLine3D({0,0,0}, Vector3Scale(cubeRotAxis, 5), cubeAxisColor);

    EndMode3D();

    DrawFPS(10, 10);


    if(GuiCheckBox({10,200,20,20}, "X", &xAxis)) axis = 0;
    if(GuiCheckBox({50,200,20,20}, "Y", &yAxis)) axis = 1;
    if(GuiCheckBox({90,200,20,20}, "Z", &zAxis)) axis = 2;

    GuiSlider((Rectangle){(float)(GetScreenWidth()/2.0)-400, ((float)GetScreenHeight()-50), 800, 30}, "0", "1", &rotationSpeed, 0.0, 600.0);
    if(GuiDropdownBox({(float)(GetScreenWidth()/2.0)+250,50,200,50}, "Gray;Red;Green;Blue;Purple;Beige;Brown;Violet", &activeDropDown, dropEdit)) dropEdit = !dropEdit;

    EndDrawing();
    //------------------------------------------------------------------------------

  }
  //------------------------------------------------------------------------------
  // De-initialization
  //------------------------------------------------------------------------------
  CloseWindow();
  //------------------------------------------------------------------------------
  return 0;
}
