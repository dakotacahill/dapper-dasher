#include "raylib.h"

int main()
{
    // window dimensions 
    const int windowWidth{512};
    const int windowHeight{380};
    InitWindow( windowWidth, windowHeight, "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x  = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y  = windowHeight - scarfyRec.height;
    
    int frame{}; // animation frame
    const float updateTime{1.0 / 12.0}; // amt of time before we update anim frame
    float runningTime{};

    bool isInAir{}; // is the rectangle in the air
    const int jumpVel{-600}; // jump velocity (pixels/s)

    int velocity{0}; 

    SetTargetFPS(60);
    while ( !WindowShouldClose() )
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyPos.y > windowHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel; 
        }

        // update position
        scarfyPos.y += velocity * dT;

        // update running time
        runningTime += dT;

        if (runningTime >= updateTime)
        {
            runningTime = 0;
            // update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE); 

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}