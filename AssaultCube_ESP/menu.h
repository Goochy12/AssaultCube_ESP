#pragma once
#include <iostream>
#include <vector>

class Menu
{
private:
	std::vector<int> *menuItems;

public:
	Menu(std::vector<int> menuItems);
	~Menu();
};

