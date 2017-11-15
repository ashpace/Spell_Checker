//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	small_dictionary.cpp
// ID1222781
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "small_dictionary.h"
#include "utility.h"

#include <string>
#include <vector>
#include <algorithm>

long DLdistance (std::string A , std::string B);

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	dict::Dictionary200 () 
//  returns a vector of first initial 200 words
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::vector<std::string> dct::Dictionary200 ()
{
	std::vector<std::string> Dict
	({
	    "the", "be", "of", "and", "a", "to", "in", "he", "have", "it", "that",  
	    "for", "they", "I", "with", "as", "not", "on", "she", "at", "by", "this", 
	    "we", "you", "do", "but", "from", "or", "which", "one", "would", "all", 
	    "will", "there", "say", "who", "make", "when", "can", "more", "if", 
	    "no", "man", "out", "other", "so", "what", "time", "up", "go", "about", 
	    "than", "into", "could", "state", "only", "new", "year", "some", "take", 
	    "come", "these", "know", "see", "use", "get", "like", "then", "first", 
	    "any", "work", "now", "may", "such", "give", "over", "think", "most", 
	    "even", "find", "day", "also", "after", "way", "many", "must", "look", 
	    "before", "great", "back", "through", "long", "where", "much", "should", 
	    "well", "people", "down", "own", "just", "because", "good", "each", 
	    "those", "feel", "seem", "how", "high", "too", "place", "little", 
	    "world", "very", "still", "nation", "hand", "old", "life", "tell", 
	    "write", "become", "here", "show", "house", "both", "between", "need", 
	    "mean", "call", "develop", "under", "last", "right", "move", "thing", 
	    "general", "school", "never", "same", "another", "begin", "while", 
	    "number", "part", "turn", "real", "leave", "might", "want", "point", 
	    "form", "off", "child", "few", "small", "since", "against", "ask", 
	    "late", "home", "interest", "large", "person", "end", "open", "public", 
	    "follow", "during", "present", "without", "again", "hold", "govern", 
	    "around", "possible", "head", "consider", "word", "programme", 
	    "problem", "however", "lead", "system", "set", "order", "eye", "plan", 
	    "run", "keep", "face", "fact", "group", "play", "stand", "increase", 
	    "early", "course", "change", "help", "line"
	}); 
	//The vector comes from the assessment given file. 
	
	return Dict;
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	dict::existance ()
//  true if the input exists in the dictionary and false if it doesn't
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool dct::existance (std::vector<std::string>  & Dict , std::string & input)
{
	std::vector<std::string>::iterator it;
	it = find (Dict.begin(), Dict.end(), input); //find the location of the 
												 //input in the dictionary
	if (it != Dict.end()) return true; // if the pointer points at the end of 
									   // the vector, input was not found
	else return false;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	disct::suggestions
//  give suggestive words from the dictionary
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::vector<std::string> dct::suggestions (std::vector<std::string> & Dict , std::string & input)
{
	std::vector<std::string> suggestions;
	
	long DicSize = Dict.size(); 
	for (long i = 0 ; i != DicSize ; ++i)
	{
		long Distance = DLdistance (input , Dict[i] );
		if (Distance < input.size()*0.51) suggestions.push_back(Dict[i]);
		// The suggestion holds the words with distance smaller than 51% of the input size. 
		// The logic is: the bigger the word, the more mistakes can be made, the bigger the 
		// distance is to the real word. 51% was chosen to cover two letter words. 
		// anything less than 51% does not cover two letter words
	}
	return suggestions;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	DLdistance()
//  Find the distance between two strings
//  local function to the script
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
long DLdistance (std::string A , std::string B)
{
	long lal = A.size();       //number of characters in A
    long lbl = B.size();	   //number of characters in B
    
    
    A.insert(0," ");
    B.insert(0," ");
    //inserting null characters. It helps to point at the right character when
    //pointing at the character number. 
    
    std::vector< std::vector<long> > d_j_i; //the distance matrix 
    
    
    std::vector<long> temp; //temporary vector defined local to the function
    
    for (long i = 0; i != lal+1 ; ++i) 
    {
    	temp.push_back(i);
	}
	d_j_i.push_back(temp); //filling the first row the matrix
	temp.clear();		   //releasing the memory for temp
	

    
    for (long j = 1; j != lbl+1 ; ++j ) //filling the matrix row by row
    {
    	
		temp.push_back(j); // The first colume of the matrix is the 1,2,3,...
		
    	for (long i = 1; i != lal+1; ++i)
    	{
    		long option1 = temp[i-1]+1;
    		long option2 = d_j_i[j-1][i]+1;
    		long option3 = d_j_i[j-1][i-1];
    		if (A[i] != B[j]) ++option3;
    		
    		long the_minimum; // The minimum will be allocated to the minimum option
			
    		if (i > 1 and j > 1 and A[i] == B[j-1] and A[i-1] == B[j])
    		{
    			long option4 = d_j_i[j-2][i-2]+1;  // Under this condition, and onother option exists 
    			if (option1 < option2 and option1 < option3 and option1 < option4) the_minimum = option1;
    			if (option2 < option1 and option2 < option3 and option2 < option4) the_minimum = option2;
    			if (option3 < option1 and option3 < option2 and option3 < option4) the_minimum = option3;
    			else the_minimum = option4;
			}
    		
    		if (i == 1 or j == 1 or A[i] != B[j-1] or A[i-1] != B[j])
    		{
    			if (option1 < option2 and option1 < option3) the_minimum = option1;
    			if (option2 < option1 and option2 < option3) the_minimum = option2;
    			else the_minimum = option3;
			}
			
			temp.push_back(the_minimum); // The minimum is found and the next element of row is added to the temp
		}
		
		d_j_i.push_back(temp); //The newly created row saved in the temp, is now pushed back to the matrix.
		
		temp.clear(); //Temporary file is cleared and memory is released.
		
	}
    return d_j_i[lbl][lal]; // The distance is defined as the final element of the matrix. 
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


