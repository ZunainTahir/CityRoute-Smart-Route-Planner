#pragma once
// ---------------------------------------------------------------------------
// Utils.h  --  INTERFACE CONTRACT (Day 1)
// Owner: Member 1.  Implementation: src/Utils.cpp (Day 5).
// Declarations only. Other members may code against these signatures now.
// ---------------------------------------------------------------------------

namespace Utils {

constexpr double EARTH_RADIUS_KM = 6371.0;

// Great-circle (Haversine) distance in kilometres between two points.
// Inputs: latitude/longitude in decimal degrees.
double haversineKm(double lat1, double lon1, double lat2, double lon2);

}  // namespace Utils
