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
  
  // Store the coords of each letter
  
  // Store the playfair cihper key map
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  if (cipherMode == CipherMode::Encrypt) {
    std::cout << "key_ is " << key_ << std::endl;
  }
  // Change J → I
  
  // If repeated chars in a digraph add an X or Q if XX
  
  // if the size of input is odd, add a trailing Z
  
  // Loop over the input in Digraphs
  
  // - Find the coords in the grid for each digraph
  // - Apply the rules to these coords to get 'new' coords
  // - Find the letter associated with the new coords
  // return the text
  return inputText;
}
