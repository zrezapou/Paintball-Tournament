#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "paintball_class.h"
#include "main_header.h"
using namespace std;
int main()
{

	tournament t1;
	process_person_info(t1);
	string input;
	bool print= true;
	while(getline(cin, input))
	{
		string temp;
		istringstream iss(input);
		iss>>temp;
		if(temp=="show")
			scoreboard(input, t1);
		if(check_input_validity_alphabet(input))
		{
			if(temp=="newgame")
			{

				competition c1;
				get_input(t1, c1, print);
				t1.push_competition(c1);
			}
			else if(temp=="endtournament")
				exit(EXIT_SUCCESS);
		}
	}
	cerr<<"here";
	return 0;
}
