#include "TerrainReader.hpp"
#include <gdal.h>
#include <gdal_priv.h>
#include <stdexcept>

TerrainReader::TerrainReader(const std::string& filepath)
    : dataset(nullptr) {
    GDALAllRegister();
    dataset = static_cast<GDALDataset*>(GDALOpen(filepath.c_str(), GA_ReadOnly));
    if (!dataset) {
        throw std::runtime_error("Falha ao abrir arquivo de terreno");
    }
    dataset->GetGeoTransform(geoTransform);
    rasterXSize = dataset->GetRasterXSize();
    rasterYSize = dataset->GetRasterYSize();
}

TerrainReader::~TerrainReader() {
    if (dataset) {
        GDALClose(dataset);
    }
}

double TerrainReader::getElevation(double latitude, double longitude) const {
    if (!dataset) {
        throw std::runtime_error("Dataset não carregado");
    }

    // Conversão de coordenadas geográficas para pixels
    double x = (longitude - geoTransform[0]) / geoTransform[1];
    double y = (latitude - geoTransform[3]) / geoTransform[5];

    if (x < 0 || x >= rasterXSize || y < 0 || y >= rasterYSize) {
        return 0.0; // Fora dos limites do arquivo
    }

    float elevation = 0.0f;
    GDALRasterBand* band = dataset->GetRasterBand(1);
    CPLErr err = band->RasterIO(GF_Read,
                               static_cast<int>(x),
                               static_cast<int>(y),
                               1, 1,
                               &elevation,
                               1, 1,
                               GDT_Float32,
                               0, 0);

    if (err != CE_None) {
        throw std::runtime_error("Erro ao ler dados de elevação");
    }

    return static_cast<double>(elevation);
}
