#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string>
#include <vector>
#include "GeoCoordinate.hpp"

class InputManager {
public:
    static InputManager& getInstance();  // Método Singleton

    void readInputs();                   // Leitura dos inputs via terminal
    void printInputs() const;           // Impressão dos valores lidos


    GeoCoordinate getTxCoordinate() const;
    GeoCoordinate getRxCoordinate() const;
    std::string getTerrainProfileFile() const;

private:
    InputManager() = default;           // Construtor privado
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    static InputManager* instance;      // Ponteiro estático para Singleton

    // Variáveis de entrada
    double lat_tx, lon_tx;
    double lat_rx, lon_rx;
    double f_MHz;
    double p;
    double h_tx, h_rx;
    int clima;
    std::string perfil_terreno_file;
    std::vector<std::string> foEs_files;
};

#endif // INPUTMANAGER_HPP
