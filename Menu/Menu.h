#pragma once
#include <map>
#include <iostream>

class Menu
{
    public: 
        Menu();

        inline void displayMenu(const std::map<int, std::string> &orderedMap)
        {
            std::cout << "\n***************" << '\n';
            for (const auto &pair : orderedMap) {
                std::cout << pair.second << std::endl;
            }

            std::cout << "***************\n" << std::endl;
            std::cout << "Pass the action: " << std::flush;
        }

        inline void displayMainMenu() { displayMenu(MainMenu); }
        inline void displaySettingsMenu() { displayMenu(SettiingsMenu); }

    private:
        static std::map<int, std::string> MainMenu;
        static std::map<int, std::string> SettiingsMenu;
};