#pragma once

namespace Utils {
    const double EARTH_RADIUS_KM = 6371.0;

    double haversineKm(double lat1, double lon1, double lat2, double lon2);
}
