all:	server client

server:	shm_server.c
	cc shm_server.c -o server

client: shm_client.c
	cc shm_client.c -o client
