#include <string>
#include <iostream>

#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key )
{
  this->setKey(key);
}

void PlayfairCipher::setKey( const std::string& key )
{
  key_ = key;
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  if (cipherMode == CipherMode::Encrypt) {
    std::cout << "applyCipher called" << std::endl;
  }
  return inputText;
}
