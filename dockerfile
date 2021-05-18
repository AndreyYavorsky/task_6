FROM debian

WORKDIR /laba_6

COPY server_tcp.c server_udp.c /laba_6/

RUN apt update;\
	apt install gcc -y;                       

CMD gcc server_tcp.c -lpthread -o serv_tcp;\
	gcc server_udp.c -lpthread -o serv_udp;\
	/bin/bash