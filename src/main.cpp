#include "game.hpp"
#include <iostream>

int main(){
    try {
        Game game;
        game.play();
    } catch (const char* msg) {
        std::cerr << "Error: " << msg << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }
    return 0;
}