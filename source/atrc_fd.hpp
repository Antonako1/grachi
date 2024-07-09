#ifndef ATRC_FD_H
#define ATRC_FD_H
#include <ATRC.h>
#include <memory>

extern std::unique_ptr<ATRCFiledata> fd_su25;

void initialize_asset_data();

std::string read_key_as_string(ATRCFiledata *fd, const std::string block, const std::string key);
void read_key_to_string(ATRCFiledata *fd, const std::string block, const std::string key, std::string input);

std::string read_var_as_string(ATRCFiledata *fd, const std::string var_name);
void read_var_to_string(ATRCFiledata *fd, const std::string var_name, std::string input);

void change_key_value(ATRCFiledata *fd, const std::string block, const std::string key, const std::string new_value);
void change_var_value(ATRCFiledata *fd, const std::string var_name, const std::string new_value);

#endif // ATRC_FD_H