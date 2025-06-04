#include "InputManager.hpp"
#include "OutputManager.hpp"
#include "GeoCalculator.hpp"
#include "TerrainReader.hpp"

#include <iostream>
#include <vector>

int main() {
    // --- Leitura de entradas e inicialização de coordenadas ---
    InputManager& inputManager = InputManager::getInstance();
    OutputManager output;

    inputManager.readInputs();
    inputManager.printInputs();

    GeoCoordinate tx = inputManager.getTxCoordinate();
    GeoCoordinate rx = inputManager.getRxCoordinate();

    // --- Leitura do terreno via GDAL (arquivo SRTM) ---
    try {
        TerrainReader terrain("/home/imbeluser/Documents/compartilhada/rj/SF-23-Z-B.tif");

        // Obtém elevações nos pontos extremos
        double elevationTx = terrain.getElevation(tx.latitude, tx.longitude);
        double elevationRx = terrain.getElevation(rx.latitude, rx.longitude);

        std::cout << "\nElevação no transmissor (" << tx.latitude << ", " << tx.longitude << "): "
                  << elevationTx << " m\n";
        std::cout << "Elevação no receptor (" << rx.latitude << ", " << rx.longitude << "): "
                  << elevationRx << " m\n";

        // --- Cálculos geográficos principais ---
        GeoCalculator calculator(tx.latitude, tx.longitude, rx.latitude, rx.longitude);

        double distanceKm = calculator.computeDistanceKm();
        auto [midLat, midLon] = calculator.computeMidpoint();

        std::cout << "\nDistância: " << distanceKm << " km\n";
        std::cout << "Ponto médio: (" << midLat << ", " << midLon << ")\n";

        // --- Construção do perfil de terreno real ao longo do caminho ---
        const int nSamples = 100;  // Número de pontos ao longo do percurso
        std::vector<double> profile;

        for (int i = 0; i < nSamples; ++i) {
            double t = static_cast<double>(i) / (nSamples - 1);

            // Interpolação linear entre Tx e Rx
            double lat = tx.latitude + t * (rx.latitude - tx.latitude);
            double lon = tx.longitude + t * (rx.longitude - tx.longitude);

            double elev = terrain.getElevation(lat, lon);
            profile.push_back(elev);
        }

        // --- Visualização do perfil real ---
        calculator.setTerrainProfile(profile);
        calculator.drawPath2D();

        // --- Simulação e saída dos resultados finais ---
        double Lbf = 120.5;  // Valores exemplo - substitua pelos cálculos reais
        double Lb = 145.8;
        std::string mecanismoPredominante = "Troposcatter";

        output.printResults(Lbf, Lb, mecanismoPredominante);
        output.saveResultsToFile("saida.txt", Lbf, Lb, mecanismoPredominante);

    } catch (const std::exception& e) {
        std::cerr << "\nErro no processamento: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
