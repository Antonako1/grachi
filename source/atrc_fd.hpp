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

// do npos check yourself
double str_to_double(const std::string& str);

// Lists seperated by ;
// Example: pylon_contents=AA;B;R;
std::vector<std::string> atrc_value_to_list(const std::string &value);

// Points automatically to \\assets\\data\\. Just send the path from that point onwards...
std::unique_ptr<ATRCFiledata> reader(const std::string& filename);

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

std::string str_to_lower(const std::string &str);

// trims the str inside the function
bool str_to_bool(const std::string &str);

#endif // ATRC_FD_H