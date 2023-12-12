#pragma once
#include <map>
#include <iostream>

class Menu
{
    public: 
        Menu();

        inline void displayMenu(const std::map<int, std::string> &orderedMap)
        {
            std::cout << "\nAvailable actions: \n" << std::endl;
            for (const auto &pair : orderedMap) {
                std::cout << pair.second << std::endl;
            }
            std::cout << "\nPass the action: " << std::flush;
        }

        inline void displayMainMenu() { displayMenu(MainMenu); }
        inline void displaySettingsMenu() { displayMenu(SettiingsMenu); }
        inline void displayBackMenu() { displayMenu(BackMenu); }

        void provideNewWord();

    private:
        static std::map<int, std::string> MainMenu;
        static std::map<int, std::string> SettiingsMenu;
        static std::map<int, std::string> BackMenu;
};