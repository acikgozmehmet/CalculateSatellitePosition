# Calculation of Satellite Position from Ephemeris Data

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
In this project, position of any satellite at any epoch is calculated  using broadcast ephemeris data. 
The main driver for the project is CalcSatPos_Project.

Project contains the following subfolders/class in addition to the unit test (Unit_CalcSatPos.cpp)
* **BrdcEph**

  It contains the class which loads the broadcast ephemeris file and calculates the ECEF position of the satellite at the desired epoch.
It also generates a summary file about the availability of the satellites for the input ephemeris file. The extension of the file  *.sum

* **Constants**

  It contains the defined data types and constant values for the project
  
* **TimeSystems**
  
  It provides the conversion among the time systems used in GNSS applications.

## Technologies
Project is built in C++

## Setup/Availability
install it locally using git:

```
$ git clone https://github.com/acikgozmehmet/CalculateSatellitePosition.git
cd CalculateSatellitePosition
unzip CalcSatPos_Project
```
