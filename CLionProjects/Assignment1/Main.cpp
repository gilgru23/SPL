#include <iostream>
//#include  "../include/Session.h"
#include <iostream>;
#include <fstream>
#include "Session.h"
#include "json.hpp";
using json= nlohmann::json ;
using namespace std;

int main(int argc, char** argv){
    std::ifstream ifs("config1.json");
    json j = json::parse(ifs);
    cout<<j["movies"][0]["name"];

    /*
	if(argc!=2)
	{
		cout << "usage splflix input_file" << endl;
		return 0;
	}
	Session s(argv[1]);
	s.start();

	return 0;
*/
}
