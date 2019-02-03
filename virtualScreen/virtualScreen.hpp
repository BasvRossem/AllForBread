#pragma once
#include <SFML/Graphics.hpp>
class VirtualScreen : public sf::Drawable
{
private:
	//Location of the Virtual Screen
	sf::Vector2f location = { 0,0 };

	//The core of the virtual screen
	sf::RenderTexture vScreen;

	//Resets the size of the virtual screen 
	inline void setSize(const unsigned int & width, const unsigned int & height) { vScreen.create(width, height); }
public:
	//constructor applying the size of the virtual screen
	VirtualScreen(const unsigned int & width = 20, const unsigned int & height = 20);

	//Inherited via Drawable
	//The draw function that allows you to use window.draw(this_class)
	//Draws the virtual screen
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	//Set the location of the virtual screen
	inline void setLocation(const sf::Vector2f& loc) { location = loc; }

	//Returns the virtual screen for drawing purposes
	/*
		the virtual screen is used and called just like a regular window
		therefor you musn't forget to call clear and display;

		Example:
		class specialSquare {
			private:
			VirtualScreen screen;

			public:
			void draw(sf::RenderWindow& w) {
				sf::RectangleShape rect({5,5});
				rect.setFillColor(sf::Color::Green);

				screen.drawSurfaceClear();
				screen.drawSurfaceDraw(rect);
				screen.drawSurfaceDisplay();

				w.draw(screen);
			}
		}
		
	*/
	inline void drawSurfaceClear(const sf::Color& color = sf::Color(0, 0, 0, 255)) { vScreen.clear(color); }
	inline void drawSurfaceDraw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default) { vScreen.draw(drawable, states); }
	inline void drawSurfaceDisplay() { vScreen.display(); }
	
	//check collision with the virtualscreen itself
	bool collision(const sf::Vector2i & point);

	//check collision with the given object with the offset of the virtual screen
	template <typename T>
	inline bool collision(const sf::Vector2i & point, T object) 
	{
		object.move(location);
		return object.getGlobalBounds().contains(point.x, point.y);
	}

	

};

