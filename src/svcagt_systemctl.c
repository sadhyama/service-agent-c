/******************************************************************************
   Copyright [2016] [Comcast]

   Comcast Proprietary and Confidential

   All Rights Reserved.

   Unauthorized copying of this file, via any medium is strictly prohibited

******************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "svcagt_systemctl.h"
#include "svcagt_log.h"


// Can be changed for debugging
const char *svcagt_systemctl_cmd = "systemctl";

// Invoke systemctl to get the running/stopped state of a service
int svcagt_get_service_state (const char *svc_name)
{
	int exit_code;
	bool running;
	char cmdbuf[128];

	sprintf (cmdbuf, "%s is-active %s.service", svcagt_systemctl_cmd, svc_name);
	exit_code = system (cmdbuf);
	if (exit_code == -1) {
		svcagt_log (LEVEL_ERROR,"Error invoking systemctl command, errno:%d(%s)\n", errno, strerror(errno));
		return -1;
	}
	running = (exit_code == 0);
	return running;
}

// Invoke systemctl to start or stop a service
int svcagt_set_service_state (const char *svc_name, bool state)
{
	int exit_code = 0;
	char cmdbuf[128];
	const char *start_stop_msg;
	const char *cmd_option;

	if (state) {
		start_stop_msg = "Starting";
		cmd_option = "start";
	} else {
		start_stop_msg = "Stopping";
		cmd_option = "stop";
	}

	svcagt_log (LEVEL_INFO,"%s %s\n", start_stop_msg, svc_name);
	sprintf (cmdbuf, "%s %s %s.service", 
		svcagt_systemctl_cmd, cmd_option, svc_name); 
	exit_code = system (cmdbuf);
	if (exit_code != 0)
		svcagt_log (LEVEL_ERROR,"Command %s failed, errno:%d(%s)\n", cmdbuf, errno, strerror(errno));
	return exit_code;
}

