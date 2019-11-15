#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../defines.h"
#include "../aodv/aodv_defines.h"

#define IP_ADDR			    uint32_t
#define BROADCAST           "255.255.255.255"

#define REM_DEBUG   		DEBUG && 1
#define BATTERY_DEBUG       DEBUG && 1
#define RSS_DEBUG           DEBUG && 1
