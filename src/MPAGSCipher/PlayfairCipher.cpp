#include <string>
#include <iostream>
#include <algorithm>

#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key )
{
  this->setKey(key);
}

void PlayfairCipher::setKey( const std::string& key )
{
  key_ = key;
  // Append the alphabet
  key_ += alphabet_;
  
  // Make sure the key is upper case
  std::transform(std::begin(key_), std::end(key_), std::begin(key_), ::toupper);
  // Remove non-alpha characters
  auto iter = std::remove_if(key_.begin(), key_.end(), [] (char x) {return !std::isalpha(x);});
  key_.erase(iter, key_.end());
  // Change J -> I
  std::transform(std::begin(key_), std::end(key_), std::begin(key_), [] (char x) {
								       if ( x == 'J') {return 'I';}
								       else {return x;}
								     } );
  // Remove duplicated letters
  std::string lettersEncountered {""};
  auto iter2 = std::remove_if(key_.begin(), key_.end(), [&] (char x) {
							  if (lettersEncountered.find(x) == std::string::npos )
							    {lettersEncountered += x;
							      return false;}
							  else {return true;}
							}
    );
    key_.erase(iter2, key_.end());
  
  // Store the coords of each letter
    for (std::string::size_type i{0}; i<25; ++i)
      {
	std::string::size_type columnNumber { i%5 };
	std::string::size_type rowNumber { i/5 };
	
	auto coords = std::make_pair(rowNumber, columnNumber);
	// Store the playfair cipher key map
	Coord2CharMap_[coords] = key_[i];
	Char2CoordMap_[key_[i]] = coords;
      }
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  std::string outputText = inputText;
  // Change J → I
  std::transform(std::begin(outputText), std::end(outputText), std::begin(outputText), [] (char x) {
								       if ( x == 'J') {return 'I';}
								       else {return x;}
								     } );
  // If repeated chars in a digraph add an X or Q if XX
  // myString ABCDE -> size=5 -> myString[4]=E=myString[size-1]
  std::string tempString {""};
  for (std::string::size_type i=0; i<outputText.size(); i+=2)
    {
      tempString+=(outputText[i]);
      if (i!=(outputText.size()-1))
	{
	  if (outputText[i+1] == outputText[i] && outputText[i] == 'X')
	    {
	      tempString+='Q';
	    }
	  else if (outputText[i+1] == outputText[i])
	    {
	      tempString+='X';
	    }
	  tempString+=(outputText[i+1]);
	}
      else
	{
	  break;
	}

    }
  outputText.swap(tempString);

  // if the size of input is odd, add a trailing Z
  if (outputText.size()%2 == 1)
    {
      outputText.push_back('Z');
    }
  // Loop over the input in Digraphs
  for (std::string::size_type i=0; i<outputText.size(); i+=2)
    {
      // - Find the coords in the grid for each digraph
      coordPair firstCoord {Char2CoordMap_.at(outputText[i])};
      coordPair secondCoord {Char2CoordMap_.at(outputText[i+1])};

      // - Apply the rules to these coords to get 'new' coords
      int shift {1};
      if (cipherMode == CipherMode::Decrypt)
	{shift = -1;}
      
      if (firstCoord.first == secondCoord.first)
	{
	  firstCoord.second = (firstCoord.second+5+shift)%5;
	  secondCoord.second = (secondCoord.second+5+shift)%5;
	}
      else if (firstCoord.second == secondCoord.second)
	{
	  firstCoord.first = (firstCoord.first+5+shift)%5;
	  secondCoord.first = (secondCoord.first+5+shift)%5;
	}
      else
	{
	  std::swap(firstCoord.second, secondCoord.second);
	}
      // - Find the letter associated with the new coords
      outputText[i] = Coord2CharMap_.at(firstCoord);
      outputText[i+1] = Coord2CharMap_.at(secondCoord);
    }
  
  // return the text
  return outputText;
}
