from setuptools import setup, find_packages

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name = "phantom",
    version = "v0.0.1",
    author = "Matthew Maxwell",
    author_email = "maxwellmattryan" + "@" + "gmail.com",
    description = "Phase distortion prototyping in python",
    long_description = long_description,
    url = "https://github.com/maxwellmattryan/phantom",
    packages = find_packages(),
    classifiers = [
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent"
    ],
    python_requires = ">=3.7"
)