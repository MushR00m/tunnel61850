/**
 * IEC 61850 Ethernet to UDP tunnel
 *
 * Copyright (c) 2012 Steven Blair
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "interface.h"

unsigned char bufIn[2048] = {0};

pcap_t *fp;
char errbuf[PCAP_ERRBUF_SIZE];


void default_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
	//
}

pcap_t *init_pcap() {
	pcap_t *fpl;
    pcap_if_t *alldevs;
    pcap_if_t *used_if;

    // retrieve the device list from the local machine
#ifdef _WIN32
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1) {
        fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
        exit(1);
    }
#else
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    	fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
    	exit(1);
    }
#endif

    used_if = alldevs;

#ifdef _WIN32
    fprintf(stdout, "network interface: %s\n", used_if->description);
#else
    fprintf(stdout, "network interface: %s\n", used_if->name);
#endif
    fflush(stdout);

	if ((fpl = pcap_open_live(used_if->name,	// name of the device
							 65536,				// portion of the packet to capture. It doesn't matter in this case
							 1,					// promiscuous mode (nonzero means promiscuous)
							 1,					// read timeout
							 errbuf				// error buffer
							 )) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", alldevs->name);
		exit(2);
	}

    pcap_freealldevs(alldevs);

	return fpl;
}

void start() {
	fp = init_pcap();		// initialise platform-specific libpcap network interface
}

void stop() {
	pcap_close(fp);	// close network interface
}


int sendPacket(unsigned char *buf, int len) {
	return pcap_sendpacket(fp, buf, len);
}

int readPacket() {
	return pcap_loop(fp, 1, default_packet_handler, NULL);
}

int setCallback(void (*packet_handler)(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)) {
	return pcap_loop(fp, -1, packet_handler, NULL);
}
