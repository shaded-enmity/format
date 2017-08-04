from distutils.core import setup, Extension
from sys import version_info, exit

if version_info.major != 2:
    print('Only Python2.X is supported')
    exit(-1)

fmtmod = Extension('format',
                   sources = ['format.c'])

setup (name = 'format',
       version = '1.0',
       author = 'Pavel Odvody',
       author_email = 'podvody@redhat.com',
       license = 'MIT',
       keywords = 'string interpolation',
       description = 'Faux string interpolation for Python2.7',
       url = 'https://github.com/shaded-enmity/format',
       ext_modules = [fmtmod])
