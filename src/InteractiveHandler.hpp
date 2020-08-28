#pragma once

#include <curses.h>
#include <memory>
#include <pqxx/pqxx>

class InteractiveHandler {
// Properties
private:
    static bool handlerExists;
    WINDOW *win;
    std::shared_ptr<pqxx::connection> c;

// Functions
public:
    static std::unique_ptr<InteractiveHandler> getNewHandler();
    void runInteractive();
    ~InteractiveHandler();
    void setConnection(std::shared_ptr<pqxx::connection> const &c);

private:
    InteractiveHandler();

};