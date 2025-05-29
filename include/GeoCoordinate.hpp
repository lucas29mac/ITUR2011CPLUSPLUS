/*
 * GeoCoordinate.hpp
 *
 *  Created on: 29 de mai. de 2025
 *      Author: Lucas Machado
 */

#ifndef GEOCOORDINATE_HPP_
#define GEOCOORDINATE_HPP_

struct GeoCoordinate {
    double latitude;
    double longitude;

    GeoCoordinate() = default;
    GeoCoordinate(double lat, double lon) : latitude(lat), longitude(lon) {}
};

#endif /* GEOCOORDINATE_HPP_ */
