#include "pages.h"

double lastUpdateTime = 0;
Color bgcolor;
Color buttoncolor;
Color textcolor;
Game game = Game();
Board grid = Board();
Block block = Block();
int rotationMain = 5;
float fSpeed = 0.4;
bool playMusic = true;
Music music;
int mydfc = 2;
bool hardMod = false;
int setRow = 10;
int ScoreBest;


bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        UpdateMusicStream(music);
        return true;
    }
    return false;
}

void playGame(int screenWidth, int screenHeight)
{
    bool isPaused = false;
    SetTargetFPS(60);
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game = Game(setRow);
    game.bestScore = ScoreBest;
    game.setRow = setRow;
    game.setNewSpeed = fSpeed;
    game.gameSpeed = fSpeed;
    game.dfc = mydfc;
    game.rotateChange = rotationMain;
    game.firstRotateChange = rotationMain;
    game.gameMod = hardMod;
    game.Gmode = hardMod;
    

    SetWindowSize(screenWidth, screenHeight);

    if (hardMod == false){
        while (!WindowShouldClose())
    {
            if (game.gameOver){
                game.UpdateBestScore();
                ScoreBest = game.bestScore; 
            }
            if (IsKeyPressed(KEY_P))
            {
                isPaused = !isPaused;
            }

            if (!isPaused)
            {
                game.HandleInput();
                if (EventTriggered(game.gameSpeed))
                {
                    game.MoveBlockDown();
                }
            }

            BeginDrawing();
            ClearBackground(bgcolor);
            DrawTextEx(font, "Score", {360, 15}, 38, 2, textcolor);
            DrawTextEx(font, "Next", {370, 175}, 38, 2, textcolor);
            
            DrawRectangleRounded({355, 55, 100, 60}, 2, 6, buttoncolor);
            Rectangle rotationChangeRect = {320, 125, 170, 40};  

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, textcolor);
            DrawRectangleRounded({320, 215, 170, 140}, 0.3, 6, buttoncolor);
            DrawRectangleRounded({320, 370, 170, 180}, 0.3, 6, buttoncolor);
            DrawTextEx(font, "Held Block", {335, 375}, 27, 2, textcolor);
            DrawTextEx(font, "P=PAUSE", {360, 555},25,2,textcolor);
            game.Draw();

            DrawRectangleRounded(rotationChangeRect, 0.3, 6, buttoncolor);
            char rotationChangeText[30];
            sprintf(rotationChangeText, "Rotation : %d", game.rotateChange);
            DrawText(rotationChangeText, (int)rotationChangeRect.x + 15, (int)rotationChangeRect.y + 10, 23, textcolor);

            if (isPaused)
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.5f));
                DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 80) / 2, GetScreenHeight() / 2 - 50, 80, RED);
                DrawText("Press ESC to Menu", GetScreenWidth() / 2 - MeasureText("Press ESC to Menu", 40) / 2, GetScreenHeight() / 2 + 30, 40, RED);
            }

            game.PortalFunction();

            if (game.gameOver)
            {
                ScoreBest = game.bestScore;
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RED, 0.7f));
                DrawText("GAME OVER !", GetScreenWidth() / 2 - MeasureText("GAME OVER !", 80) / 2 + 60, GetScreenHeight() / 2 - 30, 60, WHITE);
                DrawText("Press any button", GetScreenWidth() / 2 - MeasureText("Press any button", 40) / 2 , GetScreenHeight() / 2 + 30, 40, WHITE);

                StopMusicStream(music);
                PlayMusicStream(music);
            }   
        EndDrawing();
    }

    }
    else if (hardMod == true){
        while (!WindowShouldClose())
    {
            if (game.gameOver){
                game.UpdateBestScore();
                ScoreBest = game.bestScore; 
            }
            if (IsKeyPressed(KEY_P))
            {
                isPaused = !isPaused;
            }

            if (!isPaused)
            {
                game.HandleInput();
                if (EventTriggered(game.gameSpeed))
                {
                    game.MoveBlockDown();
                }
            }

            BeginDrawing();
            ClearBackground(bgcolor);
            DrawTextEx(font, "Score", {680, 15}, 38, 2, textcolor);
            DrawTextEx(font, "Next", {690, 175}, 38, 2, textcolor);
            
            DrawRectangleRounded({675, 55, 100, 60}, 2, 6, buttoncolor);
            Rectangle rotationChangeRect = {640, 125, 170, 40};  

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {640 + (170 - textSize.x) / 2, 65}, 38, 2, textcolor);
            DrawRectangleRounded({640, 215, 170, 140}, 0.3, 6, buttoncolor);
            DrawRectangleRounded({640, 370, 170, 180}, 0.3, 6, buttoncolor);
            DrawTextEx(font, "Held Block", {655, 375}, 27, 2, textcolor);
            DrawTextEx(font, "P=PAUSE", {680, 555},25,2,textcolor);
            game.Draw();

            DrawRectangleRounded(rotationChangeRect, 0.3, 6, buttoncolor);
            char rotationChangeText[30];
            sprintf(rotationChangeText, "Rotation : %d", game.rotateChange);
            DrawText(rotationChangeText, (int)rotationChangeRect.x + 15, (int)rotationChangeRect.y + 10, 23, textcolor);

            if (isPaused)
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(WHITE, 0.5f));
                DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 80) / 2, GetScreenHeight() / 2 - 50, 80, RED);
                DrawText("Press ESC to Menu", GetScreenWidth() / 2 - MeasureText("Press ESC to Menu", 40) / 2, GetScreenHeight() / 2 + 30, 40, RED);
            }

            game.PortalFunction();

            if (game.gameOver)
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RED, 0.7f));
                DrawText("GAME OVER !", GetScreenWidth() / 2 - MeasureText("GAME OVER !", 80) / 2 + 60, GetScreenHeight() / 2 - 30, 60, WHITE);
                DrawText("Press any button", GetScreenWidth() / 2 - MeasureText("Press any button", 40) / 2 , GetScreenHeight() / 2 + 30, 40, WHITE);

                StopMusicStream(music);
                PlayMusicStream(music);
            }   
        EndDrawing();
        SetWindowSize(830, 620);
    }
    
    }

    UnloadFont(font);
    SetWindowSize(500, 620);
}



void openSettings()
{
    SetTargetFPS(60);
    Font font = LoadFont("Resources/monogram.ttf");
   

    Image sbg = LoadImage("Images/setBg.png");
    Texture2D sbgTex = LoadTextureFromImage(sbg);
    UnloadImage(sbg);
         
    const int screenWidth = 500;
    const int screenHeight = 620;
    const int buttonWidth = 140;
    const int buttonHeight = 60;

    const int buttonTopMargin = 80;  

    Rectangle THEME1_BUTTON = {(float)(screenWidth / 2 - 150 - buttonWidth / 2 - 10), (float)(buttonTopMargin), (float)buttonWidth, (float)buttonHeight};
    Rectangle THEME2_BUTTON = {(float)(screenWidth / 2 - 70), (float)(buttonTopMargin), (float)buttonWidth, (float)buttonHeight};
    Rectangle THEME3_BUTTON = {(float)(screenWidth / 2 + 90), (float)(buttonTopMargin), (float)buttonWidth, (float)buttonHeight};
    
    Color THEME1_BUTTONColor = newDarkPurple;
    Color THEME2_BUTTONColor = newYellow;
    Color THEME3_BUTTONColor = newBronze;

    Rectangle easyButton= {(float)(screenWidth / 2 - 150 - buttonWidth / 2 - 10), (float)(3*buttonTopMargin), (float)buttonWidth, (float)buttonHeight};
    Rectangle normalButton = {(float)(screenWidth / 2 - 150 - buttonWidth / 2 - 10), (float)(3*buttonTopMargin+80), (float)buttonWidth, (float)buttonHeight};
    Rectangle hardButton = {(float)(screenWidth / 2 - 150 - buttonWidth / 2 - 10), (float)(3*buttonTopMargin+160), (float)buttonWidth, (float)buttonHeight};

    Color easyButtonColor = buttoncolor;
    Color normalButtonColor = buttoncolor;
    Color hardButtonColor = buttoncolor;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(bgcolor);

        Vector2 mousePoint = GetMousePosition();

        if (playMusic) {
        }

        if (CheckCollisionPointRec(mousePoint, THEME1_BUTTON))
        {
            THEME1_BUTTONColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                std::cout << "classic";
                bgcolor = newBlack;
                buttoncolor = newDarkPurple;
                textcolor = GOLD;
                
            }
        }
        else
        {
            THEME1_BUTTONColor = newDarkPurple;
        }

        if (CheckCollisionPointRec(mousePoint, THEME2_BUTTON))
        {
            THEME2_BUTTONColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                std::cout << "dark";
                bgcolor = DARKGRAY;
                buttoncolor = newYellow;
                textcolor = BLACK;
            }
        }
        else
        {
            THEME2_BUTTONColor = newYellow;
        }
        if (CheckCollisionPointRec(mousePoint, THEME3_BUTTON))
        {
            THEME3_BUTTONColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                std::cout << "dark";
                bgcolor = RAYWHITE;
                buttoncolor = newBronze;
                textcolor = DARKBLUE;
            }
        }
        else
        {
            THEME3_BUTTONColor = newBronze;
        }

        if (CheckCollisionPointRec(mousePoint, easyButton))
        {
            easyButtonColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                std::cout << "dark";
                fSpeed = 0.70;
                game.setNewSpeed = fSpeed;
                rotationMain = 10;
                game.firstRotateChange = rotationMain;
                mydfc = 1;
                game.dfc = mydfc;
                game.GetCurrentDifficultyText();
                setRow = 10;
                hardMod = false;
                game.gameMod = hardMod;
            }
        }
        else
        {
            easyButtonColor = buttoncolor;
        }
        if (CheckCollisionPointRec(mousePoint, normalButton))
        {
            normalButtonColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                std::cout << "dark";
                fSpeed = 0.40;
                game.setNewSpeed = fSpeed;
                rotationMain = 5;
                game.firstRotateChange = rotationMain;
                mydfc = 2;
                game.dfc = mydfc;
                game.GetCurrentDifficultyText();
                setRow = 10;
                hardMod = false;
                game.gameMod = hardMod;
            }
        }
        else
        {
            normalButtonColor = buttoncolor;
        }
        if (CheckCollisionPointRec(mousePoint, hardButton))
        {
            hardButtonColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                std::cout << "dark";
                fSpeed = 0.20;
                game.setNewSpeed = fSpeed;
                rotationMain = 3;
                game.firstRotateChange = rotationMain;
                mydfc = 3;
                game.dfc = mydfc;
                game.GetCurrentDifficultyText();
                setRow = 20;
                hardMod = true;
                game.gameMod = hardMod;
            }
        }
        else
        {
            hardButtonColor = buttoncolor;
        }

        DrawTexture(sbgTex, 0, 0, Fade(WHITE, 0.35f)); 

        DrawRectangleRec(THEME1_BUTTON, THEME1_BUTTONColor);
        DrawRectangleRec(THEME2_BUTTON, THEME2_BUTTONColor);
        DrawRectangleRec(THEME3_BUTTON, THEME3_BUTTONColor);
        DrawText("THEME 1", (int)THEME1_BUTTON.x + 10, (int)THEME1_BUTTON.y + 15, 26, GOLD);
        DrawText("THEME 2", (int)THEME2_BUTTON.x + 10, (int)THEME2_BUTTON.y + 15, 26, BLACK);
        DrawText("THEME 3", (int)THEME3_BUTTON.x + 10, (int)THEME3_BUTTON.y + 15, 26, darkBlue);
        DrawText("Choose Theme :", 20, 40, 35, textcolor);

        DrawText("Choose Difficulty:", 20, 200, 35, textcolor);
        char currentDifficultyText[10];
        sprintf(currentDifficultyText, "%d", game.dfc_1);
        Vector2 textSizeDfc = MeasureTextEx(font, currentDifficultyText, 27, 2);
        DrawTextEx(font, currentDifficultyText, {95 + 235 + (35 - textSizeDfc.x) / 2, 200}, 35, 2, textcolor);


        DrawRectangleRec(easyButton, easyButtonColor);
        DrawRectangleRec(normalButton, normalButtonColor);
        DrawRectangleRec(hardButton, hardButtonColor);

        DrawText("EASY", (int)easyButton.x + 10, (int)easyButton.y + 15, 26, textcolor);
        DrawText("NORMAL", (int)normalButton.x + 10, (int)normalButton.y + 15, 26, textcolor);
        DrawText("HARD", (int)hardButton.x + 10, (int)hardButton.y + 15, 26, textcolor);

        DrawText("Game Speed : ", 180, 320, 27, textcolor);
        DrawText("*The game board expands " , 180, 410, 20, textcolor);
        if (hardMod==false){
            DrawText("in the HARD mode." , 185, 430, 20, textcolor);
        }
        else if (hardMod == true){
            DrawText("in RIGHT NOW!" , 185, 430, 20, RED);
        }

        char speedText[10];
        sprintf(speedText, "%.2f", game.setNewSpeed);
        Vector2 textSize = MeasureTextEx(font, speedText, 27, 2);
        DrawTextEx(font, speedText, {180 + 185 + (27 - textSize.x) / 2, 320}, 27, 2, textcolor);

        DrawText("Rotation Change:", 180, 350, 27, textcolor);

        char rotateText[10];
        sprintf(rotateText, "%d", game.firstRotateChange);
        Vector2 textSizeHeader = MeasureTextEx(font, "Rotation Change:", 27, 2);
        DrawTextEx(font, rotateText, {180 + textSizeHeader.x + 10, 350}, 27, 2, textcolor);

        DrawText("BEST SCORE : ", 125, 560, 27, textcolor);
        char bestScoreText[10];
        sprintf(bestScoreText, "%d", ScoreBest);
        Vector2 textSizeB = MeasureTextEx(font, bestScoreText, 27, 2);
        DrawTextEx(font, bestScoreText, {95 + 225 + (35 - textSizeB.x) / 2, 542}, 55, 2, textcolor);

        EndDrawing();

    }

    UnloadFont(font);
}

void menu(){
    const int screenWidth = 500;
    const int screenHeight = 620;
    InitAudioDevice(); 
    Music music = LoadMusicStream("Sounds/music.mp3");  
    PlayMusicStream(music);

    InitWindow(screenWidth, screenHeight, "Oyun Menüsü");
    Font font = LoadFont("Font/monogram.ttf");

    const int buttonWidth = 200;
    const int buttonHeight = 60;

    Rectangle buttonPlayGame = {static_cast<float>(screenWidth / 2 - 100 - buttonWidth / 2 - 10), static_cast<float>(60 + screenHeight / 2 - buttonHeight / 2), buttonWidth, buttonHeight};
    Rectangle buttonOpenSettings = {static_cast<float>(screenWidth / 2 + 10), static_cast<float>(60 + screenHeight / 2 - buttonHeight / 2), buttonWidth, buttonHeight};
    Rectangle buttonQuit = {static_cast<float>(screenWidth / 2 - buttonWidth / 2), static_cast<float>(60 + screenHeight / 2 + 40), buttonWidth, buttonHeight};

    Color buttonPlayGameColor = buttoncolor;
    Color buttonOpenSettingsColor = buttoncolor;
    Color ButtonQuitColor = buttoncolor;

    Image bg = LoadImage("Images/mybackground.png");
    Texture2D bgTex = LoadTextureFromImage(bg);
    UnloadImage(bg);

    Image logo = LoadImage("Images/logo.png");
    Texture2D logoTex = LoadTextureFromImage(logo);
    UnloadImage(logo);

    Rectangle logoRect = {(float)(screenWidth / 2), (float)(screenHeight / 4 + 30), 390, 250}; // Adjusted position and size
    float logoScale = 1.0f;
    float logoScaleSpeed = 0.001f; // Reduced scaling speed
    SetTargetFPS(60);
    

while (!WindowShouldClose())
{
    
    Vector2 mousePoint = GetMousePosition();
    BeginDrawing();
    ClearBackground(bgcolor);
    UpdateMusicStream(music);

    if (!IsWindowMinimized() && !IsWindowResized() && !IsWindowFullscreen())
    {
        if (CheckCollisionPointRec(mousePoint, buttonPlayGame))
        {
            buttonPlayGameColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                    playGame(500, 620);
                
                
                StopMusicStream(music);
                PlayMusicStream(music);
            }
        }
        else
        {
            buttonPlayGameColor = buttoncolor;
        }

        if (CheckCollisionPointRec(mousePoint, buttonOpenSettings))
        {
            buttonOpenSettingsColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                openSettings();
            }
        }
        else
        {
            buttonOpenSettingsColor = buttoncolor;
        }
        if (CheckCollisionPointRec(mousePoint, buttonQuit))
        {
            ButtonQuitColor = LIGHTGRAY;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
                break;
            }
        }
        else
        {
            ButtonQuitColor = buttoncolor;
        }

        

        DrawTexture(bgTex, 0, 0, WHITE);  

        DrawRectangleLinesEx(buttonPlayGame, 22, BLACK);
        DrawRectangleLinesEx(buttonOpenSettings, 42, BLACK);
        DrawRectangleLinesEx(buttonQuit, 2, BLACK);

        DrawRectangleRec(buttonPlayGame, buttonPlayGameColor);
        DrawRectangleRec(buttonOpenSettings, buttonOpenSettingsColor);
        DrawRectangleRec(buttonQuit, ButtonQuitColor);
        
        DrawText("Play Game", static_cast<int>(buttonPlayGame.x) + 30, static_cast<int>(buttonPlayGame.y) + 15, 30, textcolor);
        DrawText("Settings", static_cast<int>(buttonOpenSettings.x) + 40, static_cast<int>(buttonOpenSettings.y) + 15, 30, textcolor);
        DrawText("Quit", static_cast<int>(buttonQuit.x) + 70, static_cast<int>(buttonQuit.y) + 15, 30, textcolor);

        DrawTexturePro(logoTex, {0, 0, (float)logo.width, (float)logo.height},
                           {logoRect.x, logoRect.y, logoRect.width * logoScale, logoRect.height * logoScale},
                           {(float)(logoRect.width * logoScale / 2), (float)(logoRect.height * logoScale / 2)}, 0.0f, WHITE);

            logoScale += logoScaleSpeed;

            if (logoScale > 1.05f || logoScale < 1.0f) {
                logoScaleSpeed = -logoScaleSpeed;
            }

    }

    EndDrawing();
    }

    UnloadFont(font);
    StopMusicStream(music);
    CloseAudioDevice();
}