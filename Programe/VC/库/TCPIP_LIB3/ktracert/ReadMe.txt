This sample finds the route to the remote host.

How does it work:

The application sends an ICMP echo packet with TTL of 1.
When it reaches the next router, he decrement it.
When the TTL is zero that specific router receives the packet and reply
back with and IcMP echo reply.

We do it again, but we increment the TTL to 2.
The same will happend but for the router after the first router.

We will do it until the final reply will be from our host.