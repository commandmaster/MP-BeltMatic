#include <iostream>
#include <enet/enet.h>

int main() {
    std::cout << "Client Application Started" << std::endl;

	if (enet_initialize() != 0) {
		std::cerr << "An error occurred while initializing ENet." << std::endl;
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	ENetHost* client;
	client = enet_host_create(NULL, 1, 1, 0, 0);

	if (client == NULL)
	{
		std::cerr << "An error occurred while trying to create an Enet Client Host" << std::endl;
		return EXIT_FAILURE;	
	}

	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;

	enet_address_set_host(&address, "127.0.0.1");
	address.port = 3000;

	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL)
	{
		std::cerr << "No available peers for initiating an Enet connection" << std::endl;
		return EXIT_FAILURE;
	}
	
	if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection to 127.0.0.1:3000 succeeded" << std::endl;
	}
	else
	{
		enet_peer_reset(peer);
		std::cout << "Connection to 127.0.0.1:3000 failed." << std::endl;
		return EXIT_SUCCESS;
	}

	// GAME LOOP
	while(enet_host_service(client, &event, 1000) > 0)
	{
		switch(event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
				printf ("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
				event.packet -> dataLength,
				event.packet -> data,
				event.peer -> address.host,
				event.peer -> address.port,
				event.channelID);
				break;
		}
	}	

	

	// GAME LOOP END

	enet_peer_disconnect(peer, 0);

	while(enet_host_service(client, &event, 3000) > 0)
	{
		switch(event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				puts("Disconnection succeeded.");
				break;
		}
	}

	return EXIT_SUCCESS;    
}