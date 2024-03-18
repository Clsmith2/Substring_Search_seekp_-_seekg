#include "BufferedFile.h"

class StreamNavigator {
  public:
    StreamNavigator(const char* search_word, const char* fname);
    void put(const char& ch); //simply call bf.put
    bool eof() const; //simply return/call bf.eof
    StreamNavigator& get(char& ch);
    void found_partial_match(int count, char mismatched_ch);
  private:
    BufferedFile bf;
    const char* srch_word; //or similar
    enum { BufFile, SearchString } getting_from;
    int matches;
    int starting_pos;
    int matchesLeft;
};