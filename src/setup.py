from setuptools import setup
from setuptools.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize

extensions = [Extension("samaritan",
                        sources = ["samaritan.pyx","main.cpp",'mods/Node.cpp',
                        'mods/Manager.cpp','mods/Mesher.cpp'],
                        #extra_link_args = ['-static']
                        )
]
setup(
    cmdclass = {'build_ext':build_ext},
    ext_modules = cythonize(extensions)
) # end setup
