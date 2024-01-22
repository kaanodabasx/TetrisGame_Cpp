#pragma once
#include "board.h"
#include "blocks.cpp"
#include <string> 

class Game
{
public:
    Game(int setRow = 10);
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void MoveBlockPortal();
    void setSpeed();
    void DrawPortalImage();
    void PortalFunction();
    bool currentBlockIsAtSpecificPosition();
    void MoveBlockAwayFromPortal();
    void HoldBlock();
    bool gameOver;
    float gameSpeed;
    float setNewSpeed;
    int score;
    int teleportRow;
    int teleportColumn;
    int rotateChange;
    int firstRotateChange;
    int portalIndex;
    int lowerScore;
    bool isSwap;
    Music music;
    bool isVertical;
    void GetCurrentDifficultyText();
    int dfc;
    int dfc_1;
    int setRow;
    void setColumn(int column);
    bool gameMod;
    bool Gmode;
    int bestScore;
    void UpdateBestScore();
    bool hasPlayedVictorySound;

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Board grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    Sound portalSound;
    Sound gameoversound;
    Sound victorysound;
    int i;
    Texture2D portalTexture;
    Image portalImage;
    bool activate;
    Block heldBlock;
    int counter;
};