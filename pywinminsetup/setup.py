#!/usr/bin/env python3
from setuptools import setup, find_packages
from os import path

here = path.abspath(path.dirname(__file__))

setup(
    name='pywinminsetup',  # Required
    version='0.0.1',  # Required
    description='winmin-setup helper script',  # Optional
    author='Victor Fuentes',  # Optional
    author_email='hyruleterminatirforce@gmail.com',  # Optional
    #packages=find_packages(where='pywinminsetup'),  # Required
    python_requires='>=3.5, <4',
    project_urls={  # Optional
        'Source': 'https://github.com/vlinkz',
    },
    packages=['pywinminsetup'],
    scripts=['pywinminsetup/pywinminsetup.py'],
)
