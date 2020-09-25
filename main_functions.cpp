#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "main_header.h"
#include "paintball_class.h"
using namespace std;
#define invalid -1
bool check_input_validity_alphabet(string input)
{
	for(int i=0; i < input.length(); i++)
		if((input[i] > 'z' || input[i] < 'a') && (input[i]<'0' || input[i]>'9') && input[i]!=' ')
			return false;
	return true;
}

void read_file(string name, vector<string>& text)
{
	const char * input = name.c_str();
	string line;
	ifstream myfile (input);
    if (myfile.is_open())
	{
    	while ( getline (myfile,line) )					///Read from from file
    		text.push_back(line);
    	myfile.close();
    }
    else
    	cerr << "Unable to open file";
}
int s_to_i(string num)
{
    int number=0;
    for(int i=0;i<num.size();i++)
    {
        number=number+(num[num.size()-1-i]-48)*pow(10,i);
    }
    return number;
}

void start_game(tournament& t1, competition& c1, bool& print)
{
	while(c1.get_player_size()>1)
		for (int i = 0; i < c1.get_player_size(); i++)
			shoot(t1, c1, i, print);
	c1.who_is_winner();
	Player* winner;
	int id=c1.get_ith_player_id(0);
	winner=c1.get_player_addr(id);
	winner->account_refinement(c1);
}
void shoot(tournament& t1, competition& c1, int& i, bool& print)
{
	string input;
	int shooter_id;
	Player* shooter;
	int power;
	double destination;
	getline(cin, input);
	int pos=input.find(':');
	replace(input.begin(),input.end(),':',' ');
	istringstream iss(input);
    vector<string> tokens;

	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter(tokens));

	if(tokens.size()>0 && tokens[0]=="shoot" && pos!=invalid)
	{
		double damage=0;;
		double range;
		double destination;
		string shot_place;
		int is_shot_id=0;
		shooter=c1.get_player_addr(shooter_id=c1.get_ith_player_id(i));
		if(shooter!=NULL && shooter->get_weapon_addr()!=NULL)
		{
			int row=s_to_i(tokens[1]) + find_random(shooter->get__skill(), c1);
			int column =s_to_i(tokens[2])+find_random(shooter->get__skill(), c1);
			shot_place=c1.find_shot_place(row, column, is_shot_id);
			if(shot_place=="")
			{
				shot_place="missed";
				if(print==false)
					cout<<endl;
				cout<<"player <"<<shooter_id<<"> "<<shot_place;
				print=false;
			}
			else
			{
				Player* is_shot;
				is_shot_id=c1.get_ith_player_id(is_shot_id);
				is_shot=c1.get_player_addr(is_shot_id);
				Shot s1(shooter, is_shot=c1.get_player_addr(is_shot_id));
				int i_shooter_chest=shooter->get_chest("row");
				int j_shooter_chest=shooter->get_chest("column");
				destination=sqrt(pow(row- i_shooter_chest,2)+pow(column- j_shooter_chest,2));
				range=shooter->get__range();
				damage=calc_damage(range, destination, shot_place, shooter->get_bullet_power());
				//cerr<<endl<<"shot_place: "<<shot_place<<endl<<"damage: "<<damage<<endl<<"destination: "<<destination;
				s1.set_parameters(damage , destination, shot_place);
				is_shot->apply_damage(damage);
				c1.shot_push(s1);
				if(print==false)
					cout<<endl;
				cout<<"player <"<<shooter_id<<"> hits player <"<<is_shot_id<<"> in the "<<shot_place;
				print=false;
				if(is_shot->get_life()<=0)
					c1.kill_person(shooter, is_shot);
			}
		}
	}
	else if(tokens.size()>0 && tokens[0]=="surrender")
		c1.surrender_ith_on_vector(i);
	else if(tokens.size()>0 && tokens[0]=="endtournament")
		exit(EXIT_SUCCESS);
}
double calc_damage(double range, double destination, string shot_place, double bullet_power)
{
	double constant;
	double destruction;
	if(destination<=range)
		constant=1;
	else if(destination<=2*range)
		constant=0.5;
	else
		constant=0.25;
	if(shot_place=="head")
		destruction=5;
	else if(shot_place=="chest")
		destruction=3;
	else if(shot_place=="abdoman")
		destruction=2;
	else if(shot_place=="arms"||shot_place=="legs")
		destruction=1;
	else
		exit(EXIT_FAILURE);
	return (constant*destruction*bullet_power);
}

int find_random(int skill, competition& c1)
{
	if(skill==100)
		return 0;
	srand(c1.get_seed());
	double random=rand()%(2*(100-skill)+1)-(100-skill);
	if(abs(random)>=0 && abs(random)<=15-skill/10)
		return 0;
	else if(abs(random)>15-skill/10 && abs(random)<=int(pow(52-skill/2,1.1)))
		return random>0?1:-1;
	else
		return random>0?2:-2;
}

void process_person_info(tournament& t1)
{
	vector<string> players_info;
	read_file("players.txt",players_info);
	for (int i = 0; i < players_info.size(); i++)
	{
		vector<string>data;
		for(int j=0; j<4; j++)
		{
			int pos;
			string temp;
			string process;
			pos=players_info[i].find(',');
			process=players_info[i].substr(0,pos);
			istringstream input(process);
			input>>temp;
			players_info[i]=players_info[i].substr(pos+1);
			data.push_back(temp);
		}
		Person p1(data[1], s_to_i(data[0]), atof(data[3].c_str()), s_to_i(data[2]));
		t1.push_persons(p1);
	}
}

void process_weapon_info(tournament& t1, competition& c1)
{
	std::vector<string> weapons_info;
	read_file("weapons.txt",weapons_info);
	for (int i = 0; i < weapons_info.size(); i++)
	{
		vector<string>data2;
		for(int j=0; j<4; j++)
		{
			int pos;
			string temp;
			string process;
			pos=weapons_info[i].find(',');
			process=weapons_info[i].substr(0,pos);
			if(j!=0)
			{
				istringstream input(process);
				input>>temp;
			}
			else
				temp=process;
			weapons_info[i]=weapons_info[i].substr(pos+1);
			data2.push_back(temp);
		}
		Weapon w1(data2[0], atof(data2[1].c_str()), atof(data2[2].c_str()), atof(data2[3].c_str()));
		c1.push_weapon(w1);
	}
}

void get_input(tournament& t1,competition& c1, bool& print)
{
	string input;
	string temp;
	process_weapon_info( t1, c1);
	newgame( t1, c1);
	while(getline(cin, input))
	{
		istringstream iss(input);
		iss>>temp;
		input.erase(input.begin(),input.begin()+temp.size());
		if(temp=="supports")
			support(t1,c1,input);
		else if(temp=="purchase")
			purchase(t1,c1,input);
		else if(temp=="startgame")
		{
			start_game(t1,c1, print);
			break;
		}
		else if(temp=="endtournament")
			exit(EXIT_SUCCESS);
	}
}

void newgame(tournament& t1,competition& c1)
{
	string input;
	int num;
	getline(cin, input);
	num=s_to_i(input);
	std::vector<string> input2;
	for (int i = 0; i < num; i++)
	{
		getline(cin, input);
		replace(input.begin(),input.end(),':',' ');
		input2.push_back(input);
	}
	long int _seed;
	double _match_cost;
	double _ticket_revenue;
	getline(cin, input);
	istringstream iss(input);
	iss>>_seed>>_match_cost>>_ticket_revenue;
	c1.set_cost(_match_cost, _ticket_revenue,_seed);
	for (int i = 0; i < num; i++)
	{
		int row;
		int column;
		int id;
		char d;
		Person* p1;
		istringstream iss(input2[i]);
		iss>>id>>row>>column>>d;
		Player pl1(row, column, d, p1=t1.get_addr_person(id));
		p1->set_fund(_match_cost);
		c1.player_push(pl1);
	}
}

void support(tournament& t1, competition& c1,string input)
{
	int pos;
	int pos2;
	int supporter;
	int supported;
	double cash;
	pos2=input.find('>');
	replace(input.begin(),input.end(),'>',' ');
	pos=input.find('f');
	if(pos!=invalid && pos2!=invalid)
	{
		input.erase(input.begin()+pos,input.begin()+pos+3);
		istringstream iss(input);
		iss>>supporter>>supported>>cash>>cash;
		if(!c1.find_player(supporter))
		{
			double fund;
			Person* p1=t1.get_addr_person(supporter);
			Person* p2=t1.get_addr_person(supported);
			fund=p1->get_fund();
			if(fund>=cash && cash > 0 && p1!=NULL && p2!=NULL)
			{
				p1->pay_cost(cash);
				p2->reach_money(cash);
				Sponsor s1(p1, cash);
				c1.set_sponsor(supported, s1);
			}
		}
	}
}
vector<string> analyze_purchase(string input)
{
	int pos;
	pos=input.find('<');
	if(pos!=invalid)
	{
		replace(input.begin(),input.end(),'<',' ');
		istringstream iss(input);
	    vector<string> tokens;

		copy(istream_iterator<string>(iss),
		     istream_iterator<string>(),
		     back_inserter(tokens));

		pos=input.find(tokens[0]);
		input.erase(input.begin(),input.begin()+pos+tokens[0].size());
		pos=input.find(tokens[1]);
		input.erase(input.begin(),input.begin()+pos);
		pos=input.find(tokens[tokens.size()-1]);
		pos=input.length()-pos;
		input.erase(input.end()-pos+tokens[tokens.size()-1].length(),input.end());
		std::vector<string> data;
		data.push_back(tokens[0]);
		data.push_back(input);
		return data;
	}
	else
	{
		std::vector<string> empty;
		empty.push_back("empty");
		return empty;
	}
}
void purchase(tournament& t1, competition& c1, string input)
{
	vector<string> data;
	Player* p1;
	Weapon* weapon;
	double cost;
	double cash;
	data=analyze_purchase(input);
	if(data[0]!="empty")
	{
		weapon=c1.find_weapon(data[1]);
		p1=c1.get_player_addr(s_to_i(data[0]));
		if(p1!=NULL && weapon!=NULL)
		{
			cost=weapon->get_cost();
			cash=p1->player_cash();
			if(cost<=cash)
			{
				p1->pay_weapon(cost);
				p1->set_weapon(weapon);
			}
		}
		else if(weapon==NULL)
			p1->set_weapon(NULL);
	}
	//cerr<<p1->get_bullet_power();
	//cerr<<p1->player_cash()<<endl;
	/*istringstream iss(input);
	iss>>buyer;
	input.find()*/
}

void scoreboard(string input, tournament t1)
{
	std::vector<string> tokens;
	istringstream iss(input);
	copy(istream_iterator<string>(iss),
		     istream_iterator<string>(),
		     back_inserter(tokens));
	tokens[1].erase(tokens[1].begin());
	tokens[1].erase(tokens[1].begin()+1);
	tokens[4].erase(tokens[4].begin());
	int pos=tokens[4].find('>');
	tokens[4].erase(tokens[4].begin()+pos);
	t1.get_most_kill(s_to_i(tokens[1]), tokens[5], tokens[4]);
}
