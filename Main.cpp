//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	main.cpp
// ID1222781
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#include <iostream>
#include <string>
#include <algorithm>
#include "small_dictionary.h"
#include "utility.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main () 
{
	std::vector<std::string> Dict = dct::Dictionary200 ();
	// creating the dictionary vector. 
	bool run = true;  // while run is true the following while loop, loops.

	while(run)
	{
		ut::Printline(); //print a line to distinguish new word's journey
		std::string input = ut::GetString("Please enter your word ");
		//Ask the user for the input
		
		if (dct::existance( Dict , input )) std::cout << 
        "The word is found in the dictionary" << std::endl;

		else
		{ 
			std::cout << "** The entered word could not be found in the dictionary ** \n";
			
			std::vector<std::string> suggestions = dct::suggestions ( Dict , input );
			//creating suggestions from the dictionary. 
			long SugSize = suggestions.size();
			//find the size to see if there is any suggestions at all
			
			bool correction = false; // true when the user has chosen a correction
			
			if (SugSize > 0) // if there was any suggestion
			{
				std::cout << "The suggested word(s) are/is: \n";
				
				for (long i = 0 ; i != SugSize ; ++i)
				std::cout << "                             "<<
				i+1 << "-" << suggestions[i] << std::endl; 
				//print the suggestions
				
				std::cout << "If you meant any of the suggestions enter the suggestion number" 
				<< std::endl << " otherwise press any integer to proceed " << std::endl;
				
				long choice = ut::GetLong ("Enter your choice");
				
				if (choice <= SugSize)
				{
					correction = true;
					std::cout << "The correct word is now : <" << suggestions[choice-1] << ">\n";
				}
					
				else correction = false;
			}
			
			while (correction != true) //if the user did not use the sugestions loop starts. 
										// This loops until the user enters a valid input. 
			{
				std::string add = "add" , ignore = "ignore";
				std::cout << "Enter: \n" ;
				std::cout << "      -add :to add the word to the dictionary \n" ;
				std::cout << "      -ignore :to ignore the mistake" ;
				std::string choice = ut::GetString("your choice ");
				
				if (choice == add)
				{
					Dict.push_back(input);
					std::cout << "The Word has been added to the dictionary \n" ;
					break;
				}
				if (choice == ignore) break; 
			}
			 
		}
		
		while (run) //this loops until a valid respond is captured 
		{
			std::string quit = "q" , fcontinue = "c";
			std::cout << "Enter: \n" ;
			std::cout << "      -q :to quit the program \n" ;
			std::cout << "      -c :to continue entering words" ;
			std::string choice = ut::GetString("your choice ");
			
			if (choice == quit) run = false;
			if (choice == fcontinue) break; 
		}
		
	}

    return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
