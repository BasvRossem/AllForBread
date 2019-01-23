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
		w.clear();
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

	clear();
	if (choices.size() > 0){
		while (true) {
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
					if (overAllMax + max > choices.size() - 1) {
						max = choices.size() - overAllMax - 1;
						overAllMax = choices.size() - 1;
						needNext = false;
					}
					else {
						max -= 1;
						overAllMax += max;
						needNext = true;
					}
				}else if(page < oldPage) {
					if (overAllMax - max > choices.size() - 1) {
						max = choices.size() - overAllMax - 1;
						overAllMax = choices.size() - 1;
						needNext = false;
					}
					else {
						max -= 1;
						overAllMax -= max;
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