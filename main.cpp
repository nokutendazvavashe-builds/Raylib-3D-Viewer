#include "raylib.h"
#include "raymath.h"

int main() {
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "C++ Physics Playground");

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 15.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Player State & Physics Variables
    Vector3 playerPos = { 0.0f, 1.0f, 0.0f };
    Vector3 velocity  = { 0.0f, 0.0f, 0.0f };

    float accel     =55.0f; // Speed gain per second
    float friction  = 8.0f;  // Ground drag rate per second
    float gravity   = -30.0f;
    float jumpForce = 15.0f;
    bool isGrounded = true;

    SetTargetFPS(120);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime(); // Delta time in seconds

        // -------------------------------------------------------------
        // 1. INPUT & HORIZONTAL ACCELERATION
        // -------------------------------------------------------------
        Vector3 inputDir = { 0.0f, 0.0f, 0.0f };
        if (IsKeyDown(KEY_W)) inputDir.z -= 1.0f;
        if (IsKeyDown(KEY_S)) inputDir.z += 1.0f;
        if (IsKeyDown(KEY_A)) inputDir.x -= 1.0f;
        if (IsKeyDown(KEY_D)) inputDir.x += 1.0f;

        // Normalize input vector so diagonal movement isn't faster
        if (Vector3Length(inputDir) > 0.0f) {
            inputDir = Vector3Normalize(inputDir);
        }

        // Add acceleration based on input
        velocity.x += inputDir.x * accel * dt;
        velocity.z += inputDir.z * accel * dt;

        // -------------------------------------------------------------
        // 2. FRICTION / DRAG (Horizontal smooth deceleration)
        // -------------------------------------------------------------
        velocity.x -= velocity.x * friction * dt;
        velocity.z -= velocity.z * friction * dt;

        // -------------------------------------------------------------
        // 3. GRAVITY & JUMPING
        // -------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            velocity.y = jumpForce;
            isGrounded = false;
        }

        // Apply constant downward acceleration
        velocity.y += gravity * dt;

        // -------------------------------------------------------------
        // 4. POSITION UPDATE & FLOOR COLLISION
        // -------------------------------------------------------------
        playerPos.x += velocity.x * dt;
        playerPos.y += velocity.y * dt;
        playerPos.z += velocity.z * dt;

        // Simple ground collision at y = 1.0
        if (playerPos.y <= 1.0f) {
            playerPos.y = 1.0f;
            velocity.y = 0.0f;
            isGrounded = true;
        }

        // Keep camera focused on player
        camera.target = playerPos;
        camera.position = (Vector3){ playerPos.x, playerPos.y + 8.0f, playerPos.z + 12.0f };

        // -------------------------------------------------------------
        // 5. RENDERING
        // -------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                // Draw a grid floor
                DrawGrid(20, 1.0f);

                // Draw player sphere (or your loaded model)
                DrawSphere(playerPos, 1.0f, DARKBLUE);
                DrawSphereWires(playerPos, 1.0f, 16, 16, BLACK);
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("WASD to move (Momentum) | SPACE to Jump", 10, 35, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

