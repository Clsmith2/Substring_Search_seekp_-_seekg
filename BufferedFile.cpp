#include "BufferedFile.h"
#include<filesystem>
#include<sys/types.h>
#include<cassert>

BufferedFile::BufferedFile(const char* fname)
  : FStream(fname), filename(fname), getpos(0), putpos(0), hit_file_eof(false), eof_and_empty_buffer(false)
{
  assert(std::fstream::good());
}

std::istream& BufferedFile::get_from_file(char& c)
{
  if(hit_file_eof)
    return *this;
  FStream::seekg(getpos);
  getpos=FStream::get(c).tellg();
  if(FStream::eof())
  {
    FStream::clear();
    hit_file_eof=true;
  }
  return *this;
}

BufferedFile& BufferedFile::get (char& c)
{
  if(buffer.size()>0)
  {
    c=buffer.front();
    buffer.pop_front();
    return *this;
  }
  get_from_file(c);
  if(hit_file_eof)
    eof_and_empty_buffer=true;
  return *this;
}

std::ostream& BufferedFile::put (char c)
{
  if(getpos==putpos && !hit_file_eof)
  {
    char ch='#';
    get_from_file(ch);
    if(!hit_file_eof)
      buffer.push_back(ch);
  }
  FStream::seekp(putpos);
  putpos=FStream::put(c).tellp();
  return *this;
}

void BufferedFile::putback(char ch)
{
  buffer.push_front(ch);
}

bool BufferedFile::eof() const
{
  return eof_and_empty_buffer;
}

BufferedFile::~BufferedFile()
{
  assert(buffer.size()==0);
  FStream::close();
  std::filesystem::resize_file(filename, putpos);
}