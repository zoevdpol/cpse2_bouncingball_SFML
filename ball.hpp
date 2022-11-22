#ifndef _BALL_HPP
#define _BALL_HPP
#include "rectangle.hpp"
#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class ball : public drawable {
public:

	ball(const sf::Vector2f &position, const sf::Color &color, sf::Vector2f bounce, float size = 30.0, sf::Vector2f speed = {8.0, 8.0}):
        drawable(position, color, bounce),
		size{size},
		speed{speed}
		{}
            

	void draw( sf::RenderWindow & window ) override;
	void move( sf::Vector2f delta );
	void jump( sf::Vector2f target );


	sf::FloatRect getBoundingbox() override;
	void updateposition();
	void overlap(drawable &object) override;
	void interact(drawable &object);
	sf::Vector2f getBounce(sf::FloatRect &thing) override;

private:
	float size = 30;
	sf::Vector2f speed = {1.0, 1.0};
};

#endif
