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

void GeoCalculator::setTerrainProfile(const std::vector<double>& profile) {
    terrainProfile = profile;
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
    if (terrainProfile.empty()) {
        std::cerr << "Perfil de terreno não carregado.\n";
        return;
    }

    const int maxHeight = *std::max_element(terrainProfile.begin(), terrainProfile.end());
    const int minHeight = *std::min_element(terrainProfile.begin(), terrainProfile.end());
    const int plotHeight = 20;
    const int plotWidth = terrainProfile.size();

    std::vector<std::string> canvas(plotHeight, std::string(plotWidth, ' '));

    std::vector<int> normalizedHeights;
    for (double h : terrainProfile) {
        int y = static_cast<int>(
            ((h - minHeight) / (maxHeight - minHeight + 1e-6)) * (plotHeight - 1)
        );
        normalizedHeights.push_back(plotHeight - 1 - y);
    }

    for (size_t i = 0; i < normalizedHeights.size() - 1; ++i) {
        int x0 = i, x1 = i + 1;
        int y0 = normalizedHeights[i];
        int y1 = normalizedHeights[i + 1];

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


