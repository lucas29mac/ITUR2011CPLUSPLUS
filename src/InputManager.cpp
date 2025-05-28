#include "InputManager.hpp"
#include <iostream>

// Inicialização do ponteiro estático
InputManager* InputManager::instance = nullptr;

// Implementação do método getInstance
InputManager& InputManager::getInstance() {
    if (!instance) {
        instance = new InputManager();
    }
    return *instance;
}

// Método para ler inputs do usuário
void InputManager::readInputs() {
    std::cout << "Latitude do transmissor: ";
    std::cin >> lat_tx;
    std::cout << "Longitude do transmissor: ";
    std::cin >> lon_tx;
    std::cout << "Latitude do receptor: ";
    std::cin >> lat_rx;
    std::cout << "Longitude do receptor: ";
    std::cin >> lon_rx;
    std::cout << "Frequência (MHz): ";
    std::cin >> f_MHz;
    std::cout << "Percentual de tempo (p%): ";
    std::cin >> p;
    std::cout << "Altura da antena transmissora (m): ";
    std::cin >> h_tx;
    std::cout << "Altura da antena receptora (m): ";
    std::cin >> h_rx;
    std::cout << "Código do clima: ";
    std::cin >> clima;
    std::cout << "Arquivo com perfil de terreno: ";
    std::cin >> perfil_terreno_file;

    std::cout << "Arquivos foEs (4 arquivos separados por espaço): ";
    foEs_files.resize(4);
    for (auto& file : foEs_files) {
        std::cin >> file;
    }
}

// Método para imprimir os inputs lidos
void InputManager::printInputs() const {
    std::cout << "\n---- INPUTS ----\n";
    std::cout << "TX: (" << lat_tx << ", " << lon_tx << ")\n";
    std::cout << "RX: (" << lat_rx << ", " << lon_rx << ")\n";
    std::cout << "Frequência: " << f_MHz << " MHz\n";
    std::cout << "p%: " << p << "\n";
    std::cout << "Altura TX: " << h_tx << " m\n";
    std::cout << "Altura RX: " << h_rx << " m\n";
    std::cout << "Clima: " << clima << "\n";
    std::cout << "Perfil do terreno: " << perfil_terreno_file << "\n";
    std::cout << "Arquivos foEs: ";
    for (const auto& file : foEs_files) {
        std::cout << file << " ";
    }
    std::cout << "\n----------------\n";
}
