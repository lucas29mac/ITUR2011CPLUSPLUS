#include "GeoCalculator.hpp"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace GeographicLib;

GeoCalculator::GeoCalculator(double latTx_, double lonTx_, double latRx_, double lonRx_)
    : latTx(latTx_), lonTx(lonTx_), latRx(latRx_), lonRx(lonRx_) {}

void GeoCalculator::loadTerrainProfile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erro ao abrir arquivo de terreno: " << filename << std::endl;
        return;
    }

    double height;
    while (file >> height) {
        terrainHeights.push_back(height);
    }

    file.close();
}

double GeoCalculator::computeDistanceKm() const {
    const Geodesic& geod = Geodesic::WGS84();
    double s12;
    geod.Inverse(latTx, lonTx, latRx, lonRx, s12);
    return s12 / 1000.0; // metros para km
}

std::pair<double, double> GeoCalculator::computeMidpoint() const {
    double midLat = (latTx + latRx) / 2.0;
    double midLon = (lonTx + lonRx) / 2.0;
    return {midLat, midLon};
}

void GeoCalculator::drawPath2D() const {
    if (terrainHeights.empty()) {
        std::cerr << "Perfil de terreno não carregado.\n";
        return;
    }

    const int maxHeight = *std::max_element(terrainHeights.begin(), terrainHeights.end());
    const int minHeight = *std::min_element(terrainHeights.begin(), terrainHeights.end());
    const int plotHeight = 20;
    const int plotWidth = terrainHeights.size();

    std::vector<std::string> canvas(plotHeight, std::string(plotWidth, ' '));

    // Normaliza alturas para o gráfico
    std::vector<int> normalizedHeights;
    for (double h : terrainHeights) {
        int y = static_cast<int>(
            ((h - minHeight) / (maxHeight - minHeight + 1e-6)) * (plotHeight - 1)
        );
        normalizedHeights.push_back(plotHeight - 1 - y);  // invertido (topo = 0)
    }

    // Desenha linhas entre os pontos
    for (size_t i = 0; i < normalizedHeights.size() - 1; ++i) {
        int x0 = i, x1 = i + 1;
        int y0 = normalizedHeights[i];
        int y1 = normalizedHeights[i + 1];

        // Interpola entre os dois pontos
        int dx = x1 - x0;
        int dy = y1 - y0;
        int steps = std::max(std::abs(dx), std::abs(dy));
        for (int s = 0; s <= steps; ++s) {
            int x = x0 + s * dx / steps;
            int y = y0 + s * dy / steps;
            if (y >= 0 && y < plotHeight && x >= 0 && x < plotWidth)
                canvas[y][x] = '*';
        }
    }

    std::cout << "\nPercurso 2D (Tx -> Rx):\n";
    for (const auto& row : canvas)
        std::cout << row << "\n";

    std::cout << "T" << std::string(plotWidth - 2, '-') << "R\n";
}

