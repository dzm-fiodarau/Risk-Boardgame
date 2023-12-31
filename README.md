[![Contributors][contributors-shield]][contributors-url]
[![MIT License][license-shield]][license-url]
[![GitHub last commit (branch)][last-commit-shield]][last-commit-url]

<br />
<div align="center">
  <p align="center">
    <h1 align="center">COMP345-RISK</h1>
    Turn-based, real-time strategy game built entirely in c++
    <br />
    <a href="https://github.com/dzm-fiodarau/COMP345-RISK/issues">Report Bug</a>
    ·
    <a href="https://github.com/dzm-fiodarau/COMP345-RISK/issues">Request a Feature</a>
  </p>
</div>

## About
This is a Risk console game developed in the context of a school assignment. 


## Installation

### Prerequisites
[![Next][git-shield]][git-url]
[![Next][cmake-shield]][cmake-url]
[![Next][g++-shield]][g++-url]


First, get the source code of the program. You can download the project files, or you can do the same through the command line (see below).

```shell
# Copy repository
git clone https://github.com/dzm-fiodarau/COMP345-RISK

# Enter directory of cloned repo
cd COMP345-RISK
```

Note that the project uses `CMake` to generate project files from the configuration in the `CMakeLists.txt` file.
Building using `CMake` is preferred. 
Below we build and run the project using `g++` and `CMake`.

### 1. Just with **g++**
```shell
# FOR WINDOWS
# In the directory of the source code
# Create output directory
mkdir bin
```
After making the build/bin directory, then you need to build the project. This can be done using the following command below:
```shell
g++ -o ./bin/COMP345_RISK -std=c++20 -I./headers ./src/*.cpp ./src/commandprocessing/*.cpp ./src/drivers/*.cpp ./src/gameengine/*.cpp ./src/player/*.cpp
```
After running the command, we can run the executable directly:
```shell
# Run built executable
./bin/COMP345_RISK
```

### 2. Using **CMake**
```shell
# FOR WINDOWS
# In the directory of the source code
# Create build directory
mkdir bin

# Generates the build files given the project files 
cmake -S ./ -B ./bin/

# Generates the executable from the build files
cmake --build ./bin/

# Run build executable
./bin/Debug/COMP345_RISK
```

## Using the program
After obtaining an executable, you can then specify additional command line arguments:

### Specifying the input
You can specify from where the program will take input from. You can put commands in a file and watch the game play. By default, the game is set to console/player input.
```shell
# Assuming the name of the executable is 'COMP345_RISK'
# File input
./COMP345_RISK [-file] FILEPATH

# Console input
./COMP345_RISK [-console]

# Or without any arguments specified
./COMP345_RISK
```



[contributors-shield]: https://img.shields.io/github/contributors/dzm-fiodarau/COMP345-RISK.svg?style=for-the-badge
[contributors-url]: https://github.com/dzm-fiodarau/COMP345-RISK/graphs/contributors

[license-shield]: https://img.shields.io/github/license/dzm-fiodarau/COMP345-RISK.svg?style=for-the-badge
[license-url]: https://github.com/dzm-fiodarau/COMP345-RISK/blob/main/LICENSE

[last-commit-shield]: https://img.shields.io/github/last-commit/dzm-fiodarau/COMP345-RISK/main?style=for-the-badge
[last-commit-url]: https://github.com/dzm-fiodarau/COMP345-RISK/graphs/commit-activity

[cmake-shield]: https://img.shields.io/badge/CMake-083464?style=for-the-badge&logo=cmake&logoColor=083464&labelColor=FFFFFF
[cmake-url]: https://cmake.org/download/

[git-shield]: https://img.shields.io/badge/git-000000?style=for-the-badge&logo=git&logoColor=FFFFFF&labelColor=000000
[git-url]: https://git-scm.com/downloads

[g++-shield]: https://img.shields.io/badge/g%2B%2B-f9ccab?style=for-the-badge&logo=gnu&labelColor=%23322d27
[g++-url]: https://gcc.gnu.org/
