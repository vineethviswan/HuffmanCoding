#pragma once

#include <queue>
#include <vector>
#include <memory>
#include <string>
#include <map>

struct Node {
	char mSymbol;
	int mFrequency;
	Node *pLeft;
	Node *pRight;
};

struct Comparator {
	bool operator()(Node *lhs, Node *rhs) {
		return lhs->mFrequency > rhs->mFrequency;
	}
};

class HFCompressor {
public:
	HFCompressor();
	~HFCompressor();
	
	void loadFrequencyTable(const std::vector<std::pair<char, int>> *input);
	std::map<char, std::string>* generateHFCode();
	std::string encode(const std::string &inStr);
	std::string decode(const std::string &inStr);
	//void printHeap();
	
private:
	Node* makeNode(std::pair<int, char>);
	void  getHFCodeHelper(Node *, std::string);
	void addToHeap();
	void buildHFTree();

	std::priority_queue<Node*, std::deque<Node*>, Comparator> mHeap;
	std::vector<std::pair<char, int>> *mFreqTable;
	std::map<char, std::string> *mHfTable;
};
