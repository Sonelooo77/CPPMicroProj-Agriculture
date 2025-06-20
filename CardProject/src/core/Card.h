#pragma once
#include <string>
#include <vector>
#include <sstream>


class Card {
	private:
		std::string name;
		int cost;

    public:
        int getCost() const { return cost; }
        std::string getName() const { return name; }
		virtual const std::vector<int>& getLastDiceDetails() const { static std::vector<int> empty; return empty;}
        Card(std::string name, int cost) : name(name), cost(cost) {}
		virtual void play() = 0;
        virtual ~Card() = default;
        virtual bool canBePlayed(int& remaining_cost) const { return remaining_cost >= cost;}
        virtual int getLastScore() const { return 0; }
        virtual bool isResourceCard() const { return false; }
};