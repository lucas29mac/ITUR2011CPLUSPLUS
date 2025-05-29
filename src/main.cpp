#include "InputManager.hpp"
#include "OutputManager.hpp"
#include "GeoCalculator.hpp"

#include <cstdlib>  // srand, rand
#include <ctime>    // time
#include <fstream>
#include <iostream>
#include <string>

int main() {
    // --- Gera arquivo perfil.txt com terreno aleatório ---
    {
        std::ofstream file("perfil.txt");
        if (!file) {
            std::cerr << "Erro ao criar arquivo perfil.txt\n";
            return 1;
        }

        std::srand(std::time(nullptr)); // inicializa semente do rand

        const int nPoints = 100;
        for (int i = 0; i < nPoints; ++i) {
            double height = std::rand() % 501; // gera valor de 0 a 500 metros
            file << height << "\n";
        }

        std::cout << "Arquivo perfil.txt criado com " << nPoints << " pontos de altura aleatória.\n";
    }

    // --- Fluxo principal do programa ---

    InputManager& inputManager = InputManager::getInstance();
    OutputManager output;

    // Lê entradas
    inputManager.readInputs();
    inputManager.printInputs();

    // Obtém coordenadas
    GeoCoordinate tx = inputManager.getTxCoordinate();
    GeoCoordinate rx = inputManager.getRxCoordinate();

    // Instancia o geocalculador com coordenadas
    GeoCalculator calculator(tx.latitude, tx.longitude, rx.latitude, rx.longitude);

    // Mostra distância e ponto médio
    double distanceKm = calculator.computeDistanceKm();
    auto [midLat, midLon] = calculator.computeMidpoint();

    std::cout << "Distância: " << distanceKm << " km" << std::endl;
    std::cout << "Ponto médio: (" << midLat << ", " << midLon << ")\n";

    // Usa o arquivo perfil.txt gerado
    calculator.loadTerrainProfile("perfil.txt");
    calculator.drawPath2D();

    // Simulando resultados de perda
    double Lbf = 120.5;
    double Lb = 145.8;
    std::string mecanismoPredominante = "Troposcatter";

    output.printResults(Lbf, Lb, mecanismoPredominante);
    output.saveResultsToFile("saida.txt", Lbf, Lb, mecanismoPredominante);

    return 0;
}
