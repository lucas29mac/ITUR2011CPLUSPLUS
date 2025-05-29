#include "TerrainReader.hpp"
#include <gdal_priv.h>
#include <cpl_conv.h>
#include <stdexcept>
#include <iostream>

TerrainReader::TerrainReader(const std::string& filepath) {
    GDALAllRegister();
    loadDataset(filepath);
}

void TerrainReader::loadDataset(const std::string& filepath) {
    dataset = (void*) GDALOpen(filepath.c_str(), GA_ReadOnly);
    if (!dataset) {
        throw std::runtime_error("Erro ao abrir o arquivo de terreno: " + filepath);
    }

    GDALDataset* gdalDataset = static_cast<GDALDataset*>(dataset);

    if (gdalDataset->GetGeoTransform(geoTransform) != CE_None) {
        throw std::runtime_error("Erro ao obter transformações geográficas.");
    }

    rasterXSize = gdalDataset->GetRasterXSize();
    rasterYSize = gdalDataset->GetRasterYSize();
}

double TerrainReader::getElevation(double latitude, double longitude) const {
    GDALDataset* gdalDataset = static_cast<GDALDataset*>(dataset);
    GDALRasterBand* band = gdalDataset->GetRasterBand(1);

    int pixel = static_cast<int>((longitude - geoTransform[0]) / geoTransform[1]);
    int line  = static_cast<int>((latitude  - geoTransform[3]) / geoTransform[5]);

    if (pixel < 0 || pixel >= rasterXSize || line < 0 || line >= rasterYSize) {
        std::cerr << "Coordenada fora dos limites do raster.\n";
        return -9999;
    }

    float value = 0.0;
    CPLErr err = band->RasterIO(GF_Read, pixel, line, 1, 1, &value, 1, 1, GDT_Float32, 0, 0);
    if (err != CE_None) {
        std::cerr << "Erro ao ler dado de elevação.\n";
        return -9999;
    }

    return static_cast<double>(value);
}
