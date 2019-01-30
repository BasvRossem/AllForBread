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
	///\brief
	/// Returns string of the text assigned to this dialogOption
	const std::string getText();
	///\brief
	/// Return the function event assigned to this dialogOption
	const std::function<void()> getEvent();
	///\brief
	/// Returns the nextNode assigned to this dialogOption
	const std::shared_ptr<DialogNode> getNextNode();
};

class DialogNode{
private:
	std::string text;
	std::vector<std::shared_ptr<DialogOption>> dialogOptions;
public:
	DialogNode(std::string text);
	///\brief
	/// Adds a dialog option to the dialogoptions vector
	void addDialogOption(std::shared_ptr<DialogOption> option);
	///\brief
	/// returns the text assigned to the node
	const std::string getText();
	///\brief
	/// Get the ammount of options
	const size_t getOptionsCount();
	///\brief
	/// returns the text of an option by index
	const std::string getOptionTextByIndex(int i);
	///\brief
	/// Return the event of an option from the vector by index
	const std::function<void()> getOptionEventByIndex(int i);
	///\brief
	/// return the next node of an option from the vector by index
	const std::shared_ptr<DialogNode> getOptionNextNodeByIndex(int i);
	///\brief
	/// Clears the vector
	void removeAllOptions();
};

class DialogTree{
private:
	std::vector< std::shared_ptr<DialogNode>> dialogNodes;
public:
	DialogTree();
	///\brief
	/// displays the dialogTree
	void performDialogue(DialogBox& diaBox, bool sound = true, int speed = 100);
	///\brief
	/// add a node to the dialogTree
	void addNode(std::shared_ptr< DialogNode> node);

};

