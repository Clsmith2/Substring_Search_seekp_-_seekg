#include <string>
#include <iostream>
#include "StreamNavagator.h"

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: stringsub searchstring replacestring filename" << std::endl;
    return 1;
  }
  std::string search_word = argv[1];
  std::string replace_word = argv[2];
  std::string filename = argv[3];

  StreamNavigator sn(argv[1], argv[3]);

  unsigned int match_count = 0;
  char ch;
  while (!sn.get(ch).eof())
  {
    if (ch == search_word[match_count])
    {
      ++match_count;
      if (match_count < search_word.length())
      {
        continue;
      }
    }
    if (match_count == search_word.length())
    {
      for (int i = 0; i < replace_word.length(); i++)
      {
        sn.put(replace_word[i]);
      }
      match_count = 0;
    }
    else if (match_count > 0)
    { // partial match
      sn.found_partial_match(match_count, ch);
      match_count = 0;
    } // set a couple flags & push_front(ch)
    else
    {
      sn.put(ch);
    }
  }
}