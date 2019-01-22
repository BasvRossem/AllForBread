#include "dialogBox.h"

DialogBox::DialogBox(sf::RenderWindow& window, uint_least16_t bufferWidth, uint_fast16_t maxLines, std::string fontFileLocation, sf::Vector2i size, sf::Vector2f position, std::string soundFileName) :
	w(window),
	bufferWidth(bufferWidth),
	maxLines(maxLines),
	diaBox(size.x, size.y)
{

	if (!font.loadFromFile(fontFileLocation)) {
		//throw fileNotFound(fontFileLocation)
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	diaBox.setLocation(position);

	if (!soundBuffer.loadFromFile(soundFileName)) {
		//throw error
	}

	feedbackSound.setBuffer(soundBuffer);
	feedbackSound.setVolume(20);
}

void DialogBox::draw() {
	diaBox.drawSurfaceClear();
	diaBox.drawSurfaceDraw(text);
	diaBox.drawSurfaceDisplay();
	w.draw(diaBox);
}


std::vector<std::string> DialogBox::wordwrap(std::string& str) {
	std::vector<std::string> returnstring;
	unsigned int beginLine = 0;

	while (beginLine < str.size()) {
		const unsigned int idealEnd = beginLine + bufferWidth;
		unsigned int endLine = idealEnd < str.size() ? idealEnd : str.size() - 1;
		if (endLine == str.size() - 1) {
			returnstring.push_back(str.substr(beginLine, (endLine - beginLine)).append("\n"));
			++endLine;
		}
		else if (std::isspace(str[endLine]) || str[endLine] == ',' || str[endLine] == '.') {
			returnstring.push_back(str.substr(beginLine, (endLine - beginLine)).append("\n"));
			++endLine;
		}
		else {
			unsigned int end = endLine;
			while (!std::isspace(str[end]) && str[end] != ',' && str[end] != '.') {
				if (end == beginLine) {
					break;
				}
				--end;
			}
			if (end != beginLine) {
				endLine = end;
				endLine++;
				returnstring.push_back(str.substr(beginLine, (end - beginLine)).append("\n"));
			}
			else {

				returnstring.push_back(str.substr(beginLine, (endLine - beginLine)).append("\n"));
			}
		}
		beginLine = endLine;
	}

	return returnstring;
}

void DialogBox::printPerm(std::vector<std::string>& textVector) {
	if (textVector.size() <= maxLines) {
		std::string textString;
		for (size_t i = 0; i < textVector.size(); i++) {
			textString.append(textVector[i]).append("\n");
		}
		text.setString(textString);
	}
}

void DialogBox::print(std::string& str, bool sound, int speed) {
	std::vector<std::string> strVect = wordwrap(str);
	uint_fast16_t page = 0;

	uint_fast16_t oldpage = 1;
	size_t max = 0;

	clear();
	draw();
	while (true) {
		unsigned int maxLTimesPage = (maxLines)* page;
		if (maxLTimesPage > strVect.size()) {
			break;
		}
		if (oldpage != page) {
			std::string tempStr;
			if (strVect.size() - maxLTimesPage < maxLines) {
				max = strVect.size() - maxLTimesPage;
			}
			else {
				max = maxLines;
			}
			for (size_t i = 0; i < max; i++) {
				int curline = i + maxLTimesPage;
				tempStr.append(strVect[curline]);
			}
			

			for (size_t i = 0; i < tempStr.size(); i++) {
				text.setString(tempStr.substr(0, i));
				if (sound){
					float pitch = 1.0f;
					feedbackSound.setPitch(pitch);
					feedbackSound.play();
				}
				draw();
				w.display();
				sf::sleep(sf::milliseconds(speed));

			}
			draw();
			oldpage = page;
			tempStr.clear();
		}
		else {
			sf::Event event;
			while (w.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Enter) {
						page++;
					}if (event.type == sf::Event::Closed) {
						w.close();
					}
				}
			}

		}
		draw();
		w.display();
	}
}

void DialogBox::clear() {
	text.setString("");
	draw();
}



void DialogBox::printChoices(std::vector<std::pair<std::string, std::function<void()>>>& choices) {
	
	uint_fast16_t page = 0;
	uint_fast16_t oldPage = 1;
	size_t choiceMax = 8;
	size_t max = 0;
	size_t overAllMax = 0;
	size_t begin = 0;
	size_t end = 0;
	KeyboardHandler keyHandle;
	keyHandle.setOverride(true);

	clear();
	if (choices.size() > 0){
		while (true) {
			if (oldPage != page) {
				std::string tempStr;

				maxLines < choiceMax ? max = maxLines : max = choiceMax;
				overAllMax = max;
				if (max + (page * overAllMax) > choices.size()) {
					max = choices.size() - (page * overAllMax);
				}
					std::function<void()> func = [&]() {page--; };
				if (page > 0) {
					begin = 1;
					int index = 26 + 1;
					tempStr.append("1. previous").append("\n");
					keyHandle.addListener((sf::Keyboard::Key)index, func);

				}
				else {
					begin = 0;
				}
				end = max + begin + (page * overAllMax);
				std::cout << end << '\n';
				std::cout << begin + page * overAllMax << '\n';
				for (size_t i = begin + page * overAllMax; i < end; i++) {
					std::cout << i << '\n';
					int index = 26 + i + 1 - (page * overAllMax);
					std::stringstream ss;
					ss << (index - 26) << ". " << choices[i - begin].first << '\n';
					tempStr.append(ss.str());
					keyHandle.addListener((sf::Keyboard::Key)index, choices[i - begin].second);

				}
				if (page * 8 < choices.size()) {
					int index = 26;
					tempStr.append("0. next").append("\n");
					std::function<void()> func = [&]() {page++; };
					keyHandle.addListener((sf::Keyboard::Key)index, func);
				}
				text.setString(tempStr);
				oldPage = page;

			}
			else {
				sf::Event event;
				while (w.pollEvent(event)) {
					if (event.type == sf::Event::KeyPressed) {
						if (event.type == sf::Event::KeyPressed)
							keyHandle.processKey(event.key.code);
						if (event.type == sf::Event::Closed)
							w.close();

					}
				}
				draw();
				w.display();
			}

		}
	}
	
}