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
using namespace std;
Person::Person(std::string _name, int _id, double _fund, int _skill)
{
	if(_name=="" || _fund<0 || _id < 0 || _skill<0)
		exit(EXIT_FAILURE);
	name=_name;
	id=_id;
	fund=_fund;
	skill=_skill;
	kill=0;
	death=0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
Weapon::Weapon(std::string _name, double _power, double _effective_range, double _cost)
{
	if(_name=="" || _power<0 || _effective_range<0 || _cost<0)
		exit(EXIT_FAILURE);
	name=_name;
	power=_power;
	effective_range=_effective_range;
	cost=_cost;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(int _i, int _j, int _d, Person* _person)
{
	if(_i<0||_j<0)
		exit(EXIT_FAILURE);
	i=_i;
	j=_j;
	if(_d!='N'||_d!='S'||_d!='E'||_d!='W')
		abort;
	d=_d;
	person=_person;
	life=100;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int Player::get_chest(std::string axis)
{
	if(axis=="row" && d=='N')
		return i+1;
	else if(axis=="row" && d=='S')
		return i-1;
	else if (axis=="row" && (d=='W'||d=='E') )
		return i;
	else if(axis=="column" && (d=='N'||d=='S'))
		return j;
	else if(axis=="column" && d=='E')
		return j-1;
	else if(axis=="column" && d=='W')
		return j+1;
	else
		exit(EXIT_FAILURE);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Player::apply_damage(double _damage)
{
	if(_damage>0)
		life-=_damage;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
Sponser::Sponser(Person* _person, double _cash)
{
	if(_cash<0)
		abort();
	cash=_cash;
	person=_person;
}

Person* tournament::get_addr_person(int _id)
{
	for (int i = 0; i < person_size(); i++)
		if(persons[i].get_id()==_id)
			return &persons[i];
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Person::set_fund(double _fund)
{
	if(fund>=_fund && _fund>0)
		fund-=_fund;
	else
		abort();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::pay_cost(double _cost)
{
	if(fund>=_cost)
		fund-=_cost;
	else
		exit(EXIT_FAILURE);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::reach_money(double money)
{
	if(money>0)
		fund+=money;
	else
		exit(EXIT_FAILURE);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::account_refinement(competition& c1)
{
	double fund=0;
	while(sponsors.size()>0)
	{
		fund=fund-sponsors[0].get_cash();
		sponsors[0].refine_debt();
		cout<<endl<<"player <"<<get_player_id()<<"> returns <"<<sponsors[0].get_cash()<<"> dollars to sponser <"<<sponsors[0].get_id()<<">";
		sponsors.erase(sponsors.begin());
	}
	cout<<endl<<"player <"<<get_player_id()<<"> cashed in <"<<c1.get_ticket_revenue()/2+fund<<"> dollars";
	inc_cash(c1.get_ticket_revenue()/2+fund);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void competition::set_sponser(int _id, Sponser sponser)
{
	for (int i = 0; i < players.size(); i++)
	{
		if(players[i].get_person_id()==_id)
		{
			players[i].push_sponser(sponser);
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void competition::set_cost(double _match_cost, double _ticket_revenue, long int _seed)
{
	if(_match_cost>=0 && _ticket_revenue>=0 && _seed>=0)
	{
		match_cost=_match_cost;
		ticket_revenue=_ticket_revenue;
		seed=_seed;
	}
	else
		abort;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool competition::find_player(int _id)
{
	for (int i = 0; i < players.size(); i++)
	{
		if(players[i].get_person_id()==_id)
			return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
Player* competition::get_player_addr(int _id)
{
	for (int i = 0; i < players.size(); i++)
	{
		if(players[i].get_person_id()==_id)
			return &players[i];
	}
	cerr<<"couldn't find player"<<"->"<<"get_player_addr"<<endl;
	return NULL;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void competition::kill_person(Player* shooter, Player* is_shot)
{
	for(int i=0; i<players.size(); i++)
		if(players[i].get_player_id()==is_shot->get_player_id())
		{
			players[i].inc_one_death();
			players.erase(players.begin()+i);
			break;
		}
	for (int i = 0; i < players.size(); i++)
		if(players[i].get_player_id()==shooter->get_player_id())
		{
			players[i].inc_one_kill();
			break;
		}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
std::string competition::find_shot_place(int _i, int _j, int& id)
{
	std::string shot_place;
	while(id<players.size())
	{
		int i, j;
		char d;
		i=players[id].get_i();
		j=players[id].get_j();
		d=players[id].get_d();
		if(d=='N')
			shot_place=check_zone_N(_i,  _j, i, j);
		else if(d=='E')
			shot_place=check_zone_E(_i,  _j, i, j);
		else if(d=='W')
			shot_place=check_zone_W(_i,  _j, i, j);
		else if(d=='S')
			shot_place=check_zone_S(_i,  _j, i, j);
		else
			continue;
	if(shot_place!="")
		return shot_place;
		id++;
	}
	return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
std::string competition::check_zone_N(int _i, int _j,int ii, int jj)
{
	if(_i-ii==0 && _j-jj==0)
		return "head";
	else if(_i-ii==1 && _j-jj==0)
		return "chest";
	else if((_i-ii==1 && _j-jj==-1)||(_i-ii==1 && _j-jj==1))
		return "arms";
	else if(_i-ii==2 && _j-jj==0)
		return "abdoman";
	else if((_i-ii==3 && _j-jj==-1)||(_i-ii==3 && _j-jj==1))
		return "legs";
	else
		return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
std::string competition::check_zone_E(int _i, int _j,int ii, int jj)
{
	if(_i-ii==0 && _j-jj==0)
		return "head";
	else if(_i-ii==0 && _j-jj==-1)
		return "chest";
	else if((_i-ii==-1 && _j-jj==-1)||(_i-ii==1 && _j-jj==-1))
		return "arms";
	else if(_i-ii==0 && _j-jj==-2)
		return "abdoman";
	else if((_i-ii==1 && _j-jj==-3)||(_i-ii==-1 && _j-jj==-3))
		return "legs";
	else
		return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
std::string competition::check_zone_W(int _i, int _j,int ii, int jj)
{
	if(_i-ii==0 && _j-jj==0)
		return "head";
	else if(_i-ii==0 && _j-jj==1)
		return "chest";
	else if((_i-ii==-1 && _j-jj==1)||(_i-ii==1 && _j-jj==1))
		return "arms";
	else if(_i-ii==0 && _j-jj==2)
		return "abdoman";
	else if((_i-ii==1 && _j-jj==3)||(_i-ii==-1 && _j-jj==3))
		return "legs";
	else
		return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
std::string competition::check_zone_S(int _i, int _j,int ii, int jj)
{
	if(_i-ii==0 && _j-jj==0)
		return "head";
	else if(_i-ii==-1 && _j-jj==0)
		return "chest";
	else if((_i-ii==-1 && _j-jj==-1)||(_i-ii==-1 && _j-jj==1))
		return "arms";
	else if(_i-ii==-2 && _j-jj==0)
		return "abdoman";
	else if((_i-ii==-3 && _j-jj==-1)||(_i-ii==-3 && _j-jj==1))
		return "legs";
	else
		return "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void competition::who_is_winner()
{
	if(players.size()==1)
	{
		cout<<endl<<"player <"<<players[0].get_player_id()<<"> won the game";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
Weapon* competition::find_weapon(std::string name)
{
	for (int i = 0; i < get_weapons_size(); i++)
	{
		if(weapons[i].get_name()==name)
			return &weapons[i];
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int competition::get_ith_player_id(int vector_place)
{
	if(vector_place<players.size())
		return players[vector_place].get_player_id();
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
Shot::Shot(Player* _shooter, Player* _is_shot)
{
	if(_shooter!=NULL && _is_shot!=NULL)
	{
		shooter=_shooter;
		is_shot=_is_shot;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void Shot::set_parameters(double _damage, double _source_destination, std::string _shot_place)
{
	//cerr<<_shot_place<<endl;
	if(_shot_place!="head" && _shot_place!="chest" && _shot_place!="abdoman" && _shot_place!="arms" && _shot_place!="legs")
		exit(EXIT_FAILURE);
	if(_source_destination<0)
		exit(EXIT_FAILURE);
	if(_damage<0)
		exit(EXIT_FAILURE);
	damage=_damage;
	source_destination=_source_destination;
	shot_place=_shot_place;
}
void tournament::get_most_kill(int n, string mode, string side)
{
	if(n<person_size())
	{
		if(mode=="kills")
		{
			if(side=="most")
				sort(persons.begin(), persons.end(),kill_most);
			else if(side=="least")
				sort(persons.begin(), persons.end(),kill_least);
			for(int i=0; i<n; i++)
				cout<<endl<<persons[i].get_name()<<" ("<<persons[i].get_id()<<") has <"<<persons[i].get_kill()<<"> kills in total";
		}
		else if(mode=="deaths")
		{
			if(side=="most")
				sort(persons.begin(), persons.end(),death_most);
			else if(side=="least")
				sort(persons.begin(), persons.end(),death_least);
			for(int i=0; i<n; i++)
				cout<<endl<<persons[i].get_name()<<" ("<<persons[i].get_id()<<") died <"<<persons[i].get_death()<<"> times in total";
		}
		else if(mode=="capital")
		{
			if(side=="most")
				sort(persons.begin(), persons.end(),capital_most);
			else if(side=="least")
				sort(persons.begin(), persons.end(),capital_least);
			for(int i=0; i<n; i++)
				cout<<endl<<persons[i].get_name()<<" ("<<persons[i].get_id()<<") has <"<<persons[i].get_fund()<<"> dollars in total";
		}
	}
}
