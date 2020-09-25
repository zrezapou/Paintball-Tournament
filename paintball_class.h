#ifndef PAINTBALL_CLASS_H_
#define PAINTBALL_CLASS_H_
class competition;
class Weapon{
public:
	Weapon(std::string _name, double _power, double _effective_range, double _cost);
	double get_power(){return power;}
	double get_range(){return effective_range;}
	double get_cost(){return cost;}
	std::string get_name(){return name;}

private:
	double power;
	double effective_range;
	double cost;
	std::string name;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class Person{
public:
	Person(std::string _name, int _id, double _fund, int _skill);
	int get_kill(){return kill;}
	void inc_kill(){kill++;}
	int get_death(){return death;}
	void inc_death(){death++;}
	int get_skill(){return skill;}
	double get_fund(){return fund;}
	void set_fund(double _fund);
	int get_id(){return id;}
	std::string get_name(){return name;}
	void pay_cost(double _cost);
	void reach_money(double money);
private:
	int kill;
	int death;
	int skill;
	double fund;
	int id;
	std::string name;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class Sponsor{
public:
	Sponsor(Person* _person, double _cash);
	double get_cash(){return cash;}
	void refine_debt(){person->reach_money(cash);}
	int get_id(){return person->get_id();}
private:
	Person* person;
	double cash;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player{
public:
	Player(int _i, int _j, int _d, Person* _person);
	int get_i(){return i;}
	int get_j(){return j;}
	int get_d(){return d;}
	int get_life(){return life;}
	void push_sponsor(Sponsor sponsor){sponsors.push_back(sponsor);}
	int get_person_id(){return person->get_id();}
	void pay_weapon(double _cost){person->pay_cost(_cost);}
	void set_weapon(Weapon* _weapon){weapon=_weapon;}
	Weapon* get_weapon_addr(){return weapon;}
	double player_cash(){return person->get_fund();}
	int get__skill(){return person->get_skill();}
	int get_player_id(){return person->get_id();}
	int get_chest(std::string axis);
	double get__range(){return weapon->get_range();}
	double get_bullet_power(){return weapon-> get_power();}
	void apply_damage(double _damage);
	int inc_one_kill(){person->inc_kill();}
	int get_kill(){return person->get_kill();}
	int get_death(){return person->get_death();}
	int inc_one_death(){person->inc_death();}
	void account_refinement(competition& c1);
	void inc_cash(double _cash){person->reach_money(_cash);}
private:
	std::vector<Sponsor>sponsors;
	int i;
	int j;
	int d;
	double life;
	Weapon* weapon;
	Person* person;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
class Shot{
public:
	Shot(Player* _shooter, Player* _is_shot);
	std::string get_shot_place(){return shot_place;}
	int get_damage(){return damage;}
	int get_source_destination(){return source_destination;}
	void set_parameters(double _damage, double _source_destination, std::string _shot_place);
	void calc_shot_place();
private:
	Player* shooter;
	Player* is_shot;
	std::string shot_place;
	double damage;
	int source_destination;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
class competition{
public:
	Player* get_player_addr(int _id);
	std::vector<Shot>get_shots(){return shots;}
	double get_ticket_revenue(){return ticket_revenue;}
	void player_push(Player _player){players.push_back(_player);}
	void shot_push(Shot s1){shots.push_back(s1);}
	double get_match_cost(){return match_cost;}
	void set_cost(double _match_cost, double _ticket_revenue, long int _seed);
	void set_sponsor(int _id, Sponsor sponsor);
	bool find_player(int _id);
	int get_player_size(){return players.size();}
	long int get_seed(){return seed;}
	int get_ith_player_id(int vector_place);
	std::string find_shot_place(int _x, int _y, int& _id);
	void kill_person(Player* shooter, Player* is_shot);
	void who_is_winner();
	void surrender_ith_on_vector(int _place_on_vec){players.erase(players.begin()+_place_on_vec);}
	int get_weapons_size(){return weapons.size();}
	Weapon* find_weapon(std::string name);
	void push_weapon(Weapon _weapon){weapons.push_back(_weapon);}
	//bool myfunction(Player* i,Player* j){return ();}
private:
	std::string check_zone_N(int _i, int _j, int ii, int jj);
	std::string check_zone_S(int _i, int _j, int ii, int jj);
	std::string check_zone_E(int _i, int _j, int ii, int jj);
	std::string check_zone_W(int _i, int _j, int ii, int jj);
	std::vector<Player>players;
	std::vector<Shot> shots;
	std::vector<Weapon> weapons;
	double ticket_revenue;
	double match_cost;
	long int seed;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////
class tournament{
public:
	void push_persons(Person _person){persons.push_back(_person);}
	void push_competition(competition c1){competitions.push_back(c1);}
	int person_size(){return persons.size();}
	void get_most_kill(int n, std::string mode, std::string side);
	Person* get_addr_person(int _id);
	struct kill_most {
  		bool operator() (Person i,Person j)
  		{ return (i.get_kill() > j.get_kill());}}kill_most;
  	struct death_most {
  		bool operator() (Person i,Person j)
  		{ return (i.get_death() > j.get_death());}}death_most;
  	struct capital_most {
  		bool operator() (Person i,Person j)
  		{ return (i.get_fund() > j.get_fund());}}capital_most;
  	struct kill_least {
  		bool operator() (Person i,Person j)
  		{ return (i.get_kill() < j.get_kill());}}kill_least;
  	struct death_least {
  		bool operator() (Person i,Person j)
  		{ return (i.get_death() < j.get_death());}}death_least;
  	struct capital_least {
  		bool operator() (Person i,Person j)
  		{ return (i.get_fund() < j.get_fund());}}capital_least;

private:
	std::vector<Person> persons;
	std::vector<competition>competitions;
};
#endif
