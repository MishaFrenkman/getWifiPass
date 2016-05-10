#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
	if (!pipe) throw std::runtime_error("popen() failed!");
	
	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result = buffer;
	}
	return result;
}

string getSSID (string str){
	str = str.replace(0,str.find(":")+2, "");
	return str;
}

void output (string pass, string wifi){
	system("clear");
	cout << "-------------" << endl;
	if (wifi.empty()) {
		cout << "No WiFi connection found!" << endl;
	} else 
	if (pass.empty()){
		cout << "Permission denied! Please fill in your user pass!" << endl;
	} else {
		cout << "WiFi SSID: " +wifi << "Password: " +pass;
	}
	cout << "-------------" << endl;
}


int main(int argc, char *argv[]) {
	string wifi = getSSID(exec("airport -I | grep -w SSID: "));
	string cmd = "security find-generic-password -wa " + wifi;
	
	output(exec(cmd.c_str()), wifi);
}