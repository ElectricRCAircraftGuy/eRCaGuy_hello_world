"""
pytest_hello_world_demo_test.py - Basic pytest example

GS
Oct. 2025

Originally written by GitHub Copilot. 

-----------------------
Key pytest Concepts:
-----------------------
1. File naming: Test files should start with `test_` or end with `_test.py`
2. Function naming: Test functions must start with `test_`
3. Assertions: Use simple `assert` statements to check if things are correct
4. Running tests: Use `python3 -m pytest filename.py`


-----------------------
Simple pytest commands:
-----------------------

# Run all tests in a file
python3 -m pytest pytest_hello_world_demo_test.py

# Run with verbose output
python3 -m pytest pytest_hello_world_demo_test.py -v

# Run a specific test function
python3 -m pytest pytest_hello_world_demo_test.py::test_hello_world

# Run all tests in current directory
python3 -m pytest

# Stop after first failure
python3 -m pytest -x

# Show local variables in failures
python3 -m pytest -l

# Run only failed tests from last run
python3 -m pytest --lf
"""


def hello_world():
    """A simple function to test"""
    return "Hello, World!"

def add_numbers(a, b):
    """Another simple function to test"""
    return a + b

# ===== TESTS =====
# Test functions must start with "test_"

def test_hello_world():
    """Test the hello_world function"""
    result = hello_world()
    assert result == "Hello, World!"

def test_add_numbers():
    """Test the add_numbers function"""
    result = add_numbers(2, 3)
    assert result == 5

def test_add_negative_numbers():
    """Test adding negative numbers"""
    result = add_numbers(-1, -2)
    assert result == -3

def test_add_zero():
    """Test adding with zero"""
    result = add_numbers(5, 0)
    assert result == 5

# This test will fail on purpose to show what failure looks like
def test_that_will_fail():
    """This test demonstrates a failure"""
    result = add_numbers(2, 2)
    assert result == 5  # This will fail because 2 + 2 = 4, not 5
