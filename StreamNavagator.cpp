#include "StreamNavagator.h"

StreamNavigator::StreamNavigator(const char *search_word, const char *fname) : srch_word(search_word), bf(fname), getting_from(BufFile), matches(0), starting_pos(0) {}

void StreamNavigator::put(const char &ch)
{
    if (getting_from == SearchString)
    {
        starting_pos++;
    }
    bf.put(ch);
}

bool StreamNavigator::eof() const
{
    return bf.eof();
}

StreamNavigator &StreamNavigator::get(char &ch)
{
    if (getting_from == SearchString)
    {
        ch = srch_word[matches - matchesLeft--];
        if (matchesLeft == 0)
            getting_from = BufFile;
    }
    else
        bf.get(ch);
    return *this;
}

void StreamNavigator::found_partial_match(int count, char mismatched_ch)
{
    if (getting_from == SearchString)
    {
        starting_pos++;
    }else{
        bf.putback(mismatched_ch);
        matches = count;
        starting_pos = 0;
    }
    matchesLeft = matches - starting_pos- 1;
    if (matchesLeft > 0)
        getting_from = SearchString;
    bf.put(srch_word[starting_pos]);
}