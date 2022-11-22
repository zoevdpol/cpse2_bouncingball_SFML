#include <iostream>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include <functional>


//ACTION CLASS////////////////////////////////////////////////////////////////////////////////////////////////////////
class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(std::function< bool() > condition, std::function< void() > work) : 
        condition( condition ), 
   		work( work ) 
	{}

	void operator()(){
   		if( condition() ){
      		work();
   		}
	}

	// extra constructor for keyboard key presses
	action(sf::Keyboard::Key key, std::function< void() > work) :
		condition([ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }),
		work(work)
	{}

	// extra constructor for mouse button presses
	action(sf::Mouse::Button button, std::function< void() > work) :
		condition([ button ]()->bool { return sf::Mouse::isButtonPressed( button );}),
		work(work)
	{}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2I TO 2F CONVERSION FUNCTION
sf::Vector2f Vector2f_from_Vector2i(sf::Vector2i rhs) {
	return sf::Vector2f((float)rhs.x, (float)rhs.y);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] ){

	std::cout << "Starting application 01-04 array of deltas\n";
	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	ball my_ball{ sf::Vector2f{ 320.0, 240.0 }, sf::Color::Green, sf::Vector2f{ 1.0, 1.0} };
	rectangle block(sf::Vector2f{120, 80}, sf::Vector2f{40, 100}, sf::Color::Red, sf::Vector2f{ 1.0, 1.0} );

	//walls
	rectangle wall1{sf::Vector2f{0.0,40.0}, sf::Vector2f{44.0,400.0}, sf::Color::Blue, sf::Vector2f{1.0, 1.0}};
   	rectangle wall2{sf::Vector2f{0.0,440.0}, sf::Vector2f{640.0,40.0}, sf::Color::Magenta, sf::Vector2f{1.0, 1.0}};
   	rectangle wall3{sf::Vector2f{600.0,40.0}, sf::Vector2f{44.0,400.0}, sf::Color::Cyan, sf::Vector2f{1.0, 1.0}};
   	rectangle wall4{sf::Vector2f{0.0,0.0}, sf::Vector2f{640.0,40.0}, sf::Color::Yellow, sf::Vector2f{1.0, 1.0}};

	//list drawables
	std::array<drawable*, 6> drawablelist= { &wall1, &wall2, &wall3, &wall4, &my_ball, &block };

	//Actions
	action actions[] = {
		action(sf::Keyboard::Left,[&]{block.move( sf::Vector2f( -1.0,  0.0 )); }),
		action(sf::Keyboard::Right,[&]{block.move( sf::Vector2f( 1.0,  0.0 )); }),
		action(sf::Keyboard::Up,[&]{block.move( sf::Vector2f( 0.0,  -1.0 )); }),
		action(sf::Keyboard::Down,[&]{block.move( sf::Vector2f( 0.0,  1.0 )); }),
		action(sf::Mouse::Left,[&]{block.jump(Vector2f_from_Vector2i( sf::Mouse::getPosition(window))); }),
		action([&]()-> bool {return true;}, [&](){my_ball.updateposition();})
	};

	while (window.isOpen()) {
		for (auto & action : actions) {
			action();
		}

		for(auto object : drawablelist){
			drawable *ball_pointer = &my_ball;
			if(ball_pointer != object){
				ball_pointer->overlap(*object);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			block.jump(Vector2f_from_Vector2i(sf::Mouse::getPosition(window)));
		}

		sf::Event event;
		if( window.pollEvent(event) ){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		//drawing
		my_ball.draw(window);
		block.draw(window);
		wall1.draw(window);
		wall2.draw(window);
		wall3.draw(window);
		wall4.draw(window);

		window.display();
		sf::sleep(sf::milliseconds(20));


	}

	}



