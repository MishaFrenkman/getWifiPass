#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

string exec (const char* cmd) {
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

string output (string pass, string wifi){
	system("clear");
	
	string out = "-------------\n";
	cout << "-------------" << endl;
	if (wifi.empty()) {
		cout << "No WiFi connection found!" << endl;
		out += "No WiFi connection found!\n";
	} else 
	if (pass.empty()){
		cout << "WiFi SSID: " +wifi << "*** No password found in keychain! ***" << endl;
		out += "WiFi SSID: " +wifi + "\n*** No password found in keychain! ***\n";
	} else {
		cout << "WiFi SSID: " +wifi << "Password: " +pass;
		out += "WiFi SSID: " +wifi+ "\nPassword: " +pass;
	}
	out += "-------------\n";
	cout << "-------------" << endl;
	
	return out;
}


int main(int argc, char *argv[]) {
	#ifdef __APPLE__
		string wifi = getSSID(exec("airport -I | grep -w SSID: "));
		string cmd = "security find-generic-password -wa '" + wifi + "'";
		output(exec(cmd.c_str()), wifi);
	#endif
	
	#ifdef _WIN32
		cout << endl;
		cout << "This script currently works for MacOS only :(" << endl;
		cout << "Windows Version coming soon..." << endl;
		cout << endl;
		
		/*
			Windows code
		*/
	#endif
	
}