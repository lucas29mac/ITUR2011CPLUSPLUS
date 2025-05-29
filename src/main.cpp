#include "InputManager.hpp"
#include "OutputManager.hpp"
#include "GeoCalculator.hpp"
#include "TerrainReader.hpp"

#include <cstdlib>   // srand, rand
#include <ctime>     // time
#include <fstream>
#include <iostream>
#include <string>

int main() {
    // --- Geração do arquivo de perfil de terreno sintético (perfil.txt) ---
    {
        std::ofstream file("perfil.txt");
        if (!file) {
            std::cerr << "Erro ao criar arquivo perfil.txt\n";
            return 1;
        }

        std::srand(std::time(nullptr)); // inicializa a semente aleatória
        const int nPoints = 100;

        for (int i = 0; i < nPoints; ++i) {
            double height = std::rand() % 501; // altura entre 0 e 500 metros
            file << height << "\n";
        }

        std::cout << "Arquivo perfil.txt criado com " << nPoints << " pontos de altura aleatória.\n";
    }

    // --- Leitura de entradas e inicialização de coordenadas ---
    InputManager& inputManager = InputManager::getInstance();
    OutputManager output;

    inputManager.readInputs();
    inputManager.printInputs();

    GeoCoordinate tx = inputManager.getTxCoordinate();
    GeoCoordinate rx = inputManager.getRxCoordinate();

    // --- Leitura real de elevação via GDAL para o transmissor ---
    try {
        TerrainReader terrain("/home/imbeluser/Documents/compartilhada/rj/SF-23-Z-B.tif");

        double elevationTx = terrain.getElevation(tx.latitude, tx.longitude);
        double elevationRx = terrain.getElevation(rx.latitude, rx.longitude);

        std::cout << "Elevação no transmissor (" << tx.latitude << ", " << tx.longitude << "): "
                  << elevationTx << " m\n";

        std::cout << "Elevação no receptor (" << rx.latitude << ", " << rx.longitude << "): "
                  << elevationRx << " m\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao acessar dados de elevação: " << e.what() << std::endl;
        return 1;
    }

    // --- Cálculos geográficos principais ---
    GeoCalculator calculator(tx.latitude, tx.longitude, rx.latitude, rx.longitude);

    double distanceKm = calculator.computeDistanceKm();
    auto [midLat, midLon] = calculator.computeMidpoint();

    std::cout << "Distância: " << distanceKm << " km\n";
    std::cout << "Ponto médio: (" << midLat << ", " << midLon << ")\n";

    // --- Leitura de perfil e visualização ---
    calculator.loadTerrainProfile("perfil.txt");
    calculator.drawPath2D();

    // --- Simulação e saída dos resultados finais ---
    double Lbf = 120.5;
    double Lb = 145.8;
    std::string mecanismoPredominante = "Troposcatter";

    output.printResults(Lbf, Lb, mecanismoPredominante);
    output.saveResultsToFile("saida.txt", Lbf, Lb, mecanismoPredominante);

    return 0;
}
