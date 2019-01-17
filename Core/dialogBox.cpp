#include "dialogBox.h"

DialogBox::DialogBox(sf::RenderWindow& window, uint_least16_t bufferWidth, uint_fast16_t maxLines, std::string fontFileLocation, sf::Vector2f& size, sf::vector2f& position) :
	w(window),
	bufferWidth(bufferWidth),
	maxLines(maxLines),
	diaBox(size)
{

	if (!font.loadFromFile(fontFileLocation)) {
		//throw fileNotFound(fontFileLocation)
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	diaBox.setLocation(position);
	draw();
}

void DialogBox::draw() {
	diaBox.drawSurfaceClear();
	diaBox.drawSurfaceDraw(text);
	diaBox.drawSurfaceDisplay();
	w.draw(diaBox);
	w.display();
}

std::vector<std::string> DialogBox::wordwrap(std::string& str) {
	std::vector<std::string> returnstring;
	unsigned int beginLine = 0;

	while (beginLine < str.size()){
		const unsigned int idealEnd = beginLine + bufferWidth;
		unsigned int endLine = idealEnd < str.size() ? idealEnd : str.size() - 1;
		if (endLine == str.size() - 1){
			returnstring.push_back(str.substr(beginLine, (endLine - beginLine)).append("\n"));
			++endLine;
		}else if (std::isspace(str[endLine]) || str[endLine] == ',' || str[endLine] == '.') {
			returnstring.push_back(str.substr(beginLine, (endLine - beginLine)).append("\n"));
			++endLine;
		}else {
			unsigned int end = endLine;
			while (!std::isspace(str[end]) && str[end] != ',' && str[end] != '.'){
				if (end == beginLine){
					break;
				}
				--end;
			}
			if (end != beginLine){
				endLine = end;
				endLine++;
				returnstring.push_back(str.substr(beginLine, (end - beginLine)).append("\n"));
			}else {
				
				returnstring.push_back(str.substr(beginLine, (endLine - beginLine)).append("\n"));
			}
		}
		beginLine = endLine;
	}

	return returnstring;
}




void DialogBox::print(std::string& str) {
	std::vector<std::string> strVect = wordwrap(str);
	page = 0;
	
	uint_fast16_t oldpage = 1;
	size_t max = 0;

	while (true) {
		std::string tempStr;
		int maxLTimesPage = (maxLines) * page;
		if (maxLTimesPage > strVect.size()) {
			break;
		}
		if (oldpage != page) {
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
			text.setString(tempStr);

			oldpage = page;
			tempStr.clear();
		}else {
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
		sf::sleep(sf::milliseconds(1000 / 60));
	}
}