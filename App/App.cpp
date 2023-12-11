#include <App.h>

App::App()
{

    DB database("192.168.1.21", "piotrek", "XXX");
    if (database.isConnected())
    {
        this -> SetGameStage(GameStage::Init);        
    }else{
        std::cerr << "Error: Database connection failed. Exiting application." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void App::SetGameStage(GameStage stage)
{
    this->currentStage = stage;
    this -> Action();
}

void App::Action() {
    switch (this->currentStage) {
        case GameStage::Init:
            this->menu.displayMainMenu();

            if (!(std::cin >> this->action)) {
                std::cerr << "Error: Invalid input. Exiting application." << std::endl;
                exit(EXIT_FAILURE);
            }

            switch (this->action) {
                case 1:
                    this->SetGameStage(GameStage::Start);
                    break;
                case 2:
                    this->SetGameStage(GameStage::Settings);
                    break;
                case 3:
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    std::cerr << "Error: Invalid action. Exiting application." << std::endl;
                    exit(EXIT_FAILURE);
            }
            break;


        case GameStage::Start:
            std::cout << "I'm in the Start step" << std::endl;
            break;

        case GameStage::Settings:
            this->menu.displaySettingsMenu();

            if (!(std::cin >> this->action)) {
                std::cerr << "Error: Invalid input. Exiting application." << std::endl;
                exit(EXIT_FAILURE);
            }

            break;

        default:
            break;
    }
}

    
    
    