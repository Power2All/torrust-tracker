/*
 *	Copyright © 2012 Naim A.
 *
 *	This file is part of UDPT.
 *
 *		UDPT is free software: you can redistribute it and/or modify
 *		it under the terms of the GNU General Public License as published by
 *		the Free Software Foundation, either version 3 of the License, or
 *		(at your option) any later version.
 *
 *		UDPT is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License
 *		along with UDPT.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UDPTRACKER_H_
#define UDPTRACKER_H_

#include <stdint.h>
#include "multiplatform.h"
#include "db/database.h"

struct udp_connection_request
{
	uint64_t connection_id;
	uint32_t action;
	uint32_t transaction_id;
};

struct udp_connection_response
{
	uint32_t action;
	uint32_t transaction_id;
	uint64_t connection_id;
};

struct udp_announce_request
{
	uint64_t connection_id;
	uint32_t action;
	uint32_t transaction_id;
	uint8_t info_hash [20];
	uint8_t peer_id [20];
	uint64_t downloaded;
	uint64_t left;
	uint64_t uploaded;
	uint32_t event;
	uint32_t ip_address;
	uint32_t key;
	int32_t num_want;
	uint16_t port;
};

struct udp_announce_response
{
	uint32_t action;
	uint32_t transaction_id;
	uint32_t interval;
	uint32_t leechers;
	uint32_t seeders;

	uint8_t *peer_list_data;
};

struct udp_scrape_request
{
	uint64_t connection_id;
	uint32_t action;
	uint32_t transaction_id;

	uint8_t *torrent_list_data;
};

struct udp_scrape_response
{
	uint32_t action;
	uint32_t transaction_id;

	uint8_t *data;
};

struct udp_error_response
{
	uint32_t action;
	uint32_t transaction_id;
	char *message;
};

typedef struct
{
	SOCKET sock;
	uint16_t port;

	uint8_t thread_count;

	uint8_t flags;

	HANDLE *threads;

	dbConnection *conn;
} udpServerInstance;

typedef struct udp_connection_request ConnectionRequest;
typedef struct udp_connection_response ConnectionResponse;
typedef struct udp_announce_request AnnounceRequest;
typedef struct udp_announce_response AnnounceResponse;
typedef struct udp_scrape_request ScrapeRequest;
typedef struct udp_scrape_response ScrapeResponse;
typedef struct udp_error_response ErrorResponse;

void UDPTracker_init (udpServerInstance *, uint16_t port, uint8_t threads);
void UDPTracker_destroy (udpServerInstance *);

int UDPTracker_start (udpServerInstance *);

#endif /* UDPTRACKER_H_ */