#include "InputManager.hpp"
#include <iostream>
#include "GeoCoordinate.hpp"
#include <fstream>
#include <sstream>


GeoCoordinate InputManager::getTxCoordinate() const {
    return GeoCoordinate(lat_tx, lon_tx);
}

GeoCoordinate InputManager::getRxCoordinate() const {
    return GeoCoordinate(lat_rx, lon_rx);
}

std::string InputManager::getTerrainProfileFile() const {
    return perfil_terreno_file;
}

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
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Erro ao abrir arquivo input.txt\n";
        exit(1);
    }

    auto readValue = [](std::ifstream& in, auto& var) {
           std::string line;
           std::getline(in, line);
           std::istringstream iss(line);
           iss >> var;
       };

       readValue(infile, lat_tx);
       readValue(infile, lon_tx);
       readValue(infile, lat_rx);
       readValue(infile, lon_rx);
       readValue(infile, f_MHz);
       readValue(infile, p);
       readValue(infile, h_tx);
       readValue(infile, h_rx);
       readValue(infile, clima);

       // Lê a linha do arquivo de perfil do terreno
       std::string line;
       std::getline(infile, line);
       std::istringstream iss1(line);
       iss1 >> perfil_terreno_file;

       // Lê a linha dos 4 arquivos foEs
       std::getline(infile, line);
       std::istringstream iss2(line);
       foEs_files.resize(4);
       for (auto& file : foEs_files) {
           iss2 >> file;
       }

       infile.close();
       std::cout << "Dados carregados com sucesso de entrada.txt\n";
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
