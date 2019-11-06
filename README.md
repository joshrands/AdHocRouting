# Ad hoc Network Routing Protocol Implementations

### NASA SmallSat Project - Colorado School of Mines

Classes designed for physical implementation and simulated implementation of an ad-hoc network on a single decentralized subnet.

Author: Josh Rands

## To Do

### AODV 

AODV Protocol: https://www.ietf.org/rfc/rfc3561.txt

1. Add functions for generating RREQ
2. Add functions for generating RREP
  - Create struct for packet format (section 5.2)
  - Add check in RREQ if time for RREP (section 6.6)
  - Unicast RREP message back to orig (section 6.7)
3. Add functions for generating RERR
  - Create struct for packet format (section 5.3)
  - Generate RERR in all 3 situations (section 6.11)
4. Add TTL for RREQ dissemination (section 6.4)
5. Add AODVRoutingTable updates 

### Hardware
1. Add adhoc/wifi switching
2. Add auto login (if its a thing)

### ADHOC-HARDWARE
1. Implement data forwarding (wrap data packets and send to routing table neighbour)
i. Actually implemented just check that this is handled correctly on AODV side (aodv.cc:83)
ii. Add vector or some storage method if the packet was for us
2. Add sliding window on udp message queue
4. Comment/Document
5. Add packet sniffing and or check signal strength on packet receive
6.

### AODV-REM
1. Add network monitoring 

### ns3 Simulation
1. Create a module with this aodv
  - https://www.nsnam.org/docs/manual/html/new-modules.html

## Running the code

This code is currently stand alone classes, but I added test.cc to so we can test while we develop. 

1. Clone this repository 
2. Using a terminal, cd into the src directory and type 'make'
3. Code should compile and you can run ./test to run the tests

I use Visual Studio Code to develop. It has a nice built in terminal. 
