#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H
#include "paintball_class.h"
bool check_input_validity_alphabet(std::string input);
void read_file( std::string name, std::vector<std::string>& text );
int s_to_i( std::string num );
void process_person_info( tournament& t1 );
void process_weapon_info( tournament& t1, competition& c1 );
void get_input( tournament& t1, competition& c1, bool& print);
void scoreboard(std::string input, tournament t1);
void newgame( tournament& t1, competition& c1 );
void support( tournament& t1, competition& c1, std::string input );
void purchase( tournament& t1, competition& c1, std::string input );
std::vector<std::string> analyze_purchase( std::string input );
void start_game( tournament& t1, competition& c1, bool& print);
int find_random( int _skill, competition& c1 );
double calc_damage( double range, double destination, std::string shot_place, double bullet_power );
void shoot( tournament& t1, competition& c1, int& i, bool& print );
#endif
