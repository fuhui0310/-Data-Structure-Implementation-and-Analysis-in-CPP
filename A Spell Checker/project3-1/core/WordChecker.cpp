// WordChecker.cpp
//
// ICS 46 Winter 2019
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <iostream>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector<std::string> suggestions;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //swapping
    for(int i = 0; i < word.size() - 1; i++){
    	std::string tmp = word;
    	tmp[i] = tmp[i+1];
    	tmp[i+1] = word[i];
    	if((std::find(suggestions.begin(), suggestions.end(), tmp) == suggestions.end())&&(wordExists(tmp))){
    		suggestions.push_back(tmp);
    	}
    }

    //inserting
    for(int i = 0; i < word.size(); i++){
    	for(int j = 0; j < letters.size(); j++){
    		std::string tmp = word;
    		tmp.insert(i, letters.substr(j, 1));
    		if((std::find(suggestions.begin(), suggestions.end(), tmp) == suggestions.end())&&(wordExists(tmp))){
    			suggestions.push_back(tmp);
    		}
    	}
    }

    //deleting
    for(int i = 0; i < word.size() - 1; i++){
    	std::string tmp = word;
    	tmp.erase(i,1);
    	if((std::find(suggestions.begin(), suggestions.end(), tmp) == suggestions.end())&&(wordExists(tmp))){
    		suggestions.push_back(tmp);
    	}
    }

    //replacing
    for(int i = 0; i < word.size(); i++){
    	for(int j = 0; j < letters.size(); j++){
    		std::string tmp = word;
    		tmp[i] = letters[j];
    		if((std::find(suggestions.begin(), suggestions.end(), tmp) == suggestions.end())&&(wordExists(tmp))){
    			suggestions.push_back(tmp);
    		}
    	}
    }

    //splitting
    for(int i = 1; i < word.size(); i++){
    	std::string tmp1 = word.substr(0,i);
    	std::string tmp2 = word.substr(i,word.size() - i);
    	std::string tmp3 = tmp1 + " " + tmp2;
    	if((std::find(suggestions.begin(), suggestions.end(), tmp3) == suggestions.end())&&(wordExists(tmp1))&&(wordExists(tmp2))){
    		suggestions.push_back(tmp3);
    	 }
    }
    return suggestions;
}

