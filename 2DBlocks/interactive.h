#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include <string> // std::string

namespace interactive
{
    char prompt();
    bool choose(char choice, World world);
    void promptPlace(World world);
    void promptDestroy(World world);

    int getIntFromUser(std::string message);
    char getCharFromUser(std::string message);
    std::string getStringFromUser(std::string message);
    size_t getSize_tFromUser(std::string message);

    bool isBadInput();
    void clearCinBuffer();
}

#endif