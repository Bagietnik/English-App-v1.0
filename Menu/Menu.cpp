#include "Menu.h"

std::map<int, std::string> Menu::MainMenu;
std::map<int, std::string> Menu::SettiingsMenu;

Menu::Menu() {
    MainMenu[1] = "1. Start";
    MainMenu[2] = "2. Settings";
    MainMenu[3] = "3. Exit";

    SettiingsMenu[1] = "1. Add a new word";
    SettiingsMenu[2] = "2. Remove a word";
    SettiingsMenu[3] = "3. List all the words";
    SettiingsMenu[4] = "4. Exit";
}