#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Oct. 2023

Practice converting 4 quaternions to 3 Euler angles: roll, pitch, and yaw.

Status: DONE AND WORKS! Unit tested. Tested in real code too.

keywords: quaternions, euler angles, roll, pitch, yaw, 3-2-1 sequence, 3-2-1 rotation sequence,
ZYX rotation sequence, yaw-pitch-roll, yaw-pitch-roll sequence, yaw-pitch-roll rotation sequence,
flight dynamics, aerospace, aeronautics, aircraft, spacecraft, rockets, attitude, attitude,
flight control systems

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint quaternions_to_euler_angles.py
```

Run command:
```bash
./quaternions_to_euler_angles.py
# OR
python3 quaternions_to_euler_angles.py
```

References:
1. ***** GitHub Copilot
1. *****+ Bing Chat
1. I mostly just used GitHub Copilot and Bing Chat for this. I'd really like to use something more
   robust, like a book or even this Wikipedia article
   (https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles), but I haven't
   had a chance to dive deeply into it yet.
1. https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
1. Google search for "stack overflow conversion quaternions euler angles" -
   https://www.google.com/search?q=stack+overflow+conversion+quaternions+euler+angles&oq=stack+overflow+conversion+quaternions+euler+angles&gs_lcrp=EgZjaHJvbWUyBggAEEUYOTIGCAEQRRhAMgYIAhBFGEDSAQg5NTUzajBqNKgCALACAA&sourceid=chrome&ie=UTF-8
   1. [NEED TO STUDY & READ] https://stackoverflow.com/q/53033620/4561887 - looks REALLY USEFUL!
      Uses `scipy.spatial.transform.Rotation.from_euler()`, for instance! <========================
      https://stackoverflow.com/a/63536106/4561887
1. https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.transform.Rotation.html
    1. Quaternions to Euler angles:
       https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.transform.Rotation.from_quat.html
    1. Euler angles to quaternions:
       https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.transform.Rotation.from_euler.html
1. [NEED TO STUDY & READ] https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
1. [NEED TO STUDY & READ] https://stackoverflow.com/q/1031005/4561887 - Is there an algorithm for
   converting quaternion rotations to Euler angle rotations?
    1. These papers look useful: https://stackoverflow.com/a/2390399/4561887  <===
1. https://rotations.berkeley.edu/the-euler-angle-parameterization/
1. ********** https://web.archive.org/web/20210410215436/http://bediyap.com/programming/convert-quaternion-to-euler-rotations/
    1. Mentioned in the Wikipedia talk page:
       https://en.wikipedia.org/wiki/Talk:Conversion_between_quaternions_and_Euler_angles
1. I left a comment on the Wikipedia talk page here:
   https://en.wikipedia.org/wiki/Talk:Conversion_between_quaternions_and_Euler_angles#Changed_the_quaternion_to_Euler_angles_conversion_formula
   I am user "ERCaGuy".
1.

TODO:
1. [ ] Try out this code, and see if its results vary from mine. It might just be a different
   mathematical way to do the same thing. I'm not sure, but the pitch equation is definitely
   different, for instance:
   https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Source_code_2
1. [ ] experiment with the `scipy.spatial.transform.Rotation` class and its methods, such as
   `from_quat()` and `from_euler()`, etc., too.
1. [ ] get out my Aero books and old college notes and other resources and study up on spacial
   transformations and rotation matrices and things.
1. [ ] Gain a solid understanding of this topic of quaternions.
1. [ ] Read about "gimbal lock" and how to avoid it, too.

"""


import numpy as np

# <========================  Discussion with @Ebernardes; SciPy, and Sympy  ========================
# BOTH of the `quaternion2euler()` functions below work, and produce the exact same results for my
# test cases. However, **the Wikipedia version is the better one,** because it has had the pitch
# equation modified by @Ebernardes to use `arctan2()` instead of `arcsin()` in order to be more
# numerically stable. Ebernardes states to me: "Basically, arcsin, arccos are not as numerically
# well-behaved as arctan2, which is why we used this version when I updated the transformation code
# in https://scipy.org/." Ebernardes has helped write these functions in both SciPy and Sympy. See
# his response to me (where I am @ERCaGuy) in the Wikipedia Talk page here:
# https://en.wikipedia.org/wiki/Talk:Conversion_between_quaternions_and_Euler_angles#Changed_the_quaternion_to_Euler_angles_conversion_formula

def quaternion2euler(q):
    """
    OPTION 1: [USE THIS ONE] The Wikipedia version, with the pitch equation modified by @Ebernardes:
    https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Source_code_2

    > this implementation assumes normalized quaternion converts to Euler angles in 3-2-1 sequence.

    This means the order of the rotations is:
    1. Z-axis rotation (yaw)
    1. Y-axis rotation (pitch)
    1. X-axis rotation (roll)

    ---

    Summary:
    Convert 4 quaternion values to 3 Euler angles in degrees in the ZYX order (according to GitHub
    Copilot), AKA the 3-2-1 sequence, AKA the "yaw, pitch, roll" sequence.

    Inputs:
    q is a numpy array of shape (4,) representing a quaternion [a, b, c, d]; it can be a list,
    tuple, or numpy array of single (scalar) values OR of Pandas Series objects OR of more numpy
    arrays of values.

    Returns:
    A tuple of Euler angles (phi, theta, psi) in degrees
    - phi   = roll,  +/- 180 deg, rotation around x-axis
    - theta = pitch, +/-  90 deg, rotation around y-axis
    - psi   = yaw,   +/- 180 deg, rotation around z-axis

    References:
    1. https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Source_code_2
        1. Talk page discussion with @Ebernardes:
           https://en.wikipedia.org/wiki/Talk:Conversion_between_quaternions_and_Euler_angles#Changed_the_quaternion_to_Euler_angles_conversion_formula
    1. Bing Chat
    1. Github Copilot
    """

    w, x, y, z = q  # convert list or tuple to 4 separate variables

    # TODO: normalize the quaternion vector to be a unit vector of length 1 before processing it!
    # OR, throw a warning or error if it comes in non-normalized. This equation expect a normalized
    # quaternion vector.
    # - TODO: BEST: just fix q to be normalized if it comes in non-normalized.
    # - NB: if this code is ever expected to run in real-time, safety-critical-like or live control
    #   code, do NOT assert in it! Gracefully handle errors instead!
    assert np.isclose(np.sqrt(w**2 + x**2 + y**2 + z**2), 1), \
        "q must be a normalized unit vector of length 1!"

    # roll (x-axis rotation)
    sinr_cosp = 2*(w*x + y*z)
    cosr_cosp = 1 - 2*(x**2 + y**2)
    roll = np.arctan2(sinr_cosp, cosr_cosp)

    # pitch (y-axis rotation)
    sinp = np.sqrt(1 + 2*(w*y - x*z))
    cosp = np.sqrt(1 - 2*(w*y - x*z))
    pitch = 2*np.arctan2(sinp, cosp) - np.pi/2

    # yaw (z-axis rotation)
    siny_cosp = 2*(w*z + x*y)
    cosy_cosp = 1 - 2*(y**2 + z**2)
    yaw = np.arctan2(siny_cosp, cosy_cosp)

    # convert radians to degrees
    roll = np.degrees(roll)
    pitch = np.degrees(pitch)
    yaw = np.degrees(yaw)

    return roll, pitch, yaw


def quaternion2euler2(q):
    """
    OPTION 2 [not quite as good]: The original version from Bing Chat, which is the same as what the
    Wikipedia version **used to** have. The Wikipedia version now has in improved (more numerically
    stable) form for the pitch equation. See its notes above.

    Bing Chat produced something very similar to this equation when I asked it to write a Python
    function to convert from quaternions to Euler angles.

    Summary:
    Convert 4 quaternion values to 3 Euler angles in degrees in the ZYX order (according to GitHub
    Copilot), AKA the 3-2-1 sequence, AKA the "yaw, pitch, roll" sequence.

    Inputs:
    q is a numpy array of shape (4,) representing a quaternion [a, b, c, d]; it can be a list,
    tuple, or numpy array of single (scalar) values OR of Pandas Series objects OR of more numpy
    arrays of values.

    Returns:
    A tuple of Euler angles (phi, theta, psi) in degrees
    - phi   = roll,  +/- 180 deg, rotation around x-axis
    - theta = pitch, +/-  90 deg, rotation around y-axis
    - psi   = yaw,   +/- 180 deg, rotation around z-axis

    References:
    1. ***** Bing Chat
    1. GitHub Copilot
    1. https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    """

    # quaternion components
    w, x, y, z = q  # convert list or tuple to 4 separate variables

    # - NB: if this code is ever expected to run in real-time, safety-critical-like or live control
    #   code, do NOT assert in it! Gracefully handle errors instead!
    assert np.isclose(np.sqrt(w**2 + x**2 + y**2 + z**2), 1), \
        "q must be a normalized unit vector of length 1!"

    # roll
    phi = np.arctan2(2*(w*x + y*z), 1 - 2*(x**2 + y**2))
    # pitch
    theta = np.arcsin(2*(w*y - z*x))
    # yaw
    psi = np.arctan2(2*(w*z + x*y), 1 - 2*(y**2 + z**2))

    phi = np.degrees(phi)
    theta = np.degrees(theta)
    psi = np.degrees(psi)

    return phi, theta, psi


def convert_plus_or_minus_180_to_0_to_360(degrees):
    """
    Convert +/- 180 degrees to 0 to 360 degrees.
    """

    # Option 1:
    # if degrees < 0:
    #     degrees = 360 + degrees

    # Option 2 (same thing, but more robust because it can accept multiples of +/- 180 deg):
    degrees = degrees % 360

    return degrees


def assert_is_close(func, q, euler_angles_expected):
    euler_angles = func(q)
    assert np.isclose(euler_angles, euler_angles_expected).all(), \
        f"{euler_angles} != {euler_angles_expected}"


def test_convert_plus_or_minus_180_to_0_to_360():
    array_in = np.array([-180, -45, -90, -10, 0, 10, 45, 90, 180])
    array_out_expected = np.array([180, 315, 270, 350, 0, 10, 45, 90, 180])
    array_out1 = convert_plus_or_minus_180_to_0_to_360(array_in)
    array_out2 = array_in % 360

    assert np.array_equal(array_out1, array_out_expected)
    assert np.array_equal(array_out2, array_out_expected)

    print("All test cases passed.")


def test_quaternion2euler(func_quaternion2euler):
    # GS Note: for the quaternion to be a unit (w, x, y, z) vector of length 1, it must be true that
    # it is normalized such that sqrt(w**2 + x**2 + y**2 + z**2) = 1.
    # - Ensure this is the case for your input quaternions.

    q = (1, 0, 0, 0)
    euler_angles_expected = (0.0, 0.0, 0.0)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0, 1, 0, 0)
    euler_angles_expected = (180.0, 0.0, 0.0)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0, 0, 1, 0)
    euler_angles_expected = (180, 0.0, 180)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0, 0, 0, 1)
    euler_angles_expected = (0.0, 0.0, 180)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0, 0.1, -0.591607978, 0.8)
    euler_angles_expected = (-73.52157267757873, -9.206896221345911, -173.1156409518999)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0.5, 0.5, 0.5, 0.5)
    euler_angles_expected = (90.0, 0.0, 90.0)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0.5, -0.5, 0.5, -0.5)
    euler_angles_expected = (-90, 0, -90)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0.5, 0.5, -0.5, -0.5)
    euler_angles_expected = (90, 0, -90)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0.5, -0.5, -0.5, 0.5)
    euler_angles_expected = (-90, 0, 90)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0.70710678, 0, 0, 0.70710678)
    euler_angles_expected = (0.0, 0.0, 90)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    q = (0.70710678, 0, 0.70710678, 0)
    euler_angles_expected = (0.0, 89.995, 0.0)
    assert_is_close(func_quaternion2euler, q, euler_angles_expected)

    print("All test cases passed.")


def run_tests():
    """
    Run some basic unit tests.
    """
    test_quaternion2euler(quaternion2euler)
    test_quaternion2euler(quaternion2euler2)

    test_convert_plus_or_minus_180_to_0_to_360()


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    run_tests()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/quaternions_to_euler_angles.py
    All test cases passed.
    All test cases passed.
    All test cases passed.

"""
