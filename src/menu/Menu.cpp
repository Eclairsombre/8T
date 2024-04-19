#include "Menu.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <cstring>

void Menu::drawMenu()
{
    if (this->logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Game Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("The Turbocharged, Topsy-Turvy, Transmutable Tic-Tac-Toe!").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("The Turbocharged, Topsy-Turvy, Transmutable Tic-Tac-Toe!");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        if (ImGui::Button("Play", ImVec2(200, 50)))
        {
            this->gamestate = GameState::ChooseGameMode;
        }

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 100) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Options", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Options;
        }
        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 250) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Quit", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Quit;
        }

        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(50);

        if (ImGui::Button("Credits", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Credits;
        }
        ImGui::PopStyleColor();

        ImGui::End();
    }
}

void Menu::menu()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    if (this->asGameStarted)
    {
        this->asGameStarted = false;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawMenu();
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawChooseGameModeMenu()
{
    if (this->logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Game Mode Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Game Mode Menu").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("Game Mode Menu");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        if (ImGui::Button("Local", ImVec2(200, 50)))
        {
            this->gamestate = GameState::GameCreation;
        }

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 100) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Multiplayer", ImVec2(200, 50)))
        {
            this->gamestate = GameState::ChooseCreateOrJoin;
        }
        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(50);

        if (ImGui::Button("Back", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Menu;
        }
        ImGui::PopStyleColor(); // Restore default text color

        ImGui::End();
    }
}

void Menu::chooseGameModeMenu()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawChooseGameModeMenu();
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawPauseMenu()
{
    if (logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Pause Menu").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("Pause Menu");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        if (ImGui::Button("Resume", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Game;
        }

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 100) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Options", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Options;
        }
        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 250) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Exit", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Menu;
        }
        ImGui::PopStyleColor();

        ImGui::End();
    }
}

void Menu::pauseMenu()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
        else if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_ESCAPE)
        {
            this->gamestate = GameState::Game;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawPauseMenu();
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawGameCreation(Graphic &graphic)
{
    if (logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Game Creation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Game Creation").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("Game Creation");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        static int player1Shape = 0;
        static int player1Color = 0;
        static int player2Shape = 1;
        static int player2Color = 1;

        const char *shapes[] = {"Croix", "Rond", "Triangle", "Carrée"};
        const char *colors[] = {"Rouge", "Bleu", "Vert", "Jaune"};

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        float windowWidth = ImGui::GetWindowSize().x;
        float textWidth, comboWidth;

        ImVec2 oldCursorPos = ImGui::GetCursorPos();

        ImGui::SetCursorPos(ImVec2(-9999, -9999));
        ImGui::Combo("##invisible", &player1Shape, shapes, IM_ARRAYSIZE(shapes));
        comboWidth = ImGui::GetItemRectSize().x;
        textWidth = ImGui::CalcTextSize("Joueur 1").x;

        ImGui::SetCursorPos(oldCursorPos);
        ImGui::SetCursorPosX((windowWidth - textWidth) / 2);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY());

        ImGui::Text("Joueur 1");
        textWidth = ImGui::CalcTextSize("Joueur 1").x;
        ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
        ImGui::Combo("Forme1", &player1Shape, shapes, IM_ARRAYSIZE(shapes));
        ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
        ImGui::Combo("Couleur1", &player1Color, colors, IM_ARRAYSIZE(colors));

        ImGui::SetCursorPosX((windowWidth - textWidth) / 2);

        ImGui::Text("Joueur 2");
        textWidth = ImGui::CalcTextSize("Joueur 2").x;
        ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
        ImGui::Combo("Forme2", &player2Shape, shapes, IM_ARRAYSIZE(shapes));
        ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
        ImGui::Combo("Couleur2", &player2Color, colors, IM_ARRAYSIZE(colors));

        ImGui::PopStyleColor();
        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 250);

        if (ImGui::Button("Start", ImVec2(200, 50)))
        {

            if (player1Shape != player2Shape && player1Color != player2Color)
            {
                this->gamestate = GameState::Game;

                char shape1;
                char shape2;
                if (strcmp(shapes[player1Shape], "Croix") == 0)
                {
                    shape1 = 'X';
                }
                else if (strcmp(shapes[player1Shape], "Rond") == 0)
                {
                    shape1 = 'O';
                }
                else if (strcmp(shapes[player1Shape], "Triangle") == 0)
                {
                    shape1 = 'T';
                }
                else
                {
                    shape1 = 'C';
                }

                if (strcmp(shapes[player2Shape], "Croix") == 0)
                {
                    shape2 = 'X';
                }
                else if (strcmp(shapes[player2Shape], "Rond") == 0)
                {

                    shape2 = 'O';
                }
                else if (strcmp(shapes[player2Shape], "Triangle") == 0)
                {
                    shape2 = 'T';
                }
                else
                {
                    shape2 = 'C';
                }

                Player player1 = Player(std::string(1, shape1), std::string(colors[player1Color]));
                Player player2 = Player(std::string(1, shape2), std::string(colors[player2Color]));
                graphic = *(new Graphic(this->window, this->renderer, player1, player2));
                this->asGameStarted = true;
            }
        }
    }

    ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
    ImGui::SetCursorPosX(50);

    if (ImGui::Button("Back", ImVec2(200, 50)))
    {
        this->gamestate = GameState::ChooseGameMode;
    }
    ImGui::PopStyleColor();

    ImGui::End();
}

void Menu::gameCreation(Graphic &graphic)
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawGameCreation(graphic);
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::endMenu(Graphic &graphic)
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawEndMenu(graphic);
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawEndMenu(Graphic &graphic)
{

    SDL_Texture *winnerTexture = graphic.getWinnerTexture();

    if (winnerTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(winnerTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(winnerTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("End Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("End Menu").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("End Menu");
        ImGui::Separator();

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 500) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::Text("The winner is: ");

        // Display the winner texture
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 25);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 200) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Menu", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Menu;
        }

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 350) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Quit", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Quit;
        }
        ImGui::PopStyleColor();

        ImGui::End();
    }
    else
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("End Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("End Menu").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("End Menu");
        ImGui::Separator();

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        if (ImGui::Button("Menu", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Menu;
        }

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 100) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        if (ImGui::Button("Quit", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Quit;
        }
        ImGui::PopStyleColor();

        ImGui::End();
    }
}

void Menu::createOnlineGameMenu(Graphic &graphic)
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawCreateOnlineGameMenu(graphic);
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawCreateOnlineGameMenu(Graphic &graphic)
{
    if (logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Create Online Game Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Create Online Game Menu").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("Create Online Game Menu");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        static int player1Shape = 0;
        static int player1Color = 0;

        const char *shapes[] = {"Croix", "Rond", "Triangle", "Carrée"};
        const char *colors[] = {"Rouge", "Bleu", "Vert", "Jaune"};

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        float windowWidth = ImGui::GetWindowSize().x;
        float textWidth, comboWidth;

        ImVec2 oldCursorPos = ImGui::GetCursorPos();

        ImGui::SetCursorPos(ImVec2(-9999, -9999));
        ImGui::Combo("##invisible", &player1Shape, shapes, IM_ARRAYSIZE(shapes));
        comboWidth = ImGui::GetItemRectSize().x;
        textWidth = ImGui::CalcTextSize("Joueur 1").x;

        ImGui::SetCursorPos(oldCursorPos);
        ImGui::SetCursorPosX((windowWidth - textWidth) / 2);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY());

        ImGui::Text("Joueur 1");
        textWidth = ImGui::CalcTextSize("Joueur 1").x;
        ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
        ImGui::Combo("Forme1", &player1Shape, shapes, IM_ARRAYSIZE(shapes));
        ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
        ImGui::Combo("Couleur1", &player1Color, colors, IM_ARRAYSIZE(colors));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 200) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::Text("IP Address : ");
        static char ip[16] = " ";
        ImGui::Text("%s", ip);

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 300) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PopStyleColor();

        if (ImGui::Button("Create", ImVec2(200, 50)))
        {
            // Envoi player1Shape et player1Color et attend le retour
        }

        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(50);

        if (ImGui::Button("Back", ImVec2(200, 50)))
        {
            this->gamestate = GameState::ChooseGameMode;
        }
        ImGui::PopStyleColor();

        ImGui::End();
    }
}

void Menu::joinOnlineGameMenu(Graphic &graphic)
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawJoinOnlineGameMenu(graphic);
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::Options()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawOptions();
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawOptions()
{
    if (logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Options").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("Options");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 400) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        static ImGuiSliderFlags flags = ImGuiSliderFlags_None;

        ImGui::PushItemWidth(400);
        if (ImGui::SliderInt("Music", &music, 0, 100, "%d", flags))
        {
            Mix_VolumeMusic(music);
        }

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(50);

        if (ImGui::Button("Back", ImVec2(200, 50)))
        {
            if (this->asGameStarted)
            {
                this->gamestate = GameState::Game;
            }
            else
            {
                this->gamestate = GameState::Menu;
            }
        }

        ImGui::PopStyleColor();

        ImGui::End();
    }
}
void Menu::drawJoinOnlineGameMenu(Graphic &graphic)
{
    if (logoTexture != nullptr)
    {
        if (findNetwork)
        {
            GLuint oglTextureID;
            SDL_GL_BindTexture(logoTexture, NULL, NULL);
            glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
            SDL_GL_UnbindTexture(logoTexture);

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(this->io->DisplaySize);
            ImGui::Begin("Create Online Game Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            ImGui::SetWindowFontScale(1.7f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Create Online Game Menu").x) * 0.5f);
            ImGui::SetCursorPosY(100);

            ImGui::Text("Create Online Game Menu");
            ImGui::Separator();

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
            ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

            static int player1Shape = 0;
            static int player1Color = 0;

            const char *shapes[] = {"Croix", "Rond", "Triangle", "Carrée"};
            const char *colors[] = {"Rouge", "Bleu", "Vert", "Jaune"};

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            float windowWidth = ImGui::GetWindowSize().x;
            float textWidth, comboWidth;

            ImVec2 oldCursorPos = ImGui::GetCursorPos();

            ImGui::SetCursorPos(ImVec2(-9999, -9999));
            ImGui::Combo("##invisible", &player1Shape, shapes, IM_ARRAYSIZE(shapes));
            comboWidth = ImGui::GetItemRectSize().x;
            textWidth = ImGui::CalcTextSize("Joueur 1").x;

            ImGui::SetCursorPos(oldCursorPos);
            ImGui::SetCursorPosX((windowWidth - textWidth) / 2);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY());

            ImGui::Text("Joueur 1");
            textWidth = ImGui::CalcTextSize("Joueur 1").x;
            ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
            ImGui::Combo("Forme1", &player1Shape, shapes, IM_ARRAYSIZE(shapes));
            ImGui::SetCursorPosX((windowWidth - comboWidth) / 2);
            ImGui::Combo("Couleur1", &player1Color, colors, IM_ARRAYSIZE(colors));

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 200) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            ImGui::Text("IP Address : ");
            static char ip[16] = " "; // Met la function pour afficher l'ip de la game ici
            ImGui::Text("%s", ip);

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 300) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            ImGui::PopStyleColor();

            if (ImGui::Button("Create", ImVec2(200, 50)))
            {
                // Envoi player1Shape et player1Color et au createur de la game et attend la validation
            }

            ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
            ImGui::SetCursorPosX(50);

            if (ImGui::Button("Back", ImVec2(200, 50)))
            {
                this->gamestate = GameState::ChooseGameMode;
            }
            ImGui::PopStyleColor();

            ImGui::End();
        }

        else
        {
            GLuint oglTextureID;
            SDL_GL_BindTexture(logoTexture, NULL, NULL);
            glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
            SDL_GL_UnbindTexture(logoTexture);

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(this->io->DisplaySize);
            ImGui::Begin("Join Online Game Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            ImGui::SetWindowFontScale(1.7f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Join Online Game Menu").x) * 0.5f);
            ImGui::SetCursorPosY(100);

            ImGui::Text("Join Online Game Menu");
            ImGui::Separator();

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
            ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 50) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            static char ip[16] = " ";
            ImGui::PushItemWidth(200);
            ImGui::InputText("IP", ip, IM_ARRAYSIZE(ip));

            ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 200) * 0.5f);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

            if (ImGui::Button("Start", ImVec2(200, 50)))
            {
                // check si l'ip est valide
                this->findNetwork = true;
            }

            ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
            ImGui::SetCursorPosX(50);

            if (ImGui::Button("Back", ImVec2(200, 50)))
            {
                this->gamestate = GameState::ChooseGameMode;
            }

            ImGui::PopStyleColor();

            ImGui::End();
        }
    }
}

void Menu::chooseCreateOrJoinMenu()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawChooseCreateOrJoinMenu();
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawChooseCreateOrJoinMenu()
{
    if (logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Choose Create Or Join Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Choose Create Or Join Menu").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::Text("Choose Create Or Join Menu");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::PopStyleColor();

        ImGui::SetWindowFontScale(2.0f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Coming soon...").x) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        ImGui::Text("Coming soon...");
        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(50);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        if (ImGui::Button("Back", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Menu;
        }

        ImGui::PopStyleColor();

        ImGui::End();
    }
}

void Menu::Credits()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        if (this->event.type == SDL_QUIT)
        {
            this->gamestate = GameState::Quit;
        }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    drawCredits();
    ImGui::Render();
    glViewport(0, 0, (int)this->io->DisplaySize.x, (int)this->io->DisplaySize.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(this->window);
}

void Menu::drawCredits()
{
    if (logoTexture != nullptr)
    {
        GLuint oglTextureID;
        SDL_GL_BindTexture(logoTexture, NULL, NULL);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&oglTextureID);
        SDL_GL_UnbindTexture(logoTexture);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(this->io->DisplaySize);
        ImGui::Begin("Credits", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowFontScale(1.7f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Credits").x) * 0.5f);
        ImGui::SetCursorPosY(100);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        ImGui::Text("Credits");
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Image((void *)(intptr_t)oglTextureID, ImVec2(200, 200));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y - 50) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::Text("Developed by : ");

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Text("Alexandre THOUNY");

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Text("Maël Cornec");

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Text("Yousif Jijji");

        ImGui::SetCursorPosY((ImGui::GetWindowSize().y + 200) * 0.5f);
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);

        ImGui::Text("Music : ");

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 200) * 0.5f);
        ImGui::Text("Deus Ex Sillicium by Stephane Marty");

        ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 100);
        ImGui::SetCursorPosX(50);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        if (ImGui::Button("Back", ImVec2(200, 50)))
        {
            this->gamestate = GameState::Menu;
        }

        ImGui::PopStyleColor();

        ImGui::End();
    }
}

int main()
{
    Menu menu;
    menu.start();
    return 0;
}

void Menu::start()
{
    Graphic graphic = Graphic(this->window, this->renderer);
    while (this->gamestate != GameState::Quit && SDL_GetWindowFlags(this->window) & SDL_WINDOW_SHOWN)
    {

        switch (this->gamestate)
        {
        case GameState::Menu:
            this->menu();
            break;
        case GameState::Game:
            graphic.play(this->gamestate);

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
            ImGui::CreateContext();
            ImGui_ImplSDL2_InitForOpenGL(this->window, this->gl_context);
            ImGui_ImplOpenGL3_Init("#version 330");

            break;
        case GameState::Pause:
            this->pauseMenu();
            break;
        case GameState::ChooseGameMode:
            this->chooseGameModeMenu();
            break;
        case GameState::Options:
            this->Options();
            break;
        case GameState::GameCreation:
            this->gameCreation(graphic);
            break;
        case GameState::End:
            this->endMenu(graphic);
            break;
        case GameState::CreateOnlineGame:
            this->createOnlineGameMenu(graphic);
            break;
        case GameState::JoinOnlineGame:
            this->joinOnlineGameMenu(graphic);
            break;
        case GameState::ChooseCreateOrJoin:
            this->chooseCreateOrJoinMenu();
            break;
        case GameState::Credits:
            this->Credits();
            break;
        default:
            break;
        }
    }
}

Menu::Menu()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(1);
    }
    int screenWidth, screenHeight;
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        std::cout << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
    screenWidth = dm.w;
    screenHeight = dm.h;

    srand(time(NULL));

    this->window = SDL_CreateWindow("8T", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (this->window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->io = &ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark(); // TODO add light mode
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 330");

    SDL_Surface *logoSurface = IMG_Load("../data/images/logo_big.png");
    logoTexture = SDL_CreateTextureFromSurface(this->renderer, logoSurface);
    SDL_FreeSurface(logoSurface);
}

Menu::~Menu()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(this->gl_context);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
