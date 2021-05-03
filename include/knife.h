#pragma once
#ifndef KNIFE_H
#define KNIFE_H
#include <SFML/Graphics.hpp>

class Knife
{
public:
  sf::Vector2f getKnifePos(){ return knifePos; }
	float getKnifeSpeed(){ return knifeSpeed; }
	void setKnifePos(sf::Vector2f &pos){ this->knifePos = pos; }
private:
  sf::Vector2f knifePos;
  float knifeSpeed = 2500;
}
#endif
