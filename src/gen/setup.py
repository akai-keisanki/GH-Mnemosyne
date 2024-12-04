# python3 setup.py build_ext --inplace

from setuptools import setup, Extension
from pybind11 import get_include

setup(
    name = 'genhor',
    ext_modules = [
        Extension(
            'genhor', sources = ['main.cpp'], language = 'c++',
            include_dirs = [get_include()]
        )
    ]
)
