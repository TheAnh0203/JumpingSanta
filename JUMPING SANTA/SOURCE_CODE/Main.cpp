#include "Santa.h"
#include "Obstacle.h"
#include "Button.h"

//GENERAL VARIABLES
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;
SDL_Color textColor = { 252, 185, 0 };
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;

//TEXTURE VARIABLES
BaseObject gMenuTexture;
BaseObject gInstructionTexture;
BaseObject gBackgroundTexture;
BaseObject gStartBG;
BaseObject gLoseTexture;

BaseObject gStartButtonTexture;
BaseObject gHelpButtonTexture;
BaseObject gExitButtonTexture;

BaseObject gBackButtonTexture;
BaseObject gPauseButtonTexture;
BaseObject gPlayButtonTexture;

BaseObject gScoreTexture;
BaseObject gHighScoreTexture;
BaseObject gScoreBox;

//ARRAY FOR BUTTON TEXTURE
SDL_Rect gStartButton;
SDL_Rect gHelpButton;
SDL_Rect gExitButton;
SDL_Rect gBackButton;
SDL_Rect gPauseButton;
SDL_Rect gPlayButton;

//ARRAY FOR SANTA TEXTURE

//INITIALIZE BUTTON
Button StartButton(459, 220);
Button HelpButton(459, 296);
Button ExitButton(459, 372);
Button BackButton(55, 49);
Button PauseButton(55, 49);
Button PlayButton(55, 49);

//INITIALIZE CHARACTER
Santa santa;

//PATH
const std::string WINDOW_TITLE = "Jumping Santa";
const std::string BG_MUSIC_PATH = "Sound/BackgroundMusic.wav";
const std::string MENU_MUSIC_PATH = "Sound/MenuMusic.wav";
const std::string JUMP_MUSIC_PATH = "Sound/JumpSound.wav";
const std::string LOSE_MUSIC_PATH = "Sound/LoseSound.wav";
 
static int backgroundOffset = 0;
static int rollStartBG = 0;

//SANTA FRAME HANDLE
BaseObject gSantaTexture;
const int SANTA_FRAME = 11;
SDL_Rect gSantaClips[SANTA_FRAME];

#define FRAME_INCREASEMENT 1
#define SLOW_SANTA_FRAME 3

//SCORE HANDLE
#define TIME_MAX 1000
#define SPEED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1

//SCORE TEXT LOCATION
#define POSX_COL_1 820
#define POSY_ROW_1 30
#define POSX_COL_2 980
#define POSY_ROW_2 70

bool Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Unable to initialize SDL! " << SDL_GetError() << std::endl;
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!";
        return false;
    }

    //INITIALIZE WINDOW
    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cout << "Unable to create window." << SDL_GetError() << std::endl;
        return false;
    }

    //INITIALIZE RENDERER
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL)
    {
        std::cout << "Unable to create renderer." << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Unable to initialize SDL_image." << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Unable to initialize SDL_mixer." << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "Unable to initialize SDL_ttf." << std::endl;
        return false;
    }
    return true;
}

bool LoadMedia()
{
    gMusic = Mix_LoadMUS(BG_MUSIC_PATH.c_str());
    if (gMusic == nullptr)
    {
        std::cout << "Failed to load background music" << std::endl;
        return false;
    }

    gMenuMusic = Mix_LoadMUS(MENU_MUSIC_PATH.c_str());
    if (gMenuMusic == nullptr)
    {
        std::cout << "Failed to load menu music" << std::endl;
        return false;
    }

    gJump = Mix_LoadWAV(JUMP_MUSIC_PATH.c_str());
    if (gJump == nullptr)
    {
        std::cout << "Failed to load jumping sound" << std::endl;
        return false;
    }

    gLose = Mix_LoadWAV(LOSE_MUSIC_PATH.c_str());
    if (gLose == nullptr)
    {
        std::cout << "Failed to load lose sound" << std::endl;
        return false;
    }

    gFont = TTF_OpenFont("Font/Hunters.ttf", 40);
    if (gFont == NULL)
    {
        std::cout << "Failed to load font" << std::endl;
        return false;
    }

    if (!gMenuTexture.LoadFile("Image/Background/Menu.png",gRenderer))
    {
        std::cout << "Failed to load menu image" << std::endl;
        return false;
    }

    if (!gInstructionTexture.LoadFile("Image/Background/Instruction.png", gRenderer))
    {
        std::cout << "Failed to load instruction image" << std::endl;
        return false;
    }

    if (!gStartButtonTexture.LoadFile("Image/Button/StartButton.png", gRenderer))
    {
        std::cout << "Failed to load start button image" << std::endl;
        return false;
    }
    else
    {
        gStartButton.x = 0;
        gStartButton.y = 0;
        gStartButton.w = 138;
        gStartButton.h = 66;
    }

    if (!gHelpButtonTexture.LoadFile("Image/Button/HelpButton.png", gRenderer))
    {
        std::cout << "Failed to load help button image" << std::endl;
        return false;
    }
    else
    {
        gHelpButton.x = 0;
        gHelpButton.y = 0;
        gHelpButton.w = 138;
        gHelpButton.h = 66;
    }
    
    if (!gExitButtonTexture.LoadFile("Image/Button/ExitButton.png", gRenderer))
    {
        std::cout << "Failed to load exit button image" << std::endl;
        return false;
    }
    else
    {
        gExitButton.x = 0;
        gExitButton.y = 0;
        gExitButton.w = 138;
        gExitButton.h = 66;
    }

    if (!gBackButtonTexture.LoadFile("Image/Button/BackButton.png", gRenderer))
        {
            std::cout << "Failed to load back button image" << std::endl;
            return false;
        }
        else
        {
            gBackButton.x = 0;
            gBackButton.y = 0;
            gBackButton.w = 71;
            gBackButton.h = 59;
        }

    if (!gPauseButtonTexture.LoadFile("Image/Button/PauseButton.png", gRenderer))
    {
        std::cout << "Failed to load pause button image" << std::endl;
        return false;
    }
    else
    {
        gPauseButton.x = 0;
        gPauseButton.y = 0;
        gPauseButton.w = 70;
        gPauseButton.h = 59;
    }

    if (!gPlayButtonTexture.LoadFile("Image/Button/PlayButton.png", gRenderer))
    {
        std::cout << "Failed to load play button image" << std::endl;
        return false;
    }
    else
    {
        gPlayButton.x = 0;
        gPlayButton.y = 0;
        gPlayButton.w = 70;
        gPlayButton.h = 59;
    }

    if (!gStartBG.LoadFile("Image/Background/StartBG.png", gRenderer))
    {
        std::cout << "Failed to load start background image." << std::endl;
        return false;
    }

    if (!gBackgroundTexture.LoadFile("Image/Background/WinterBG.png", gRenderer))
    {
        std::cout << "Failed to load background image." << std::endl;
        return false;
    }
    
    if (!gSantaTexture.LoadFile("Image/Santa/Santa.png", gRenderer))
    {
        std::cout << "Failed to load santa image." << std::endl;
        return false;
    }
    else
    {
        gSantaClips[0].x = 0;
        gSantaClips[0].y = 0;
        gSantaClips[0].w = 41;
        gSantaClips[0].h = 69;

        gSantaClips[1].x = 41;
        gSantaClips[1].y = 2;
        gSantaClips[1].w = 41;
        gSantaClips[1].h = 67;

        gSantaClips[2].x = 82;
        gSantaClips[2].y = 3;
        gSantaClips[2].w = 45;
        gSantaClips[2].h = 66;

        gSantaClips[3].x = 127;
        gSantaClips[3].y = 2;
        gSantaClips[3].w = 41;
        gSantaClips[3].h = 67;

        gSantaClips[4].x = 168;
        gSantaClips[4].y = 3;
        gSantaClips[4].w = 41;
        gSantaClips[4].h = 66;

        gSantaClips[5].x = 210;
        gSantaClips[5].y = 3;
        gSantaClips[5].w = 40;
        gSantaClips[5].h = 66;

        gSantaClips[6].x = 249;
        gSantaClips[6].y = 0;
        gSantaClips[6].w = 49;
        gSantaClips[6].h = 69;

        gSantaClips[7].x = 297;
        gSantaClips[7].y = 2;
        gSantaClips[7].w = 55;
        gSantaClips[7].h = 67;

        gSantaClips[8].x = 352;
        gSantaClips[8].y = 1;
        gSantaClips[8].w = 47;
        gSantaClips[8].h = 68;

        gSantaClips[9].x = 399;
        gSantaClips[9].y = 2;
        gSantaClips[9].w = 41;
        gSantaClips[9].h = 67;

        gSantaClips[10].x = 440;
        gSantaClips[10].y = 1;
        gSantaClips[10].w = 60;
        gSantaClips[10].h = 69;

    }

    if (!gScoreBox.LoadFile("Image/Background/ScoreBox1.png", gRenderer))
    {
        std::cout << "Failed to load score box image." << std::endl;
        return false;
    }

    if (!gLoseTexture.LoadFile("Image/Background/Lose.png", gRenderer))
    {
        std::cout << "Failed to load lose image." << std::endl;
        return false;
    }
    return true;
}

void Clear()
{
    gMenuTexture.Free();
    gInstructionTexture.Free();
    gStartBG.Free();
    gBackgroundTexture.Free();  
    gScoreBox.Free();
    gLoseTexture.Free();
    gSantaTexture.Free();

    gStartButtonTexture.Free();
    gHelpButtonTexture.Free();
    gExitButtonTexture.Free();
    gBackButtonTexture.Free();
    gPauseButtonTexture.Free();
    gPlayButtonTexture.Free();

    gScoreTexture.Free();
    gHighScoreTexture.Free();

    Mix_FreeMusic(gMusic);
    Mix_FreeMusic(gMenuMusic);
    Mix_FreeChunk(gLose);
    Mix_FreeChunk(gJump);
    gMusic = nullptr;
    gMenuMusic = nullptr;
    gLose = nullptr;
    gJump = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

std::string GetHighScoreFromFile(std::string path)
{
    std::fstream HighScoreFile;
    std::string highscore;

    HighScoreFile.open(path, std::ios::in);
    HighScoreFile >> highscore;

    return highscore;
}

void UpdateHighScore(std::string path, const int& score, const std::string& old_HighScore)
{
    std::fstream HighScoreFile;
    std::string newHighScore;
    std::stringstream ss;
    ss << old_HighScore;
    int oldHighScore = 0;

    ss >> oldHighScore;
    if (score > oldHighScore)
        oldHighScore = score;

    newHighScore = std::to_string(oldHighScore);

    HighScoreFile.open(path, std::ios::out);
    HighScoreFile << newHighScore;
}

void UpdateGameTimeAndScore(int& time, int& speed, int& score)
{
    if (time == TIME_MAX)
    {
        speed += SPEED_INCREASEMENT;
    }

    if (time > TIME_MAX)
    {
        time = 0;
    }
    if (time % 5 == 0)
    {
        score += SCORE_INCREASEMENT;
    }

    time += TIME_INCREASEMENT;
}

bool CheckColission(Santa santa, SDL_Rect* santaclip, Obstacle obstacle)
{
    bool collide = false;

    int left_a = santa.GetPosX();
    int right_a = santa.GetPosX() + santaclip->w;
    int top_a = santa.GetPosY();
    int bottom_a = santa.GetPosY() + santaclip->h;

    const int TRASH_PIXEL_1 = 25;
    const int TRASH_PIXEL_2 = 30;

    int left_b = obstacle.GetPosX();
    int right_b = obstacle.GetPosX() + obstacle.GetWidth();
    int top_b = obstacle.GetPosY();
    int bottom_b = obstacle.GetPosY() + obstacle.GetHeight();

    if (right_a - TRASH_PIXEL_1 >= left_b && left_a + TRASH_PIXEL_1 <= right_b)
    {
        if (bottom_a - TRASH_PIXEL_2 >= top_b)
        {
            collide = true;
        }
    }
    return collide;
}

bool CheckObstaclesColission(Santa santa, Obstacle obstacle1, Obstacle obstacle2,SDL_Rect* santaclip)
{
    if (CheckColission(santa, santaclip, obstacle1))
        return true;

    if (CheckColission(santa, santaclip, obstacle2))
        return true;

    return false;
}

void DrawScore (BaseObject gScoreTexture, SDL_Color textColor, SDL_Renderer* gRenderer, 
                TTF_Font* gFont, const int& score)
{
    if (gScoreTexture.LoadText(std::to_string(score), gFont, textColor, gRenderer))
        gScoreTexture.Render(POSX_COL_2, POSY_ROW_1, gRenderer);
}

void DrawHighScore (BaseObject gHighScoreTexture, SDL_Color textColor, SDL_Renderer* gRenderer, 
                    TTF_Font* gFont, const std::string& HighScore)
{
    if (gHighScoreTexture.LoadText(HighScore, gFont, textColor, gRenderer))
        gHighScoreTexture.Render(POSX_COL_2, POSY_ROW_2, gRenderer);
}

void EndGameSelection(BaseObject gLoseTexture, SDL_Event* event, SDL_Renderer* gRenderer, bool& PlayAgain)
{
    if (PlayAgain)
    {
        bool EndGame = false;
        while (!EndGame)
        {
            while (SDL_PollEvent(event) != 0)
            {
                if (event->type == SDL_QUIT)
                {
                    EndGame = true;
                    PlayAgain = false;
                }

                if (event->type == SDL_KEYDOWN)
                {
                    switch (event->key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        EndGame = true;
                        Mix_ResumeMusic();
                        break;
                    case SDLK_ESCAPE:
                        EndGame = true;
                        PlayAgain = false;
                        break;
                    }
                }
            }

            gLoseTexture.Render(0, 0, gRenderer);
            SDL_RenderPresent(gRenderer);
        }
    }
}

int main(int argc, char* argv[])
{
    if (!Init())
        std::cout << "Init failed!" << std::endl;

    if (!LoadMedia())
        std::cout << "Media failed!" << std::endl;

    bool QuitMenu = false;
    bool PlayAgain = false;

    Mix_PlayMusic(gMenuMusic, -1);

    while (!QuitMenu)
    {
        SDL_Event e_mouse;
        while (SDL_PollEvent(&e_mouse) != 0) 
        {            
            if (e_mouse.type == SDL_QUIT)
                goto ExitGame;            

            //HANDLE START BUTTON 
            if (StartButton.IsInside(&e_mouse, MENU_BUTTON))
            {
                if (e_mouse.type == SDL_MOUSEBUTTONDOWN)
                {
                    PlayAgain = true;
                    QuitMenu = true;
                }
            }

            //HANDLE HELP BUTTON
            if (HelpButton.IsInside(&e_mouse, MENU_BUTTON))
            {
                if (e_mouse.type == SDL_MOUSEBUTTONDOWN)
                {
                    bool ReadDone = false;
                    while (!ReadDone)
                    {
                        do
                        {
                            if (e_mouse.type == SDL_QUIT)
                                goto ExitGame;

                            else if (BackButton.IsInside(&e_mouse, MENU_BUTTON))
                            {
                                if (e_mouse.type== SDL_MOUSEBUTTONDOWN)
                                    ReadDone = true;
                            }

                            gInstructionTexture.Render(0, 0, gRenderer);
                            BackButton.Render(gRenderer, gBackButtonTexture);

                            SDL_RenderPresent(gRenderer);

                        } while (SDL_PollEvent(&e_mouse) != 0 && 
                          (e_mouse.type == SDL_MOUSEBUTTONDOWN || e_mouse.type == SDL_MOUSEMOTION));
                    }
                }
            }

            //HANDLE EXIT BUTTON
            if (ExitButton.IsInside(&e_mouse, MENU_BUTTON))
            {
                if (e_mouse.type == SDL_MOUSEBUTTONDOWN)
                    goto ExitGame;
            }
        }

        gMenuTexture.Render(0, 0, gRenderer);
        StartButton.Render(gRenderer, gStartButtonTexture);
        HelpButton.Render(gRenderer, gHelpButtonTexture);
        ExitButton.Render(gRenderer, gExitButtonTexture);

        SDL_RenderPresent(gRenderer);
    }
    
    while (PlayAgain)
    {
        srand(time(NULL));
        int time = 0;
        int score = 0;
        int acceleration = 0;
        int frameSanta = 0;

        std::string obstaclePath1, obstaclePath2;
        std::string highscore = GetHighScoreFromFile("HighScore.txt");

        SDL_Event event;        
        
        Mix_PlayMusic(gMusic, -1);

        Obstacle obstacle1;
        Obstacle obstacle2;

        bool Quit = false;
        while (!Quit)
        {
                UpdateGameTimeAndScore(time, acceleration, score);

                while (SDL_PollEvent(&event) != 0)
                {
                    if (event.type == SDL_QUIT)
                        goto ExitGame;

                    if (PauseButton.IsInside(&event, PLAYPAUSE_BUTTON))
                    {
                        switch (event.type)
                        {
                        case SDL_MOUSEBUTTONDOWN:
                            Mix_PauseMusic();
                            break;
                        case SDL_MOUSEBUTTONUP:
                            bool BackToGame = false;
                            while (!BackToGame)
                            {
                                do
                                {
                                    if (PlayButton.IsInside(&event, PLAYPAUSE_BUTTON))
                                    {
                                        if (event.type == SDL_MOUSEBUTTONDOWN)
                                        {
                                            Mix_ResumeMusic();
                                            BackToGame = true;
                                        }
                                    }

                                    PlayButton.Render(gRenderer, gPlayButtonTexture);
                                    SDL_RenderPresent(gRenderer);

                                } while ((SDL_WaitEvent(&event) != 0) && (event.type == SDL_MOUSEBUTTONDOWN));
                            }
                            break;
                        }
                    }

                    santa.HandleEvent(event, gJump);
                }

                //ROLLING BACKGROUND 
                int offsetSpeed = OBSTACLE_SPEED + acceleration;
                backgroundOffset -= offsetSpeed;

                if (rollStartBG == 0)
                {
                    gStartBG.Render(backgroundOffset, 0, gRenderer);
                    gBackgroundTexture.Render(backgroundOffset + SCREEN_WIDTH, 0, gRenderer);
                    if (backgroundOffset == -SCREEN_WIDTH)
                        rollStartBG = -1;
                }
                else 
                {
                    if (backgroundOffset < -SCREEN_WIDTH)
                        backgroundOffset = 0;

                    gBackgroundTexture.Render(backgroundOffset, 0, gRenderer);
                    gBackgroundTexture.Render(backgroundOffset + SCREEN_WIDTH, 0, gRenderer);
                }

                santa.Move();

                //RENDER SANTA CLIP
                SDL_Rect* currentSantaClip = nullptr;
                if (santa.OnGround())
                {
                    currentSantaClip = &gSantaClips[frameSanta / SLOW_SANTA_FRAME];
                    santa.Render(currentSantaClip, gRenderer, gSantaTexture);
                }
                else
                {
                    currentSantaClip = &gSantaClips[10];
                    santa.Render(currentSantaClip, gRenderer, gSantaTexture);
                }

                obstacle1.LoadFile(1, gRenderer);
                obstacle2.LoadFile(2, gRenderer);

                obstacle1.Move(acceleration);
                obstacle1.Render(gRenderer);

                obstacle2.Move(acceleration);
                obstacle2.Render(gRenderer);

                PauseButton.Render(gRenderer, gPauseButtonTexture);

                gScoreBox.Render(0, 0, gRenderer);                
                DrawScore(gScoreTexture, textColor, gRenderer, gFont, score);
                DrawHighScore(gHighScoreTexture, textColor, gRenderer, gFont, highscore);

                if (CheckObstaclesColission(santa, obstacle1, obstacle2, currentSantaClip))
                {
                    Mix_PauseMusic();
                    Mix_PlayChannel(-1, gLose, 0);
                    UpdateHighScore("HighScore.txt", score, highscore);
                    rollStartBG = 0;
                    backgroundOffset = 0;
                    Quit = true;
                }

                SDL_RenderPresent(gRenderer);

                //MANAGE SANTA FRAME
                frameSanta += FRAME_INCREASEMENT;
                if (frameSanta / SLOW_SANTA_FRAME >= (SANTA_FRAME - 1))
                    frameSanta = 0;
        }

        EndGameSelection(gLoseTexture, &event, gRenderer, PlayAgain);

        if (!PlayAgain)
        {
            obstacle1.~Obstacle();
            obstacle2.~Obstacle();
        }
    }
 ExitGame:   
    Clear();
    return 0;
}   
