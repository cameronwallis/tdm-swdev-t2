#include "InteractiveHandler.hpp"
#include <memory>

// Initialise static properties

bool InteractiveHandler::handlerExists = false;

// Function definitions
std::unique_ptr<InteractiveHandler> InteractiveHandler::getNewHandler() {
    if (InteractiveHandler::handlerExists) {
        return nullptr;
    } else {
        InteractiveHandler::handlerExists = true;
        return std::unique_ptr<InteractiveHandler>(new InteractiveHandler());
    }
}

InteractiveHandler::InteractiveHandler() : win(nullptr) {
    this->win = initscr();
}

InteractiveHandler::~InteractiveHandler() {
    endwin(); 
}

void InteractiveHandler::runInteractive() {

    bool cont = true;       

    while (cont) {
        printw("Hello World !!!");
	    refresh();                 
	    getch();
        cont = false;  
    }          
}

void InteractiveHandler::setConnection(std::shared_ptr<pqxx::connection> const &c) {
    this->c = c;
}