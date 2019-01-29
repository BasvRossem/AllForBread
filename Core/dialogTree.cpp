#include "dialogTree.hpp"

DialogOption::DialogOption(std::string text, std::shared_ptr<DialogNode> nextNode, std::function<void()> event):
	text(text),
	nextNode(nextNode),
	event(event)
{}

const std::string DialogOption::getText() {
	return text;
}

const std::shared_ptr<DialogNode> DialogOption::getNextNode() {
	return nextNode;
}

const std::function<void()> DialogOption::getEvent(){
	return event;
}

void DialogNode::addDialogOption(std::shared_ptr<DialogOption> option){
	dialogOptions.push_back(option);
}

DialogNode::DialogNode(std::string text) :
	text(text)
{}

const size_t DialogNode::getOptionsCount() {
	return dialogOptions.size();
}

const std::string DialogNode::getOptionTextByIndex(int i) {
	return dialogOptions[i]->getText();
}

const std::function<void()> DialogNode::getOptionEventByIndex(int i){
	return dialogOptions[i]->getEvent();
}

const std::string DialogNode::getText() {
	return text;
}

const std::shared_ptr<DialogNode> DialogNode::getOptionNextNodeByIndex(int i) {
	return dialogOptions[i]->getNextNode();
}

void DialogNode::removeAllOptions(){
	dialogOptions.clear();
}

DialogTree::DialogTree()
{}
void DialogTree::addNode(std::shared_ptr< DialogNode> node) {
	dialogNodes.push_back(node);
}

void DialogTree::destroyTree()
{
}

void DialogTree::performDialogue(DialogBox& diaBox, bool sound, int speed){

	if (!dialogNodes.empty()) {
		std::shared_ptr<DialogNode> currentNode = dialogNodes[0];
		while (currentNode) {
			diaBox.print(currentNode->getText(),sound, speed);
			std::cout << currentNode->getOptionsCount();
			if (currentNode->getOptionsCount() > 0){
				std::vector<std::pair<std::string, std::function<void()>>> choices;
				for (size_t i = 0; i < currentNode->getOptionsCount(); i++) {
					choices.push_back(std::pair<std::string, std::function<void()>>(currentNode->getOptionTextByIndex(i), currentNode->getOptionEventByIndex(i)));
				}
				int choice = diaBox.printChoices(choices);
				currentNode = currentNode->getOptionNextNodeByIndex(choice);
			}else {
				break;
			}
			
		}
	}
}
