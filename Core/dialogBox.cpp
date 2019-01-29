#include "dialogBox.h"

DialogBox::DialogBox(sf::RenderWindow& window, uint_least16_t bufferWidth, uint_fast16_t maxLines, std::string fontFileLocation, sf::Vector2i size, sf::Vector2f position, sf::Color backgroundColor, sf::Color edgeColor) :
	w(window),
	bufferWidth(bufferWidth),
	maxLines(maxLines),
	diaBox(size.x, size.y),
	backgroundColor(backgroundColor)
{

	if (!font.loadFromFile(fontFileLocation)) {
		//throw fileNotFound(fontFileLocation)
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(5, 5);
	diaBox.setLocation(position);

	backgroundSquare.setSize(sf::Vector2f(float(size.x - 6), float(size.y - 6)));
	backgroundSquare.setPosition(3, 3);
	backgroundSquare.setFillColor(backgroundColor);
	backgroundSquare.setOutlineColor(edgeColor);
	backgroundSquare.setOutlineThickness(3);
}

void DialogBox::draw() {
	diaBox.drawSurfaceClear(backgroundColor);
	diaBox.drawSurfaceDraw(backgroundSquare);
	diaBox.drawSurfaceDraw(text);
	diaBox.drawSurfaceDisplay();
	w.draw(diaBox);
}

void DialogBox::setSound(std::string soundFileName){
	if (!soundBuffer.loadFromFile(soundFileName)) {
		//throw error
	}

	feedbackSound.setBuffer(soundBuffer);
	feedbackSound.setVolume(20);
}

void DialogBox::setBackgroundColor(sf::Color color){
	backgroundColor = color;
}

void DialogBox::setTextFillColor(sf::Color color){
	text.setFillColor(color);
}

void DialogBox::setTextOutlineColor(sf::Color color){
	text.setOutlineColor(color);
}

void DialogBox::setTextCharacterSize(int size){
	text.setCharacterSize(size);
}

void DialogBox::setTextLetterSpacing(float spacingFactor){
	text.setLetterSpacing(spacingFactor);
}

void DialogBox::setTextLineSpacing(float spacingFactor){
	text.setLineSpacing(spacingFactor);
}

void DialogBox::setTextPosition(sf::Vector2f position){
	text.setPosition(position);
}


std::vector<std::string> DialogBox::wordwrap(std::string& str) {
	std::vector<std::string> returnstring;
	unsigned int beginLine = 0;

	while (beginLine < str.size()) {
		const unsigned int idealEnd = beginLine + bufferWidth;
		unsigned int endLine = idealEnd < str.size() ? idealEnd : str.size() - 1;
		if (endLine == str.size() - 1) {
			returnstring.push_back(str.substr(beginLine, (endLine - beginLine + 1)).append("\n"));
			++endLine;
		}
		else if (std::isspace(str[endLine]) || str[endLine] == ',' || str[endLine] == '.') {
			returnstring.push_back(str.substr(beginLine, (endLine - beginLine + 1)).append("\n"));
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
				returnstring.push_back(str.substr(beginLine, (end - beginLine + 1)).append("\n"));
			}
			else {

				returnstring.push_back(str.substr(beginLine, (endLine - beginLine + 1)).append("\n"));
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

void DialogBox::print(std::string str, bool sound, int speed) {
	std::vector<std::string> strVect = wordwrap(str);
	uint_fast16_t page = 0;

	uint_fast16_t oldpage = 1;
	size_t max = 0;

	clear();
	draw();
	while (true) {
		diaBox.drawSurfaceClear();
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

				diaBox.drawSurfaceClear();
				text.setString(tempStr.substr(0, i));
				if (sound && tempStr[i] != ' ' && feedbackSound.getBuffer() != NULL){
					float pitch = 1.0f;
					feedbackSound.setPitch(pitch);
					feedbackSound.play();
				}
				draw();
				sf::sleep(sf::milliseconds(speed));
				w.display();
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



int DialogBox::printChoices(std::vector<std::pair<std::string, std::function<void()>>>& choices) {
	int selectedValue = -1;
	uint_fast16_t page = 0;
	uint_fast16_t oldPage = 0;
	bool change = true;
	bool needNext = false;
	size_t choiceMax = 8;
	size_t max = 0;
	size_t overAllMax = 0;
	size_t begin = 0;
	size_t end = 0;

	KeyboardHandler keyHandle;
	keyHandle.setOverride(true);

	bool selected = false;

	clear();
	if (choices.size() > 0){
		while (true) {
			diaBox.drawSurfaceClear();
			if (change) {
				std::stringstream tempStr;
				int oldmax = max;


				max = maxLines < choiceMax ? maxLines : choiceMax;
				if (page > 0){
					begin = 1;
					max -= 1;
					int keyIndex = 26 + 1;
					tempStr << "1. previous\n";
					std::function<void()> func = [&] {page--; change = true; };
					keyHandle.addListener((sf::Keyboard::Key)keyIndex, func);
				}else {
					begin = 0;
				}
				if (page >= oldPage){
					if (overAllMax + max > choices.size()) {
						max = choices.size() - overAllMax;
						overAllMax = choices.size();
						needNext = false;
					}
					else {
						max -= 1;
						overAllMax += max;
						needNext = true;
					}
				}else if(page < oldPage) {
					if (overAllMax - max > choices.size()) {
						max = choices.size() - overAllMax;
						overAllMax = choices.size();
						needNext = false;
					}
					else {
						max -= 1;
						overAllMax -= oldmax;
						needNext = true;
					}
					if (page == 0){
						overAllMax = max;
					}
				}
				
				int index = overAllMax - max;
				for (size_t i = 0; i < max; i++){
					int keyIndex = 27 + i + begin;
					tempStr << (i + begin + 1) << ". " << choices[index + i].first << '\n';
					keyHandle.addListener((sf::Keyboard::Key)keyIndex, choices[index + i].second);

				}

				if (needNext){
					int keyIndex = 26;
					tempStr << "0. next\n";
					std::function<void()> func = [&]() {page++; change = true; };
					keyHandle.addListener((sf::Keyboard::Key)keyIndex, func);
				}else {
					int keyIndex = 26;
					keyHandle.removeListener((sf::Keyboard::Key)keyIndex);
				}

				text.setString(tempStr.str());
				oldPage = page;

				change = false;
				
			}else {
				sf::Event event;
				while (w.pollEvent(event)) {
					if (event.type == sf::Event::KeyPressed) {
						if (event.type == sf::Event::KeyPressed){
							keyHandle.processKey(event.key.code);
						}
						if (event.type == sf::Event::Closed)
							w.close();
						if (event.key.code >= static_cast<int>(sf::Keyboard::Num1 + begin) && event.key.code <= static_cast<int>(sf::Keyboard::Num0 + max + begin)){
							selected = true;
							int index = overAllMax - max;
							selectedValue = (event.key.code - 26) + index + begin - 1;
						}
					}
				}
				draw();
				w.display();

			}
			if (selected) {
				return selectedValue;
			}

		}
	}
	return -1;
}