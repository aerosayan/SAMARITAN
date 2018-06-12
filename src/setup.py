from setuptools import setup,Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize

setup(
    cmdclass = {'build_ext':build_ext},
    ext_modules = cythonize("*.pyx")
) # end setup
