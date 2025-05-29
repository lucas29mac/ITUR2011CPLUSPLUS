#ifndef GEOCALCULATOR_HPP_
#define GEOCALCULATOR_HPP_

#include <string>
#include <vector>
#include <utility>

class GeoCalculator {
public:
    GeoCalculator(double latTx, double lonTx, double latRx, double lonRx);

    void loadTerrainProfile(const std::string& filename);

    double computeDistanceKm() const;
    std::pair<double, double> computeMidpoint() const;

    void drawPath2D() const;

private:
    double latTx, lonTx;
    double latRx, lonRx;
    std::vector<double> terrainHeights;
};

#endif /* GEOCALCULATOR_HPP_ */
