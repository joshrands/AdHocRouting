# Ad-hoc Routing Framework for Hardware and Simulation

### NASA SmallSat Project - Colorado School of Mines

Name | Email | Cell
--- | --- | ---
Zachary Smeton | zsmeton@yahoo.com | (303) 880-9437
Joshua Rands | joshrands1@gmail.com


## Description

Classes designed for physical implementation as well as simulated implementation of an ad-hoc network on a single decentralized subnet.

## Requirements
cmake
git
python3 >= 3.7
libpcap-dev

## Running the code

This codebase is organized into several 'modules'. Modules are code grouped in a subdirectory of the main directory. Each module has been developed with a built in test framework and is compiled into a static library (.a) file for linking capabilities. 

### Testing Modules

Each module has a 'test.cc' file used for testing. Use the following tests to test a module: 

1. Navigate to the module directory in a terminal
2. Type 'make clean'
3. Type 'make'
4. Type './test'

The tests for this module should run. PASS indicates the test passed and FAIL indicates that the test failed. 

### Using NS3

NS3 is a network simulator. 

A bash script has been created to aid in the installation of ns3. NOTE: If you decide to not use this script and instead use a different version of ns3, you will have to manually install the CSM patch and adhoc-routing module located in the ns-3-allinone/ns-3.28 directory of this repository. 

```bash
cd ns-3-allinone
bash install-ns3-csm.sh
cd ns-3.28
./waf configure --build-profile=optimized
./waf
sudo ./waf install
```

The CSM custom adhoc-routing module should now be successfully built and installed on your system. To test this, run the following example from inside the ns-3.28 directory. You should see a window pop up with a bunch of nodes communicating using the CSM adhoc-routing module. 

```bash
./waf --run adhoc-example --vis
```

#### IMPORTANT: If any changes are made to modules in this repository that you would like to see reflected in ns3 you must run the update-ns3.sh bash script. This script copies this repository's modules into the correct folder in the ns3 adhoc-routing module. Similarly, if you create a NEW module in this repository, you will have to update the update-ns3.sh bash script to copy your module into the ns3 adhoc-routing module. 

## Modules Overview

### ADHOC

Infrastructure for providing ad-hoc communication. 
[code here](adhoc)

### HARDWARE

Hardware interfacing for components of ad-hoc routing.
[code here](hardware)

### SIMULATION

Simulation interfacing for components of ad-hoc routing.
[code here](simulation)

### AODV 

AODV Protocol implemented from AODV RFC3561 (https://www.ietf.org/rfc/rfc3561.txt).
[code here](aodv)

### HELLO_MONITOR

Hello messages to provide primitive network monitoring of one hop neighbors. 
[code here](hello_monitor)

### REM

Implementation of REgression-based network Monitoring (https://dl.acm.org/doi/abs/10.1145/3360774.3360795)
[code here](rem)

### SOCKET

UDP Sockets and helper classes. 
[code here](socket)

## To-Do
- Completely redo the file system and makefiles to use dependencies and actually use the static libraries, the Makefiles currently are awful
  - Use hidden directories to store build files and dependency files
  - Use structures in each file system to hold src (.cc) and include (.h)
  - Make sure all include paths are not relative ("../rssi/")
  - Use -L -l to link the static libraries
  - Figure out how to avoid recompiling every file every time we make
- Fully doxygen document the code base
- Unify the Style to use one style guideline
- Create stoppable threads
