#ifndef TERRAINREADER_HPP
#define TERRAINREADER_HPP

#include <string>
#include <gdal_priv.h>  // Inclua o cabeçalho GDAL

class TerrainReader {
public:
    TerrainReader(const std::string& filepath);
    ~TerrainReader();  // Adicione o destrutor

    double getElevation(double latitude, double longitude) const;

private:
    void loadDataset(const std::string& filepath);

    GDALDataset* dataset;  // Mude de void* para GDALDataset*
    double geoTransform[6];
    int rasterXSize;
    int rasterYSize;
};

#endif
