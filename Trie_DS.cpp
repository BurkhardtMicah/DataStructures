#include <iostream>
#include <cstddef>
#include <fstream>

//Size of alphabet
const int SIZE_ALPHA = 127;

class Trie
{
	private:
		Trie* childNodes[SIZE_ALPHA]; //array of pointers to child nodes
		bool wordEnd;
		
		void reccomendationSearch(std::string);
		void search(std::string);
		
	public:
		//Constructor
		Trie()
		{
			this->wordEnd = false;
			
			for(int i=0; i<SIZE_ALPHA; i++)
			{
				this->childNodes[i] = NULL;	
			}	
		}
		
		void insert(std::string);
		bool BasicSearch(std::string);
		int suggest(std::string);
};

void Trie::insert(std::string word)
{
	Trie *curNode = this;
	
	for(int i=0; i < word.length(); i++)
	{
		int indx = word[i];
		if(curNode->childNodes[indx] == NULL) //If node does not exist
		{
			curNode->childNodes[indx] = new Trie(); //Create new trie node
		}
		
		//move to next node
		curNode = curNode->childNodes[indx];
	}
	curNode->wordEnd = true;
}

bool Trie::BasicSearch(std::string item)
{
	Trie *curNode = this;
	
	for(int i=0; i<item.length(); i++)
	{
		int indx = item[i]; 
		
		if(curNode->childNodes[indx] == NULL)
		{
			return false; //not found
		}//If next letter does not exist
		else if(curNode->childNodes[indx] != NULL)
		{
			curNode = curNode->childNodes[indx]; //move to child node
		}//if next letter does exist
		//Else fall through
	}
	
	if(curNode->wordEnd)
	{
		return true;
	}//check if finalNode element it is end of a word
	else
	{
		return false;
	}
}

void Trie::search(std::string part_String)
{
	Trie *curNode = this;
	bool finalNode = true;

	if(curNode->wordEnd == true)//If a end of word is encountered, print suggestion
	{
		std::cout<<part_String<<std::endl;
	}
	
	for(int i=0; i<SIZE_ALPHA; i++)
	{
		if(curNode->childNodes[i] != NULL)//if any childNodes exist
		{
			finalNode = false;
			break;
		}
	}
	if(finalNode)//if it is the finalNode node
	{
		return;
	}
	
	for(int i=0; i<SIZE_ALPHA; i++)
	{
		std::string temp = part_String;
		if(curNode->childNodes[i])
		{
			part_String.push_back(i);
			
			curNode->childNodes[i]->search(part_String);
		}
		part_String = temp;
	}
}

int Trie::suggest(std::string word)
{
	Trie *curNode = this;
	
	for(int wrd_indx=0; wrd_indx<word.length(); wrd_indx++)
	{
		int indx = word[wrd_indx];
		
		if(curNode->childNodes[indx] == NULL)//if word is not found
		{
			std::cout<<"\nDo You Mean:"<<std::endl;
			this->reccomendationSearch(word);
			return 0;
		}
		
		curNode = curNode->childNodes[indx];
	}

	bool finalNode = true;
	for(int i=0; i<SIZE_ALPHA; i++)
	{
		if(curNode->childNodes[i] != NULL)//if any childNodes exist
		{
			finalNode = false;
			break;
		}
	}	
	
	if((curNode->wordEnd == true) && finalNode)
	{
		std::cout<<word<<std::endl;
		return -1;
	}
	
	if(finalNode == false)
	{
		curNode->search(word);
		return 1;
	}
}



void Trie::reccomendationSearch(std::string item)
{
	Trie *curNode = this;
	std::string suggestion;
	
	for(int i=0; i<item.length(); i++)
	{
		int indx = item[i];	
		if(curNode->childNodes[indx] != NULL)
		{
			suggestion.push_back(indx);
			curNode = curNode->childNodes[indx];
		}
		else //current node does not exist
		{	
			this->suggest(suggestion);
			return;
		}
	}	
}

int main(void)
{
	//driver for Trie creation
	Trie *T1 = new Trie();
	std::cout<<"Created T1\n"<<std::endl;
	
	//Read from dictionary
	std::string line;
	
	std::ifstream dictionary("dictionary.txt");
	
	if(dictionary.is_open())
	{
		while(std::getline(dictionary,line))
		{
			T1->insert(line);
		}
	}
	else
	{
		std::cout<<"Dictionary failed to open"<<std::endl;
		return -1;
	}
	//Close file
	dictionary.close();
	
	std::string search;
	std::cout<<"Enter search word: ";
	std::cin>>search;

	T1->suggest(search);
	
	return 0;
}
