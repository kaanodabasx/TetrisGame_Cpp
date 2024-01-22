#include "raylib.h"
//#include "vector.h"

int main() {
    // Pencere boyutlarını ayarlayın
    int screenWidth = 800;
    int screenHeight = 450;

    // Raylib penceresini başlat
    InitWindow(screenWidth, screenHeight, "Merhaba Raylib!");

    // FPS (Frame Per Second) değerini ayarla
    SetTargetFPS(60);

    // Ana döngü
    while (!WindowShouldClose()) {
        // Çizim işlemlerini başlat
        BeginDrawing();

            // Arka planı temizle
            ClearBackground(RAYWHITE);

            // Ekrana metin yaz
            DrawText("Merhaba Raylib!", 190, 200, 20, LIGHTGRAY);

        // Çizim işlemlerini bitir
        EndDrawing();
    }

    // Pencereyi kapat ve kaynakları serbest bırak
    CloseWindow();

    return 0;
}
