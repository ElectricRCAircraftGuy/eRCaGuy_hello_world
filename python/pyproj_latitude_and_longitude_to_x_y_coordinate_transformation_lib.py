#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Oct. 2023

Practice converting latitude and longitude to x and y coordinates using the pyproj library.
Convert: deg lat/lon to meters x/y, and vice versa.
This time wrap it up in a singleton class so it can be used as a library.

Status: wip

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pyproj_latitude_and_longitude_to_x_y_coordinate_transformation.py
```

Run command:
```bash
./pyproj_latitude_and_longitude_to_x_y_coordinate_transformation.py
# OR
python3 pyproj_latitude_and_longitude_to_x_y_coordinate_transformation.py
```

References:
1. Bing AI [must open in Microsoft Edge browser to view]: https://sl.bing.net/h9jlizHUFoG
    1. Prompt summary: "Convert latitude and longitude from degrees to meters, using Python."
1. GitHub Copilot
1. https://epsg.io/
    1. https://epsg.io/map
    1. ***** https://epsg.io/ --> click "Transform coordinates" blue link near top center left
    1. https://epsg.io/transform
    1. https://epsg.io/3857
    1. https://epsg.io/4326
1. pyproj (cartographic **proj**ections and coordinate transformations library).
    1. https://pyproj4.github.io/pyproj/stable/index.html
    1. https://github.com/pyproj4/pyproj
1.

"""

import pyproj # cartographic **proj**ections and coordinate transformations library
import unittest

# Define CRSs (Coordinate Reference Systems) for the two coordinate systems we want to convert
#
# WGS84 (World Geodetic System 1984) lon/lat in degrees
# See: https://epsg.io/4326
crs_wgs84_latlon = pyproj.CRS.from_epsg(4326)
# WGS84 (World Geodetic System 1984) x/y in meters
# See: https://epsg.io/3857
crs_wgs84_xy = pyproj.CRS.from_epsg(3857)

# Create transformers to convert between WGS84 lon/lat (deg) and WGS84 x/y (m)
# See:
# https://pyproj4.github.io/pyproj/stable/api/transformer.html#pyproj.transformer.Transformer.from_crs
transformer_latlon_to_xy = pyproj.Transformer.from_crs(crs_wgs84_latlon, crs_wgs84_xy)
transformer_xy_to_latlon = pyproj.Transformer.from_crs(crs_wgs84_xy, crs_wgs84_latlon)


def convert_lonlat_to_xy(lon_deg, lat_deg):
    """
    Convert longitude and latitude coordinates in degrees to x and y in meters.
    NB: the input order is lon, lat!--since lon corresponds to x and lat corresponds to y.
    """
    # NB: input order to this function is lat, lon.
    x_m, y_m = transformer_latlon_to_xy.transform(lat_deg, lon_deg)
    return x_m, y_m


def convert_xy_to_lonlat(x_m, y_m):
    """
    Convert x and y coordinates in meters to longitude and latitude in degrees.
    """
    # NB: the output order is lat, lon!
    lat_deg, lon_deg = transformer_xy_to_latlon.transform(x_m, y_m)

    # NB: the return order is swapped to lon, lat!--since lon corresponds to x and lat
    # corresponds to y.
    return lon_deg, lat_deg





class TestCoordinateTransformations(unittest.TestCase):
    # Phoenix, AZ, manually chosen off of this map:
    # https://epsg.io/map#srs=4326&x=-112.081146&y=33.456651&z=10&layer=streets
    LON_DEG = -112.081146
    LAT_DEG = 33.456651
    # Expected x, y meter values are calculated by this calculator online here, by manually
    # inputting the longitude and latitude in degrees from just above:
    # https://epsg.io/transform#s_srs=4326&t_srs=3857&x=NaN&y=NaN
    X_EXPECTED_M = -12476816.10024655  # meters
    Y_EXPECTED_M = 3956074.7956480593  # meters

    def test_convert_lonlat_to_xy(self):
        x_m, y_m = convert_lonlat_to_xy(self.LON_DEG, self.LAT_DEG)
        # print(f"x_m, y_m = {x_m}, {y_m}") # debugging
        self.assertAlmostEqual(x_m, self.X_EXPECTED_M, places=10)
        self.assertAlmostEqual(y_m, self.Y_EXPECTED_M, places=10)

    def test_convert_xy_to_lonlat(self):
        """
        Test the reverse of the conversion above.
        """
        lon_deg, lat_deg = convert_xy_to_lonlat(self.X_EXPECTED_M, self.Y_EXPECTED_M)
        self.assertAlmostEqual(lon_deg, self.LON_DEG, places=10)
        self.assertAlmostEqual(lat_deg, self.LAT_DEG, places=10)


def main():
    """
    The main function of this program.
    """
    unittest.main()  # run unit tests

    # NB: nothing runs past this point! The unit tests above run and exit.
    # print("\033[32mAll unit tests passed!\033[0m")


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/pyproj_latitude_and_longitude_to_x_y_coordinate_transformation.py
    ..
    ----------------------------------------------------------------------
    Ran 2 tests in 0.000s

    OK

"""
