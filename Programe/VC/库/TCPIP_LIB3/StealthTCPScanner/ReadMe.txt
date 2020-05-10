Index (TCP stealth Scanner)
-------------------

1. How does it work ?
2. Requirments !
3. Notes.
4. Contact us.

1. How does it work ?
---------------------

When using a convetional TCP scanner (active scanner)
the scanner will try to connect, and log your address.

A stealth scanner (Passive), send out the SYN packet (request)
and listens to what is comming back.

If it receives an SYN+RST it means there is no one the listens on this port.
If it receives an SYN+ACK it means the socket is ready to connect (the OS unaware
of the connection we tried to open send back RST packet, because it doens't
know about the connection)

Since we didn't establish a connection on both cases, the address wasn't
loged. (unless the remote site has an IDS system)

2. Requirments !
---------------

Currently working only under w2k.

3. Notes.
---------

A. Firewall tends not to send back any info on not listening sockets.
B. Do the the scan while the traffic on the interface is low.

4. Contact us.
--------------

Site : http://www.komodia.com
email : barak@komodia.com
