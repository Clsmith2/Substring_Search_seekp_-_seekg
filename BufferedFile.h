#ifndef BUFFEREDFILE_H
#define BUFFEREDFILE_H
#include<string>
#include<ios>
#include<fstream>
#include"GradingDeque.h"
#include "FStream.h"
class BufferedFile : private FStream {
  public:
    BufferedFile(const char* fname);
    BufferedFile& get(char& c);
    ~BufferedFile();
    std::ostream& put (char c);
    bool eof() const;
    void putback(char ch);
  private:
    std::istream& get_from_file(char& c);
    const char* filename;
    std::streampos getpos;
    std::streampos putpos;
    GradingDeque buffer;
    bool hit_file_eof;
    bool eof_and_empty_buffer;
};
#endif