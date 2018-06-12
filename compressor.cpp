

#include <iostream>
#include "compressor.h"
#include <string>

HFCompressor::~HFCompressor(){ 
	
	while (!mHeap.empty()) {
		Node *tmp = mHeap.top();
		mHeap.pop();
		delete tmp;
	}

	if (mFreqTable)
		delete mFreqTable;

	if (mHfTable)
		delete mHfTable;
}

HFCompressor::HFCompressor() {
	mFreqTable = new std::vector<std::pair<char, int>>;
	mHfTable = new std::map<char, std::string>;
}

void HFCompressor::loadFrequencyTable(const std::vector<std::pair<char, int>> *input) {
	mFreqTable->assign(input->begin(), input->end());
}

std::map<char, std::string>* HFCompressor::generateHFCode() {
	
	addToHeap();
	buildHFTree();

	Node *root = mHeap.top();
	std::string strCode = "";
	getHFCodeHelper(root, strCode);

	return mHfTable;
}

/*std::ostream& operator<<(std::ostream &out, const Node *node) {
	out << node->mSymbol << " - " << node->mFrequency;
	return out;
}

void HFCompressor::printHeap() {
	std::cout << "Heap Count - " << heap.size() << "\n";
	std::cout << heap.top();
	std::cout << "\n";
}*/

Node* HFCompressor::makeNode(std::pair<int, char> pElt) {

	Node *temp = new Node;
	temp->pLeft = nullptr;
	temp->pRight = nullptr;
	temp->mSymbol = pElt.first;
	temp->mFrequency = pElt.second;

	return temp;
}

void HFCompressor::addToHeap() {
	for (auto itr : *mFreqTable) {
		Node *toInsert = makeNode(itr);
		mHeap.push(toInsert);
	}
}

void HFCompressor::buildHFTree() {
	
	while (mHeap.size() > 1) {

		Node *node1 = mHeap.top();
		mHeap.pop();
		Node *node2 = mHeap.top();
		mHeap.pop();

		Node *toInsert = makeNode(std::make_pair<char, int>('~', node1->mFrequency + node2->mFrequency));
		toInsert->pLeft = node1;
		toInsert->pRight = node2;

		mHeap.push(toInsert);
	}
}

void HFCompressor::getHFCodeHelper(Node *root, std::string code) {

	if (!root)
		return;
	
	if (root->mSymbol != '~')
		mHfTable->insert(std::make_pair(root->mSymbol, code));
		//std::cout << root->mSymbol << " : " << code << "\n";

	getHFCodeHelper(root->pLeft, code + "0");
	getHFCodeHelper(root->pRight, code + "1");

}

std::string HFCompressor::encode(const std::string &inStr) {
	std::string outStr = "";
	for (auto itr : inStr)
		outStr = outStr + mHfTable->at(itr);

	return outStr;
}

std::string HFCompressor::decode(const std::string &inStr) {

	std::string outStr = "";
	Node *node = mHeap.top();
	
	for(auto itr : inStr) {
		if (itr == '1') 
			node = node->pRight;
		else 
			node = node->pLeft;
		if (!node->pLeft && !node->pRight) {
			outStr += node->mSymbol;
			node = mHeap.top();
		}
	}
	return outStr;
}