/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 The Boeing Company
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  *
  */

// custom ad hoc implementation
#include "ns3/adhoc-routing-helper.h"

#define NS3_DEBUG         1

#define TRANS_POWER       10
#define RX_GAIN           10

#define minSpeed_mpers    3
#define maxSpeed_mpers    10
#define xSize_m           500
#define ySize_m           500
#define LOCAL_MONITOR_INTERVAL  2

#define NUM_NODES         10

#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/packet.h"

#include <iostream>

using namespace ns3;

NodeContainer nodes;
map<Ptr<Node>, AdHocRoutingHelper*> adhocMap;
map< IP_ADDR, Ptr<Node> > nodeMap;

void ReceiveCallback(Ptr<Socket> socket)
{
    AdHocRoutingHelper::receivePacket(socket);
}

void testAdHoc()
{
  // Test sending from node 1 to node 3
  string msg = "Hello friend!";
  uint32_t length = msg.length();
  char* buffer = (char*)(malloc(length));
  for (uint32_t i = 0; i < length; i++)
        buffer[i] = msg.at(i);

  auto it = nodeMap.begin();
  // send data from first node to last node 
  AdHocRoutingHelper* adhoc = adhocMap[it->second];
//  i;ut += NUM_NODES - 1;
  it++;
  IP_ADDR dest = it->first;
  adhoc->sendPacket(buffer, msg.length(), dest); 

  Simulator::Schedule(Seconds(1.0), &testAdHoc);

  delete buffer;
}

void localMonitoring()
{
  map<Ptr<Node>, AdHocRoutingHelper*> adhocMap;
  auto it = adhocMap.begin();
  while (it != adhocMap.end())
  {
    it->second->monitor->updateLocalModels();
    it++;
  }

  Simulator::Schedule(Seconds(LOCAL_MONITOR_INTERVAL), &localMonitoring);
}

int main (int argc, char *argv[])
{
  std::string phyMode ("DsssRate1Mbps");
  double rss = -80;  // -dBm
  uint16_t numNodes = NUM_NODES;

  double duration = 60.00;

  CommandLine cmd;

  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
  cmd.AddValue ("rss", "received signal strength", rss);
 
  cmd.Parse (argc, argv);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",
                      StringValue (phyMode));

  nodes.Create (numNodes);

  // The below set of helpers will help us to put together the wifi NICs we want
  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  // This is one parameter that matters when using FixedRssLossModel
  // set it to zero; otherwise, gain will be added
  wifiPhy.Set ("RxGain", DoubleValue (RX_GAIN) );
  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
  wifiPhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  // The below FixedRssLossModel will cause the rss to be fixed regardless
  // of the distance between the two stations, and the transmit power
  wifiChannel.AddPropagationLoss("ns3::LogDistancePropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());

  wifiPhy.Set("TxPowerStart", DoubleValue(TRANS_POWER));
  wifiPhy.Set("TxPowerEnd", DoubleValue(TRANS_POWER));

  // Add a mac and disable rate control
  WifiMacHelper wifiMac;
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  // Set it to adhoc mode
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, nodes);

  // Note that with FixedRssLossModel, the positions below are not
  // used for received signal strength.
  MobilityHelper mobility;

  std::string xBounds = "ns3::UniformRandomVariable[Min=" + std::to_string(-1 * xSize_m/2)
    + "|Max=" + std::to_string(xSize_m/2) + "]";
  std::string yBounds = "ns3::UniformRandomVariable[Min=" + std::to_string(-1 * ySize_m/2)
    + "|Max=" + std::to_string(ySize_m/2) + "]";

  ObjectFactory positionModel;
  positionModel.SetTypeId("ns3::RandomRectanglePositionAllocator");
  positionModel.Set("X", StringValue(xBounds));
  positionModel.Set("Y", StringValue(yBounds));
  Ptr<PositionAllocator> positionAllocPtr = positionModel.Create()->GetObject<PositionAllocator>();
  mobility.SetPositionAllocator(positionAllocPtr);

  // Keep nodes immobile for initial tests 
  std::string speedInput = "ns3::UniformRandomVariable[Min=" + std::to_string(minSpeed_mpers) + "|Max=" + std::to_string(maxSpeed_mpers) + "]";
  // set mobility model for adhoc nodes
  mobility.SetMobilityModel("ns3::RandomWaypointMobilityModel",
    "Speed", StringValue(speedInput),
    "Pause", StringValue("ns3::ConstantRandomVariable[Constant=0.5]"),
    "PositionAllocator", PointerValue(positionAllocPtr));

  mobility.Install(nodes);

  InternetStackHelper internet;
  internet.Install(nodes);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("192.168.1.0", "255.255.255.0");
  ipv4.Assign (devices);

  for(int i = 0; i < numNodes; i++){
    Ptr<Socket> routeSink = Socket::CreateSocket (nodes.Get (i), UdpSocketFactory::GetTypeId ());
    InetSocketAddress localRouting = InetSocketAddress (Ipv4Address::GetAny (), ROUTING_PORT);
    routeSink->Bind(localRouting);
    routeSink->SetRecvCallback(MakeCallback(&ReceiveCallback));
    routeSink->m_port = ROUTING_PORT;

    Ptr<Socket> dataSink = Socket::CreateSocket(nodes.Get(i), UdpSocketFactory::GetTypeId()); 
    InetSocketAddress localData = InetSocketAddress (Ipv4Address::GetAny (), DATA_PORT);
    dataSink->Bind(localData);
    dataSink->SetRecvCallback(MakeCallback(&ReceiveCallback));
    dataSink->m_port = DATA_PORT;

    Ptr<Socket> monitorSink = Socket::CreateSocket(nodes.Get(i), UdpSocketFactory::GetTypeId());
    InetSocketAddress localMonitor = InetSocketAddress (Ipv4Address::GetAny (), MONITOR_PORT);
    monitorSink->Bind(localMonitor);
    monitorSink->SetRecvCallback(MakeCallback(&ReceiveCallback));
    monitorSink->m_port = MONITOR_PORT;

    Ptr<Ipv4> ipv4 = nodes.Get(i)->GetObject<Ipv4>(); // Get Ipv4 instance of the node
    Ipv4Address addr = ipv4->GetAddress (1, 0).GetLocal ();  
    // add aodv object 
    uint8_t* ipBuf = (uint8_t*)(malloc(4)); 
    addr.Serialize(ipBuf);

    IP_ADDR ip;
    memcpy(&(ip),(ipBuf),4);

    nodes.Get(i)->m_nodeIp = ip;
    nodeMap[ip] = nodes.Get(i); 
 
    adhocMap[nodes.Get(i)] = new AdHocRoutingHelper(nodes.Get(i), ip);
    nodes.Get(i)->m_AdHocRoutingHelper = adhocMap[nodes.Get(i)]; 
  }

  // Tracing
//  Simulator::Schedule (Seconds (1.0), &GenerateTraffic,
//                       c, packetSize, numPackets, Seconds(1));

  Simulator::Schedule(Seconds(1.0), &testAdHoc);// &(aodvArray[1]->socketSendPacket), buffer, msg.length() + 5, aodvArray[1]->getIp(), 654, aodvArray[3]->getIp());
  Simulator::Schedule(Seconds(LOCAL_MONITOR_INTERVAL), &localMonitoring);

  Simulator::Stop (Seconds (duration + 10.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
