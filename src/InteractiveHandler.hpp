#pragma once

#include <curses.h>
#include <memory>

class InteractiveHandler {
// Properties
private:
    static bool handlerExists;
    WINDOW *win;

// Functions
public:
    static std::unique_ptr<InteractiveHandler> getNewHandler();
    void runInteractive();
    ~InteractiveHandler();

private:
    InteractiveHandler();

};