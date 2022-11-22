#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "hwlib.hpp"
#include "iostream"
#include "rectangle.hpp"

 void ball::draw( sf::RenderWindow & window )  {
  	sf::CircleShape circle;
  	circle.setRadius(size);
	circle.setFillColor(color);
  	circle.setPosition(position);
  	window.draw(circle);
  }

 void ball::move( sf::Vector2f delta ) {
	position += delta;
 }

void ball::jump( sf::Vector2f target ) {
 	position = target;
 }

void ball::updateposition(){
	position.x += speed.x;
	position.y += speed.y;
}

sf::FloatRect ball:: getBoundingbox(){
	sf::CircleShape circle;
	circle.setRadius(size);
	circle.setPosition(position);
	return circle.getGlobalBounds();
}

void ball::overlap(drawable &object) {
	auto circlebox = getBoundingbox();
	auto objectbox = object.getBoundingbox();
	if(objectbox.intersects(circlebox)){
		interact(object);
	}
}

 void ball::interact(drawable &object){
	sf::FloatRect circlebox = object.getBoundingbox();
    sf::Vector2f bounce = this->getBounce(circlebox);
    speed.x *= bounce.x;
    speed.y *= bounce.y;

 }

 sf::Vector2f ball::getBounce(sf::FloatRect &thing)   {
            auto boundingbox = getBoundingbox();
            sf::FloatRect leftsideblock = sf::FloatRect(boundingbox.left, boundingbox.top+10, 5, boundingbox.height-15);
            sf::FloatRect rightsideblock = sf::FloatRect(boundingbox.left + boundingbox.width-5, boundingbox.top+10, 5, boundingbox.height-15);
            sf::FloatRect uppersideblock = sf::FloatRect(boundingbox.left+10, boundingbox.top, boundingbox.width-15, 5);
            sf::FloatRect lowersideblock = sf::FloatRect(boundingbox.left+5, boundingbox.top + boundingbox.height-5, boundingbox.width-10, 5);

            if(thing.intersects(uppersideblock)){
                return sf::Vector2f(1, -1);
            }
            else if (thing.intersects(lowersideblock)){
                return sf::Vector2f(1, -1);
            }
            else if(thing.intersects(leftsideblock)){
                return sf::Vector2f(-1, 1);
            }
            else if(thing.intersects(rightsideblock)){
                return sf::Vector2f(-1, 1);
            }
            else{
                return sf::Vector2f{1,1};
            }
            
        }


