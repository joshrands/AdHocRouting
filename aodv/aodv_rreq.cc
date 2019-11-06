#include "aodv_rreq.h"

#include <iostream>
#include <string.h>

using namespace std;

RREQHelper::RREQHelper()
{
    this->m_rreqID = 0;
}

RREQHelper::RREQHelper(IP_ADDR ip, AODVRoutingTable* table, uint32_t* seqNum) 
{
    this->m_pTable = table;
    this->m_ip = ip;
    this->m_rreqID = 0;
    this->m_pSequenceNum = seqNum;
}

bool RREQHelper::shouldGenerateRREP(rreqPacket receivedRREQ)
{
	// generate RREP on 2 conditions:
	// 1. This node is the final destination
	// 2. This node has an existing route to the final destination
	if (receivedRREQ.destIP == this->m_ip)
	{
		if (RREQ_DEBUG)
			cout << "[DEBUG]: RREQ reached final destination. Generating RREP..." << endl;

		return true;
	}
	else if (this->m_pTable->getNextHop(receivedRREQ.destIP) != 0 && this->m_pTable->getIsRouteActive(receivedRREQ.destIP))
	{
		if (RREQ_DEBUG)
			cout << "[DEBUG]: This node " << getStringFromIp(this->m_ip) << " has a path to the final node in its routing table." << endl;

		return true;
	}
	else
		return false;
}

bool RREQHelper::isDuplicateRREQ(rreqPacket receivedRREQ)
{
	// if the origIP exists in the routing table AND the sequence number matches 
	uint32_t packetSeqNum = receivedRREQ.origSeqNum;
	uint32_t tableSeqNum = this->m_pTable->getDestSequenceNumber(receivedRREQ.origIP);
	// or if the last rreq message id matched this one...
	uint32_t tableLastId = this->m_pTable->getLastRREQId(receivedRREQ.origIP);

	// special case that this rreq is originally from this node
	if (receivedRREQ.origIP == this->m_ip)
		return true;

	// has to be a duplicate rreq AND not a better route. 
	int currentCost = this->m_pTable->getCostOfDest(receivedRREQ.origIP);
	int newCost = this->m_pTable->getCostOfRREQ(receivedRREQ);

	if ( (packetSeqNum == tableSeqNum || tableLastId == receivedRREQ.rreqID) 
		&& (newCost > currentCost) ) 
		return true;
	else
		return false;
}

rreqPacket RREQHelper::createRREQ(const IP_ADDR destIP, const uint32_t destSeqNum)
{
	// Section 6.3 rfc3561
	if (RREQ_DEBUG)
		cout << "[DEBUG]: Creating Route Request message from " << getStringFromIp(this->m_ip) << " to " << getStringFromIp(destIP) << endl;

	// there is no current path to the destination, create a RREQ 
	rreqPacket rreq; 

	rreq.type = 0x01;

    // TODO: set the flags
	// default is all 0... 

	rreq.hopCount = 0;
	
	rreq.rreqID = (++this->m_rreqID);
	rreq.destIP = destIP;
	rreq.destSeqNum = destSeqNum; 
	if (0 == rreq.destSeqNum)
	{
		// unknown destSeqNum flag is 00001000 
		rreq.u |= 0x08;
	}
	rreq.origIP = this->m_ip;
	rreq.origSeqNum = (++*(this->m_pSequenceNum));

	return rreq;
}

rreqPacket RREQHelper::createForwardRREQ(rreqPacket receivedRREQ, IP_ADDR sourceIP)
{
	// Section 6.5 rfc3561

	rreqPacket forwardRREQ = receivedRREQ;

	// 1. Increment the hop count 
	forwardRREQ.hopCount++;

	// 2. Update routing table for this node with orig sequence nubmer 
	this->m_pTable->updateAODVRoutingTableFromRREQ(&forwardRREQ, sourceIP);

	// 3. TODO: Set lifetime of table entry

	return forwardRREQ;
}

char* RREQHelper::createRREQBuffer(const rreqPacket rreq)
{
	char* buffer = (char*)(malloc(sizeof(rreq)));	

	// fill buffer with all rreq information
	memcpy(buffer, &(rreq), sizeof(rreq));

	return buffer;
}

rreqPacket RREQHelper::readRREQBuffer(char* buffer)
{
	rreqPacket rreq;

	// convert buffer to rreq 
	memcpy(&(rreq), buffer, sizeof(rreq));

	return rreq;
}