# service_agent
systemd service agent

## Build Requirements

- https://github.com/troydhanson/uthash   (header file only)

## Files used by service agent

Initialization of the service agent requires a directory name to be
provided.  In this directory, the following files will be written:

- /logs 	
-- directory where log files will be written


- svcagt_exclude_services.txt	
-- list of services to be excluded (one per line)


- svcagt_goal_states.txt	
-- list of services that have been started or stopped by service agent
-- and the state.

## Tests

Two types of test can be run.  The systemd tests invoke systemctl, and 
actually start and stop services.  The pass-fail tests use a 
mock systemctl, so that code paths can be tested without actually
invoking systemctl.

### Setup for Tests

1. cd .../service-agent-c/tests
2. python setup_svcagt_services.py
3. sudo cp sajwt1.service /etc/systemd/system
4. sudo cp sajwt2.service /etc/systemd/system
5. sudo cp sajwt3.service /etc/systemd/system

The setup creates a mock_systemctl. It also creates and installs
three test services for use with the systemd tests.

### Running Tests

#### Systemd Tests

To run the systemd tests :

1. c .../service-agent-c/tests
2. . start_systemd_test.sh
3. In a separate terminal window, run test_svcagt


#### Pass-Fail Tests

To run the pass-fail tests :

1. c .../service-agent-c/tests
2. . start_pass_fail.sh
3. In a separate terminal window, run test_svcagt
