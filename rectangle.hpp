#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP
#include "drawable.hpp"
#include <iostream>

#include <SFML/Graphics.hpp>

class rectangle : public drawable {
    private:
        sf::Vector2f size;
    public:
        rectangle( sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Vector2f bounce):
        drawable(position, color, bounce),
            size{size}
            {}


	    void draw( sf::RenderWindow & window ) override {
             sf::RectangleShape rectangle;
	         rectangle.setSize( size );
             rectangle.setFillColor(color);
             rectangle.setPosition( position );
	         window.draw( rectangle );
         }
        
        void move( sf::Vector2f delta ) {
	  	    position += delta;
        }

        void jump( sf::Vector2f target ) {
 	        position = target;
        }

        //boundingboxes "aanmaken" 
        sf::FloatRect getBoundingbox() override{
	        sf::RectangleShape rectangle;
	        rectangle.setSize(size);
	        rectangle.setPosition(position);
	        return rectangle.getGlobalBounds();
        }

        //kijken als er een overlap/intersect is
        void overlap(drawable &object) override {
	        auto rectanglebox = getBoundingbox();
	        auto objectbox = object.getBoundingbox();
	            if(objectbox.intersects(rectanglebox)){
		            interact(object);
	         }
         }

        //interact functie die niks doet maar staat in drawable dus moet
        void interact(drawable &object) {}

        



};

#endif