/*
 * TerrainHeader.hpp
 *
 *  Created on: 29 de mai. de 2025
 *      Author: Lucas Machado
 */

#ifndef TERRAINREADER_HPP
#define TERRAINREADER_HPP

#include <string>
#include <vector>

class TerrainReader {
public:
    TerrainReader(const std::string& filepath);

    // Retorna a elevação (em metros) para uma coordenada geográfica
    double getElevation(double latitude, double longitude) const;

private:
    void loadDataset(const std::string& filepath);

    void* dataset; // ponteiro para o dataset GDAL
    double geoTransform[6];
    int rasterXSize;
    int rasterYSize;
};

#endif // TERRAINREADER_HPP

