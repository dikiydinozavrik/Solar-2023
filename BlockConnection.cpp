#include "BlockConnection.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <signal.h>

using namespace std;

ProcessManager::ProcessManager(int pid, int port, string malicious_server) : pid(pid), port(port), malicious_server(malicious_server) {}

void ProcessManager::killProcess() {
    if (kill(pid, SIGTERM) == 0) {
        cout << "Process with PID " << pid << " killed successfully." << endl;
    } else {
        cerr << "Failed to kill process with PID " << pid << endl;
    }
}

void ProcessManager::sleepProcess() {
    if (kill(pid, SIGSTOP) == 0) {
        cout << "Process with PID " << pid << " set to sleep." << endl;
    } else {
        cerr << "Failed to set process with PID " << pid << " to sleep." << endl;
    }
}

void ProcessManager::resumeProcess() {
    if (kill(pid, SIGCONT) == 0) {
        cout << "Process with PID " << pid << " resumed." << endl;
    } else {
        cerr << "Failed to resume process with PID " << pid << endl;
    }
}

void ProcessManager::blockConnection() {
    char command[100];
    sprintf(command, "sudo iptables -A INPUT -s %s -j REJECT", malicious_server.c_str());
    sprintf(command, "sudo iptables -t filter -A OUTPUT -d %s -j REJECT", malicious_server.c_str());
    
    int status = system(command);

    if (status == 0) {
        cout << "Connection for the server " << malicious_server.c_str() << " blocked using iptables." << endl;
    } else {
        cerr << "Failed to block connection for the server " << malicious_server.c_str() << " using iptables." << endl;
    }
}
