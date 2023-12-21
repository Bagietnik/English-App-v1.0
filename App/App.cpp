#include <App.h>

const std::string INVALID_INPUT_ERROR = "Error: Invalid input. Exiting application.";


App::App() : database("192.168.1.21", "piotrek", "XXX")
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

bool App::validateInput(std::string& input, const std::string& fieldName) {
    std::cout << "\n" << fieldName << ": " << std::flush;

    if (!(std::cin >> input)) {
        std::cerr << INVALID_INPUT_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }

    if (input == "exit") {
        this->SetGameStage(GameStage::Settings);
        return false;
    }

    return true;
}

bool App::validateAction() {
    std::string action = "";
    this->menu.displayBackMenu();

    if (!(std::cin >> action)) {
        std::cerr << INVALID_INPUT_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }

    if (action == "1") {
        this->SetGameStage(GameStage::Settings);
        return true;
    }

    return false;
}

void App::Settings()
{
    this->menu.displaySettingsMenu();

    if (!(std::cin >> this->action)) {
        std::cerr << INVALID_INPUT_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }

    switch (this->action) {
        case 1:
            this->SetGameStage(GameStage::AddNewWord);
        break;
        
        case 2:
            this->SetGameStage(GameStage::RemoveWord);
        break;
        
        case 3:
            this->SetGameStage(GameStage::ListWords);
        break;
        
        case 4:
            this->SetGameStage(GameStage::Init);
        break;
        
        default:
            system("clear");
            this->Settings();
    }
}

void App::Init()
{
    this->menu.displayMainMenu();

    if (!(std::cin >> this->action)) {
        std::cerr << INVALID_INPUT_ERROR << std::endl;
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
            system("clear");
            this->Init();
            break;
    }
}

void App::ListWords()
{
    this->database.showWords();

    while(!validateAction()){system("clear");}
}

void App::RemoveWord()
{
    std::string word = "";
    
    std::cout << "Specify the word you wish to delete" << '\n';
    std::cout << "If you wish to quit, enter 'exit'" << std::endl;

    if (!validateInput(word, "word")) {
        return;
    }else{
        database.removeWord(word);
    }

    while(!validateAction()){system("clear");};
}

void App::AddWord()
{
    new_word_t new_word;

    std::cout << "Great that you're expanding your vocabulary :)" << '\n';
    std::cout << "Please enter word, translation, category and level (e.g. apple, jablko, owoce, A1). \nIf you wish to quit, enter 'exit'" << std::endl;

    if (!validateInput(new_word.word, "word") ||
        !validateInput(new_word.translation, "translation") ||
        !validateInput(new_word.category, "category") ||
        !validateInput(new_word.level, "level")) {
        return;
    }

    database.addWord(new_word.word, new_word.translation, new_word.category, new_word.level);
    
    while(!validateAction());
}

void App::Action() {
    switch (this->currentStage) {
        case GameStage::Init:
            this->Init();
        break;

        case GameStage::Start:
            std::cout << "I'm in the Start step" << std::endl;
        break;

        case GameStage::Settings:
            this->Settings();
        break;

        case GameStage::ListWords:
            this->ListWords();
        break;

        case GameStage::RemoveWord:
            this->RemoveWord();
        break;

        case GameStage::AddNewWord:
            this->AddWord();
        break;

        default:
        break;
    }
}

    
    
    