#include <ATRC.h>
#include "./atrc_fd.hpp"
#include "./msg.hpp"
#include "./grachi.hpp"
#include <filesystem>
#include <string>
// #include <Windows.h>
#include <sfml/System/String.hpp>

namespace fs = std::filesystem;

void read_key_to_string(ATRCFiledata *fd, const std::string block, const std::string key, std::string input){
    std::string output = "";
    ReadKey(fd, block, key, output);
    if(output == "" ){
        if(!DoesExistKey(fd, block, key)){
            m_nrm("Block: ["+block+"] Key:'"+key+"' does not exist in file " + fd->Filename, DATA_VALUE_ERROR, FL_ATRC_FD, true);
        }
    }
    input += output;
};
std::string read_key_as_string(ATRCFiledata *fd, const std::string block, const std::string key){
    std::string output = "";
    ReadKey(fd, block, key, output);
    if(output == "" ){
        if(!DoesExistKey(fd, block, key)){
            m_nrm("Block: ["+block+"] Key:'"+key+"' does not exist in file " + fd->Filename, DATA_VALUE_ERROR, FL_ATRC_FD, true);
        }
    }
    return output;
};

void read_var_to_string(ATRCFiledata *fd, const std::string var_name, std::string input){
    std::string output = "";
    ReadVariable(fd, var_name, output);
    if(output == "" ){
        if(!DoesExistVariable(fd, var_name)){
            m_nrm("Variable:'"+var_name+"' does not exist in file " + fd->Filename, DATA_VALUE_ERROR, FL_ATRC_FD, true);
        }
    }
    input += output;
};

std::string read_var_as_string(ATRCFiledata *fd, const std::string var_name){
    std::string output = "";
    ReadVariable(fd, var_name, output);
    if(output == "" ){
        if(!DoesExistVariable(fd, var_name)){
            m_nrm("Variable:'"+var_name+"' does not exist in file " + fd->Filename, DATA_VALUE_ERROR, FL_ATRC_FD, true);
        }
    }
    return output;
};
#include <iostream>
size_t str_to_size_t(const std::string& str){
    size_t res;
    try {
        res = std::stoi(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        m_nrm("Error converting '" + str + "' to size_t", CAST_CONVERSION_ERROR, FL_ATRC_FD, true);
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        m_nrm("Error converting '" + str + "' to size_t", CAST_CONVERSION_ERROR, FL_ATRC_FD, true);
    }
    return res;
}
double str_to_double(const std::string& str){
    double res;
    size_t pos;
    try {
        res = std::stod(str, &pos);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        m_nrm("Error converting '" + str + "' to double", CAST_CONVERSION_ERROR, FL_ATRC_FD, true);
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        m_nrm("Error converting '" + str + "' to double", CAST_CONVERSION_ERROR, FL_ATRC_FD, true);
    }
    if(pos != str.length()){
        m_nrm("Error converting '" + str + "' to double", CAST_CONVERSION_ERROR, FL_ATRC_FD, true);
    }
    return res;
}

std::wstring utf8_decode(const std::string &str){
    return sf::String::fromUtf8(str.begin(), str.end());
}

std::string str_to_lower(const std::string &str){
    std::string res=str;
    for(char &c : res){
        std::tolower(c);
    }
    return res;
}

bool str_to_bool(const std::string &str){
    std::string temp=str_to_lower(str);
    trim(temp);
    if(temp == "true") {
        return true;
    } else if(temp == "false"){
        return false;
    } else {
        m_nrm("Error converting string to a boolean. Input: '" + str+"' Output: '" +temp+"'", CAST_CONVERSION_ERROR, FL_ATRC_FD, true);
        return false;
    }
}

void change_key_value(ATRCFiledata *fd, const std::string block, const std::string key, const std::string new_value){
    if(!DoesExistKey(fd, block, key)){
        m_nrm("Block: ["+block+"] Key:'"+key+"' does not exist in file " + fd->Filename, DATA_VALUE_ERROR, FL_ATRC_FD, true);
    }
    ModifyKey(fd, block, key, new_value);
}

void change_var_value(ATRCFiledata *fd, const std::string var_name, const std::string new_value){
    if(!DoesExistVariable(fd, var_name)){
        m_nrm("Variable:'"+var_name+"' does not exist in file " + fd->Filename, DATA_VALUE_ERROR, FL_ATRC_FD, true);
    }
    ModifyVariable(fd, var_name, new_value);
}

std::vector<std::string> atrc_value_to_list(const std::string &value){
    std::vector<std::string> res;
    if(value.size() == 0){
        return res;
    }
    std::string temp_value = value;
    if(temp_value.at(temp_value.size()-1) != ';'){
        temp_value += ";";
    }
    std::string buf = "";
    for(const char &c : temp_value){
        if(c == ';'){
            res.push_back(buf);
            buf = "";
            continue;
        }
        buf += c;
    }
    return res;
}
std::unique_ptr<ATRCFiledata> reader(const std::string& filename) {
    std::string full_path = atrc_path + filename;
    if (!fs::exists(atrc_path)) {
        m_nrm("Data file doesn't exist: " + atrc_path, DATA_FILE_ERROR, FL_ATRC_FD, true);
    }

    std::unique_ptr<ATRCFiledata> temp = Read(full_path, "utf-8");
    if (!temp) {
        m_nrm("Failed to read data file. " + atrc_path, DATA_FILE_ERROR, FL_ATRC_FD, true);
        return nullptr;
    }

    return temp;
}