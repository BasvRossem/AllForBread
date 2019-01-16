class State {
public:
	virtual State * update() = 0;
protected:
	sf::RenderWindow & window;
	State(sf::RenderWindow&w) : window(w) {}
};