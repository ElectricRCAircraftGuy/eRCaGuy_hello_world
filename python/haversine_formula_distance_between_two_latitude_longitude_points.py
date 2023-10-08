#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Oct. 2023

Find the curved earth (great circle) distance between two latitude and longitude points using the
Haversine formula.

Also convert the latitude/longitude points to x/y points in meters, and use the Pythagorean theorem
to find the straight-line distance between the two converted x/y points, and compare the two
results.

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint haversine_formula_distance_between_two_latitude_longitude_points.py
```

Run command:
```bash
./haversine_formula_distance_between_two_latitude_longitude_points.py
# OR
python3 haversine_formula_distance_between_two_latitude_longitude_points.py
```

References:
1. GitHub Copilot
1. ***** https://en.wikipedia.org/wiki/Haversine_formula
1. *****+ https://stackoverflow.com/a/29546836/4561887
1.

"""

# Local imports
import pyproj_latitude_and_longitude_to_x_y_coordinate_transformation_lib as lonlat2xy

# 3rd party imports
import numpy as np

# Standard library imports
# NA


# Note: this could easily be wrapped up into a singleton class, if desired.

# meters; see: https://en.wikipedia.org/wiki/Earth_radius#Global_radii
EARTH_EQUATORIAL_RADIUS_M = 6378137.0

def get_haversine_distance(lon1_deg, lat1_deg, lon2_deg, lat2_deg):
    """
    Find the curved earth (great circle) distance between two latitude and longitude points using
    the Haversine formula.

    All inputs can be numpy arrays or scalars. If arrays, they must all be the same size.
    Arrays will be element-wise operated on through vectorization.

    d = 2 * r * arcsin(sqrt(sin^2((lat2-lat1)/2) + cos(lat1) * cos(lat2) * sin^2((lon2-lon1)/2))),
    where r is the radius of the Earth and d is the distance between the two points.

    Inputs:
    - lon1_deg: longitude of point 1, in degrees
    - lat1_deg: latitude of point 1, in degrees
    - lon2_deg: longitude of point 2, in degrees
    - lat2_deg: latitude of point 2, in degrees

    Outputs:
    - distance_m: distance between the two points, in meters
    """

    lon1_rad, lat1_rad, lon2_rad, lat2_rad = \
        map(np.radians, [lon1_deg, lat1_deg, lon2_deg, lat2_deg])

    delta_lat_rad = lat2_rad - lat1_rad
    delta_lon_rad = lon2_rad - lon1_rad

    dist_m = 2 * EARTH_EQUATORIAL_RADIUS_M * np.arcsin(
        np.sqrt(
            np.sin(delta_lat_rad/2)**2 +
            np.cos(lat1_rad) * np.cos(lat2_rad) * np.sin(delta_lon_rad/2)**2
        )
    )

    return dist_m


converter = lonlat2xy.LatLonToXYConverter()


def get_pythagorean_distance(lon1_deg, lat1_deg, lon2_deg, lat2_deg):
    """
    Convert the latitude/longitude points to x/y points in meters, and use the Pythagorean theorem
    to find the straight-line distance between the two converted x/y points.
    """

    x1_m, y1_m = converter.convert_lonlat_to_xy(lon1_deg, lat1_deg)
    x2_m, y2_m = converter.convert_lonlat_to_xy(lon2_deg, lat2_deg)

    delta_x_m = x2_m - x1_m
    delta_y_m = y2_m - y1_m

    dist_m = np.sqrt(delta_x_m**2 + delta_y_m**2)

    return dist_m


def main():
    """
    The main function of this program.
    """

    # Define two points in latitude and longitude
    NEW_YORK_CITY_LON_LAT_DEG = (-74.0060, 40.7128)  # (longitude, latitude)
    LONDON_LON_LAT_DEG = (-0.1278, 51.5074)  # (longitude, latitude)

    haversine_dist_m = get_haversine_distance(
        NEW_YORK_CITY_LON_LAT_DEG[0], NEW_YORK_CITY_LON_LAT_DEG[1],
        LONDON_LON_LAT_DEG[0], LONDON_LON_LAT_DEG[1]
    )

    pythagorean_dist_m = get_pythagorean_distance(
        NEW_YORK_CITY_LON_LAT_DEG[0], NEW_YORK_CITY_LON_LAT_DEG[1],
        LONDON_LON_LAT_DEG[0], LONDON_LON_LAT_DEG[1]
    )

    print(f"Distance between New York City and London:")
    # Haversine Formula is more accurate, but it still has some error, as the earth is not a perfect
    # sphere. It's an oblate spheroid.
    #
    # The Haversine formula assumes a perfect sphere, and in my implementation of it, I assumed that
    # the Earth has a radius equal to its radius at the equator, which of course is not true unless
    # you're exactly at the equator going exactly East or West.
    print(f"    Haversine formula distance [more accurate]: {haversine_dist_m/1000} km")
    print(f"    Pythagorean distance:                       {pythagorean_dist_m/1000} km")


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/haversine_formula_distance_between_two_latitude_longitude_points.py
    Distance between New York City and London:
        Haversine formula distance [more accurate]: 5576.462122556478 km
        Pythagorean distance:                       8406.442292709182 km

"""
