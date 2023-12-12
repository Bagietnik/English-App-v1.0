#include <App.h>

App::App() : database("192.168.1.21", "piotrek", "pswrd")
{

    
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
    system("clear");
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

            switch (this->action) {
                case 1:
                    this->SetGameStage(GameStage::AddNewWord);
                    break;
                case 2:
                    break;
                case 3:
                    this->SetGameStage(GameStage::ListWords);
                    break;
                case 4:
                    this->SetGameStage(GameStage::Init);
                    break;
                default:
                    std::cerr << "Error: Invalid action. Exiting application." << std::endl;
                    exit(EXIT_FAILURE);
            }
            break;


        case GameStage::ListWords:
            this->database.showWords();
            this->menu.displayBackMenu();

            if (!(std::cin >> this->action)) {
                std::cerr << "Error: Invalid input. Exiting application." << std::endl;
                exit(EXIT_FAILURE);
            }

            switch (this->action) {
                case 1:
                    this->SetGameStage(GameStage::Settings);
                    break;
            }
            break;

            break;

        default:
            break;


        case GameStage::AddNewWord:
            new_word_t *new_word = new new_word_t;

            std::cout << "Great that you're expanding your vocabulary :)" << '\n';
            std::cout << "Please enter word, translation, category and level (e.g. apple, jablko, owoce, A1). \nIf you wish to quit, enter 'exit'" << std::endl;
            std::cout << "\nword: " << std::flush;

            if (!(std::cin >> new_word -> word)) {
                std::cerr << "Error: Invalid input. Exiting application." << std::endl;
                exit(EXIT_FAILURE);
            }

            delete new_word;

        break;
    }
}

    
    
    