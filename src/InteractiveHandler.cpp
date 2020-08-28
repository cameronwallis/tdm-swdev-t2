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
    	
	printw("Hello World !!!");
	refresh();                 
	getch();                   
}