#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib 3D Asset Viewer");

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 3.0f, 6.0f }; // Elevated camera looking down
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };   // Pointed at model center
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       // Up vector
    camera.fovy = 45.0f;                             // Field of view
    camera.projection = CAMERA_PERSPECTIVE;

    // Load the exported Blender asset
    Model sword = LoadModel("sword.obj");
    float rotation = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose(
)) { UpdateCamera(&camera, CAMERA_ORBITAL);
        // Spin the dagger smoothly
        rotation += 1.5f;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                // Draw model with position, axis of rotation, angle, scale, and color
                DrawModelEx(sword, 
                            (Vector3){ 0.0f, 0.0f, 0.0f }, 
                            (Vector3){ 0.0f, 1.0f, 0.0f }, 
                            rotation, 
                            (Vector3){ 1.0f, 1.0f, 1.0f }, 
                            LIGHTGRAY);

                DrawGrid(10, 1.0f); // Reference grid
            EndMode3D();

            DrawText("Your Blender Dagger!", 20, 20, 20, RAYWHITE);
        EndDrawing();
    }

    // Clean up memory
    UnloadModel(sword);
    CloseWindow();

    return 0;

}
