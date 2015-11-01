#include "config.h"
#include "socketcand.h"
#include "statistics.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>

fd_set readfds;

void state_default() {
	char buf[MAXLEN];
	int ret;

	if(previous_state != STATE_DEFAULT) {
		previous_state = STATE_DEFAULT;
	}

	FD_ZERO(&readfds);
	FD_SET(client_socket, &readfds);

	ret = select(client_socket+1, &readfds, NULL, NULL, NULL);

	if(ret < 0) {
		PRINT_ERROR("Error in select()\n")
			state = STATE_SHUTDOWN;
		return;
	}

	if(FD_ISSET(client_socket, &readfds)) {
		ret = receive_command(client_socket, (char *) &buf);

		if(ret == 0) {

			if (state_changed(buf, state)) {
				strcpy(buf, "< ok >");
				send(client_socket, buf, strlen(buf), 0);
				return;
			} else {
				PRINT_ERROR("unknown command '%s'\n", buf);
				strcpy(buf, "< error unknown command >");
				send(client_socket, buf, strlen(buf), 0);
			}
		} else {
			state = STATE_SHUTDOWN;
			return;
		}
	} else {
		ret = read(client_socket, &buf, 0);
		if(ret==-1) {
			state = STATE_SHUTDOWN;
			return;
		}
	}
}
