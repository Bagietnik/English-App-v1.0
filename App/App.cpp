#include <App.h>

App::App()
{

    DB database("192.168.1.21", "piotrek", "4Fa7876c");
    if (database.isConnected())
    {
        Menu menu;
        menu.displayMainMenu();
        this -> MainMenuChoice();
        
    }else{
        std::cerr << "Error: Database connection failed. Exiting application." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void App::MainMenuChoice()
{
    std::cout << "Pass the action: " << std::flush;
    if (!(std::cin >> this -> action))
    {
        std::cerr << "Error: Invalid input. Exiting application." << std::endl;
        exit(EXIT_FAILURE);
    }
}
    
    
    