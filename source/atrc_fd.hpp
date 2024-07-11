#ifndef ATRC_FD_H
#define ATRC_FD_H
#include <ATRC.h>


void initialize_asset_data();

std::string read_key_as_string(ATRCFiledata *fd, const std::string block, const std::string key);
void read_key_to_string(ATRCFiledata *fd, const std::string block, const std::string key, std::string input);

std::string read_var_as_string(ATRCFiledata *fd, const std::string var_name);
void read_var_to_string(ATRCFiledata *fd, const std::string var_name, std::string input);

void change_key_value(ATRCFiledata *fd, const std::string block, const std::string key, const std::string new_value);
void change_var_value(ATRCFiledata *fd, const std::string var_name, const std::string new_value);

// do npos check yourself
size_t str_to_size_t(const std::string& str);

// Lists seperated by ;
// Example: pylon_contents=AA;B;R;
// LIST MUST END IN ;
std::vector<std::string> atrc_value_to_list(const std::string &value);

// Points automatically to \\assets\\data\\. Just send the path from that point onwards...
std::unique_ptr<ATRCFiledata> reader(const std::string& filename);

#endif // ATRC_FD_H