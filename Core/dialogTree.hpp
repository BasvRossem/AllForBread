#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "dialogBox.h"


class DialogNode;

class DialogOption {
private:
	std::string text; 
	std::shared_ptr<DialogNode> nextNode;
	std::function<void()> event;

public:
	DialogOption(std::string text, std::shared_ptr<DialogNode> nextNode, std::function<void()> event = [] {});
	const std::string getText();
	const std::function<void()> getEvent();
	const std::shared_ptr<DialogNode> getNextNode();
};

class DialogNode{
private:
	std::string text;
	std::vector<std::shared_ptr<DialogOption>> dialogOptions;
public:
	DialogNode(std::string text);
	void addDialogOption(std::shared_ptr<DialogOption> option);
	const std::string getText();
	const size_t getOptionsCount();
	const std::string getOptionTextByIndex(int i);
	const std::function<void()> getOptionEventByIndex(int i);
	const std::shared_ptr<DialogNode> getOptionNextNodeByIndex(int i);

};

class DialogTree{
private:
	std::vector< std::shared_ptr<DialogNode>> dialogNodes;
public:
	DialogTree();
	void destroyTree();
	void performDialogue(DialogBox& diaBox);
	void addNode(std::shared_ptr< DialogNode> node);

};

