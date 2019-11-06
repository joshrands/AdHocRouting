#ifndef ROUTINGPROTOCOL_H
#define ROUTINGPROTOCOL_H

/********************************
 * RoutingProtocol.h 
 * 
 * Simple routing protocol base class for implementation of more complex routing protocols.
 * Contains necessary building blocks for custom routing protocols. 
 * 
 * Author: Josh Rands
 * Date: 9/4/2019
 ********************************/

#include <map> 
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <math.h>

#include "aodv_defines.h"

using namespace std;

// get a 32 bit ip address from a string
IP_ADDR getIpFromString(string ipStr);
string getStringFromIp(IP_ADDR ip);

/* Routing Table row class 
 * This class exists to make future modifications to priority in routing protocols */
class TableInfo 
{
public:
	IP_ADDR dest; // target destination 
	IP_ADDR nextHop; // next hop 

	uint16_t ttl; // time to live for this table entry 
};


/* Routing Table class */
class RoutingTable
{
public:
	// default constructor 
	RoutingTable();
	~RoutingTable();

	const uint16_t DEFAULT_TTL = 1800; // 1800 seconds = 30 minutes 

	// returns the ip address of the next hop 
	// returns 0 if not in table 
	IP_ADDR getNextHop(const IP_ADDR dest);

	// adds an element to the table 
	virtual void updateTableEntry(const IP_ADDR dest, const IP_ADDR nextHop);

	// get the map 
	map<IP_ADDR, TableInfo> getInternalTable() { return this->table; }

protected:
	// internal routing table maps destination to next hop 
	map<IP_ADDR, TableInfo> table;

};


/* Routing Protocol base class */
class RoutingProtocol
{
public: 
	// default constructor
	RoutingProtocol();

	static int DATA_PORT;

	const uint32_t getIp() { return ipAddress; }
	void setIp(const uint32_t ip) { ipAddress = ip; }

	// abstract function to be overwritten by child class 
	virtual int socketSendPacket(char *buffer, int length, IP_ADDR dest, int port) = 0;

protected:
	RoutingTable* table;	

	uint32_t ipAddress;
};

#endif