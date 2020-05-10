Index (UDP Scanner)
-------------------

1. How does it work ?
2. Requirments !
3. Notes.
4. Contact us.

1. How does it work ?
---------------------

Unlike TCP, you can't connect to a UDP port (there is no handshake).
The only way to know if UDP is open, is sending a packet to the port, and if it's closed
the OS sends back an ICMP error message. (Firewall don't send back any information)

Because there aren't many ICMP libraries form windows, there aren't alot of UDP scanners.


2. Requirments !
---------------

Currently working only under w2k.

3. Notes.
---------

A. The loop field means how many time to verify the outcome, since this method is not very accurate
   (some ICMP messages might be lost or not proccessed), the scanner recheck the open ports again. 
B. The scanner is using our TCP/IP library v2.1 (Not released yet)
C. The source code of this scanner will be released as soon as a new library is released.

4. Contact us.
--------------

Site : http://www.komodia.com
email : barak@komodia.com
