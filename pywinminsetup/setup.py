#!/usr/bin/env python3
from setuptools import setup, find_packages
from os import path

here = path.abspath(path.dirname(__file__))

setup(
    name='pywinminsetup',
    version='0.0.1',
    description='winmin-setup helper script',
    author='Victor Fuentes',
    author_email='hyruleterminatirforce@gmail.com',
    python_requires='>=3.5, <4',
    project_urls={
        'Source': 'https://github.com/vlinkz',
    },
    packages=['pywinminsetup'],
    scripts=['pywinminsetup/pywinminsetup.py'],
)
