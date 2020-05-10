This sample demonstrates how to "ping" another computer.

How it is done:

We send an ICMP echo request to the remote computer.
If the computer is not blocking ICMP packets (like firewall does)
it sends back and ICMP echo reply.
We receive it and time how long it took for it to arrive.