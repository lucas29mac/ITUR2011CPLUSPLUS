#include "InputManager.hpp"

int main() {
    // Acessa a instância Singleton do InputManager
    InputManager& inputManager = InputManager::getInstance();

    // Lê os inputs do usuário
    inputManager.readInputs();

    // Imprime os valores lidos
    inputManager.printInputs();

    return 0;
}
