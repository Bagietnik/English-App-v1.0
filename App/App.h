#pragma once

#include <DB.h>
#include <Menu.h>
#include <cstdlib>

typedef struct new_word_params {
    std::string word;
    std::string translation;
    std::string category;
    std::string level;
}new_word_t;

enum class GameStage {
    Init,
    MainMenu,
    Start,
    Settings,
    AddNewWord,
    ListWords,
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
        DB database;
};