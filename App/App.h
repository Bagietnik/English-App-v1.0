#pragma once

#include <DB.h>
#include <Menu.h>

enum class GameStage {
    Init,
    MainMenu,
    Start,
    Settings,
};

class App
{
    public:
        App();
        void SetGameStage(GameStage stage);
        void Action();
    private:
        int action;
        GameStage currentStage;
        Menu menu;
};