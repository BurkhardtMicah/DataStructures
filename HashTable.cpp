#include <iostream>
#include <cstddef>

//const int TABLE_SIZE = 17;
//int TABLE_SIZE;


class HashEntry
{
	private:
		int key;
		int value;
		
		
	public:
		HashEntry(int key, int value)
		{
			this->key = key;
			this->value = value;
		}
		
		int getKey()
		{
			return key;
		}
		
		int getValue()
		{
			return value;
		}
};

class HashMap 
{
private:
    HashEntry **table;
	int tableSize;
public:

//Constructor
    HashMap(int tableSize) 
	{
		this->tableSize = tableSize;
		
        table = new HashEntry*[tableSize]; //allocates an array of pointers to HashEntry objects
        for (int i = 0; i < tableSize; i++)
            table[i] = NULL;
    }

//Get Value stored at a key
    int get(int key) 
	{
        int hash = (key % tableSize);
        while (table[hash] != NULL && table[hash]->getKey() != key)
            hash = (hash + 1) % tableSize;
            
        if (table[hash] == NULL)//If empty
            return -1;
        else
            return table[hash]->getValue();
		//std::cout<<"\nValue = "<<key<<std::endl;
		//std::cout<<"Get: Hash Value = "<<hash<<std::endl;            
    }

//Insert a new value 
    void insert(int key, int value)
    {
		int hashvalue = (key % tableSize);

		int i = 0;
		while (table[hashvalue] != NULL && i < tableSize &&  table[hashvalue]->getKey() != key )
		{
			hashvalue = (hashvalue + 1) % tableSize;
			i++;
		}
		
		if(i < tableSize)
		{
			table[hashvalue] = new HashEntry(key, value);
			
			std::cout<<"\nValue = "<<value<<std::endl;
			std::cout<<"Hash Value = "<<hashvalue<<std::endl;
		}
    }
    
    int getSize()
    {
    	return tableSize;
	}

	void rehash(HashMap &newTable)
	{
        for (int i = 0; i < tableSize; i++)//i = 0-16 0-6
        {
            if(table[i] != NULL)
			{
				newTable.insert(i, table[i]->getValue());
			}//else cell is empty
			else
			{}
		}
	}

//Destructor
    ~HashMap() 
	{
        for (int i = 0; i < tableSize; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
};

//HashMap *rehash(HashMap&);

int main(void)
{
	//TABLE_SIZE = 17;
	//Values for table
	int iArr[12] = {121,81,16,100,25,0,1,9,4,36,64,49};
	
	
	HashMap *H1 = NULL;
	H1 = new HashMap(17);
	std::cout<<"HashMap H1 created with size of 17"<<std::endl; //Table Size is a universal constant
	
	int i;
	for(i=0; i<12; i++)
	{
		H1->insert(i, iArr[i]);
	}
	
	//Rehash
	std::cout<<"HashMap H2 created with size of 7"<<std::endl;	
	HashMap *H2 = NULL;
	H2 = new HashMap(7);
	
	H1->rehash(*H2);
	
	std::cout<<"\n\nFinal Print"<<std::endl;
	for(i=0; i<7; i++)
	{
		std::cout<<"\nValue = "<<H2->get(i)<<std::endl;
		std::cout<<"Hash Value = "<<i<<std::endl;
	}
		
	return 0;
}
