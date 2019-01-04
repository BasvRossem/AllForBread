#pragma once
#include <SFML/Graphics.hpp>
class VirtualScreen : public sf::Drawable
{
private:
	//Location of the Virtual Screen
	sf::Vector2f location = { 0,0 };

	//The core of the virtual screen
	sf::RenderTexture vScreen;
public:
	//constructor applying the size of the virtual screen
	VirtualScreen(const sf::Vector2f& screenSize = { 0.0f,0.0f });

	//Inherited via Drawable
	//The draw function that allows you to use window.draw(this_class)
	//Draws the virtual screen
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	//Set the location of the virtual screen
	inline void setLocation(const sf::Vector2f& loc) { location = loc; }

	//Resets the size of the virtual screen
	inline void setSize(const sf::Vector2f& screenSize) { vScreen.create(screenSize.x, screenSize.y); }

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
	
	bool collision(const sf::Vector2i & point);

	template <typename T>
	inline bool collision(const sf::Vector2i & point, T object) 
	{
		object.move(location);
		return object.getGlobalBounds().contains(point.x, point.y);
	}

	

};

