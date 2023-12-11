#pragma once
#include <map>
#include <iostream>

class Menu
{
    public: 
        Menu();

        inline void displayMenu(const std::map<int, std::string> &orderedMap)
        {
            for (const auto &pair : orderedMap) {
                std::cout << pair.second << std::endl;
            }
        }

        inline void displayMainMenu() { displayMenu(MainMenu); }

    private:
        static std::map<int, std::string> MainMenu;
        static std::map<int, std::string> SettiingsMenu;
};

/*
inline void displayMainMenu(const std::map<int, std::string> &orderedMap)
        {
            for (const auto &pair : orderedMap) {
                std::cout << pair.first << ": " << pair.second << std::endl;
            }
        }
*/