#ifndef GEOCALCULATOR_HPP_
#define GEOCALCULATOR_HPP_

#include <string>
#include <vector>
#include <utility>

class GeoCalculator {
public:
    GeoCalculator(double latTx, double lonTx, double latRx, double lonRx);

    void setTerrainProfile(const std::vector<double>& profile);


    double computeDistanceKm() const;
    std::pair<double, double> computeMidpoint() const;

    void drawPath2D() const;

private:
    double latTx, lonTx, latRx, lonRx;
    std::vector<double> terrainProfile;

};

#endif /* GEOCALCULATOR_HPP_ */
