#include <ATRC.h>
#include "./atrc_fd.hpp"
#include "./msg.hpp"
#include "./grachi.hpp"
#include <filesystem>
#include <string>

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

std::unique_ptr<ATRCFiledata> reader(const std::string& filename) {
    std::string full_path = atrc_path + filename;

    if (!fs::exists(atrc_path)) {
        m_nrm("Data file doesn't exist. " + atrc_path, DATA_FILE_ERROR, FL_ATRC_FD, true);
    }

    std::unique_ptr<ATRCFiledata> temp = Read(full_path, "utf-8");
    if (!temp) {
        m_nrm("Failed to read data file. " + atrc_path, DATA_FILE_ERROR, FL_ATRC_FD, true);
        return nullptr;
    }

    return temp;
}

std::unique_ptr<ATRCFiledata> fd_su25 = nullptr;

void initialize_asset_data(){
    fd_su25 = reader("planes\\su25.atrc");
}