#include "game.h"
#include <random>
#include "board.h"
#include <iostream>


Game::Game(int setRow)
{
    grid = Board(setRow);
    std::cout << "setRow = " << setRow << std::endl;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    setNewSpeed = 0.40;
    gameSpeed = setNewSpeed;
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    portalSound = LoadSound("Sounds/portal.mp3");
    gameoversound = LoadSound("Sounds/gameover.mp3");
    victorysound = LoadSound("Sounds/victory.mp3");
    firstRotateChange = 5;
    rotateChange = firstRotateChange;
    activate = false;
    portalIndex = 0;
    isSwap = false;
    dfc = 2;
    dfc_1 = 2;
    counter = 0;
    gameMod = false;
    Gmode = gameMod;
    bestScore = 0;
    hasPlayedVictorySound = false;

}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(portalSound);
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock(), PlusBlock()};
}


void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);

    switch (nextBlock.id)
    {   
        case 3:
            nextBlock.Draw((static_cast<float>(255 + (32 * (setRow - 10)))), 280);
            break;
        case 4:
            nextBlock.Draw((static_cast<float>(255 + (32 * (setRow - 10)))), 270);
            break;
        case 8:
            nextBlock.Draw((static_cast<float>(270 + (32 * (setRow - 10)))), 250);
            break;

        default:
            nextBlock.Draw((static_cast<float>(270 + (32 * (setRow - 10)))), 260);
            break;
        }
    
    switch (heldBlock.id)
    {
        case 3:
            heldBlock.Draw((static_cast<float>(345 + (33 * (setRow - 10)))), 420);
            break;
        case 4:
            heldBlock.Draw((static_cast<float>(375 + (33 * (setRow - 10)))), 445);
            break;
        case 8:
            heldBlock.Draw((static_cast<float>(375 + (32 * (setRow - 10)))), 435);
            break;
        default:
            heldBlock.Draw((static_cast<float>(360 + (33 * (setRow - 10)))), 445);
            break;
        }
        
}



void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0) {
        gameOver = false;
        Reset();
    }
    switch (keyPressed) {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);      
        setSpeed();
        break;
    case KEY_UP:
        if (rotateChange > 0) {
            rotateChange--;
            RotateBlock();
        }
        break;
    case KEY_ENTER: 
        HoldBlock();
        break;
    }

    
}



void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
            rotateChange = firstRotateChange;
            
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
            
        }
    }
}


void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
        PlaySound(gameoversound);
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
        setSpeed();
        GetCurrentDifficultyText();
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    gameSpeed = setNewSpeed;
    portalIndex = 0;
    lowerScore = 0;
    activate = false;
    hasPlayedVictorySound = false;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;

    if (score > bestScore && !hasPlayedVictorySound && bestScore!=0) {
        PlaySound(victorysound);
        hasPlayedVictorySound = true;
    }
}

void Game::setSpeed(){
    if (score > 300 ){
        gameSpeed = setNewSpeed*0.8;
    }
    if (score > 700){
        gameSpeed = setNewSpeed*0.55;
    }
    if (score > 1250){
        gameSpeed = setNewSpeed*0.35;
    }
}

void Game::PortalFunction() {
    static const int portalRanges[] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};
    int lowerScore = portalRanges[portalIndex];
    int upperScore = lowerScore + 50;
    
    Gmode = gameMod;

    if (!Gmode) {
        
        if (score >= lowerScore && score < upperScore && !activate) {
            i = GetRandomValue(0, 8);  
            activate = true;
            portalImage = LoadImage("Images/portal.png");
            portalTexture = LoadTextureFromImage(portalImage);
            PlaySound(portalSound);
        }

        if (activate) {
            
            if (!grid.IsCellEmpty(8, i) || !grid.IsCellEmpty(8, i + 1)) {
                
                i = GetRandomValue(0, 8);
            }
            DrawTexture(portalTexture, 10 + (i * 30), 250, WHITE);
            MoveBlockAwayFromPortal();

            
            if (score >= upperScore || lowerScore == 0) {
                UnloadTexture(portalTexture);
                activate = false;
                portalIndex = (portalIndex + 1) % (sizeof(portalRanges) / sizeof(portalRanges[0]));
            }
        }
    } 
    else if (Gmode){
        if (score >= lowerScore && score < upperScore && !activate) {
            i = GetRandomValue(0, 18);  
            activate = true;
            portalImage = LoadImage("Images/portal.png");
            portalTexture = LoadTextureFromImage(portalImage);
            PlaySound(portalSound);
        }

        if (activate) {
            
            if (!grid.IsCellEmpty(8, i) || !grid.IsCellEmpty(8, i + 1)) {
                
                i = GetRandomValue(0, 18);
            }
            DrawTexture(portalTexture, 10 + (i * 30), 250, WHITE);
            MoveBlockAwayFromPortal();

            
            if (score >= upperScore || lowerScore == 0) {
                UnloadTexture(portalTexture);
                activate = false;
                portalIndex = (portalIndex + 1) % (sizeof(portalRanges) / sizeof(portalRanges[0]));
            }
        }
    }
}

void Game::MoveBlockAwayFromPortal() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if ((item.row == 8 && item.column == i) || (item.row == 8 && item.column == i + 1)) {
            for (int a = 0; a < 12; ++a) {
                currentBlock.Move(1, 0);
                if (IsBlockOutside() || BlockFits() == false) {
                    currentBlock.Move(-1, 0);
                }
            }
        }
    }
}


void Game::HoldBlock() {
    if (!gameOver) {
        int row1= currentBlock.rowOffset;
        int col1 = currentBlock.columnOffset;
        if (!isSwap) {
            heldBlock = currentBlock;
            currentBlock = nextBlock;
            nextBlock = GetRandomBlock();
            isSwap = true;
        } else {
            Block temp = currentBlock;
            currentBlock = heldBlock;
            heldBlock = temp;
        }
        currentBlock.rowOffset = row1;
        currentBlock.columnOffset = col1;
        heldBlock.rowOffset = 0;
        heldBlock.columnOffset = 0;
    }
    if (IsBlockOutside() || BlockFits() == false){
        HoldBlock();
    }
}

void Game::GetCurrentDifficultyText(){
    if (dfc == 1){
        dfc_1 = 1;
    }
    else if (dfc == 2){
        dfc_1 = 2;
    }
    else if (dfc == 3){
        dfc_1 = 3;
    }
}

void Game::UpdateBestScore() {
    if (bestScore < score) {
        bestScore = score;
    }
}
