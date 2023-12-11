#pragma once

#include <DB.h>
#include <Menu.h>

class App
{
    public:
        App();
        void MainMenuChoice();
    private:
        uint8_t action;
};