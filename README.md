# Network IP Addresses and Bitwise Operators
COMP 211 Checkoff 3

## Topic
In networking, an IP address is contains both the network information and the host information of the target device. The network names the network the device is apart of. The host names one specific device on a network. Because both elements are found in the IP address, routers across the internet must use a standardized proceedur for separating the two to direct packets in the right direction. Hence, a subnet mask is a necessity.

## What I Explored
I explored what a subnet mask is, why it is used to separate an IP address into host and network information, and how the subnet mask uses bitwise operators.

## Key Discoveries
- Bitwise operators are faster than standard arithmetic in comparing numbers
- Network boundaries (e.g. /24) are defined in bits -> masking with AND keeps the first 24 bits, which gives the network by definition
- Bitshifting is a useful tool for coverting IP addresses in decimal to binary

## Code Examples
router_bitwise.c

**To compile and run:**

Compile: gcc -Wall -std=c99 -o router_bitwise router_bitwise.c
./router_bitwise 192.168.1.42

AI Usage: AI was used to create the sample code. I responded to the first produced code with 2 follow-ups to simplify the example to more appropriately focus on bit shifting and bit masking for the purposes of the assignment.


## Presentation
https://docs.google.com/presentation/d/125GHUQw-9FbC224pVWeLx3aeIXvavhhHnlP2kZ4Cz8U/edit?usp=sharing

## Resources
- https://claude.ai/share/1823bd6c-f769-4ce4-96e8-fa5547ae103f
- RFC 4632 (CIDR)ss