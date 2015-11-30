#ifndef FILE_CLI_HH
#define FILE_CLI_HH

#include <string>
#include <vector>

bool exists(const std::string& file_name);
std::string red(const std::string& string);

class FileCLI
{
public:
  FileCLI(int argc, char* argv[]);
  std::vector<std::string> in_files() const;
  std::string out_file() const;
private:
  int check_opts(int argn);
  void usage() const;
  std::vector<std::string> m_files;
  std::string m_output;
  const int m_nargs;
  std::string m_name;
  std::vector<std::string> m_args;
  bool m_overwrite;
};


#endif