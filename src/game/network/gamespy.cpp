/**
 * @file
 *
 * @author terrycain
 *
 * @brief Gamespy protocol.
 *
 * @copyright Thyme is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include <string>
#include <algorithm>

#include "gamespy.h"
#include <captainslog.h>

/**
 * Parses gamespy strings like \lc\1\challenge\DFDMXJLXJL\id\1\final\ and extracts keys from them
 * 
 * The key should start and end with a backslash, e.g. \challenge\
 * 
 * @param packet_data String to search
 * @param key key to search for
 * @param dest buffer to store the result in
 * @param len length of the dest buffer
 * @return 1 on successful extract, 0 otherwise.
 */
int GamespyProtocol::ValueForKey(const char* packet_data, const char* key, char* dest, int len) {
    captainslog_debug("====================================================== TERRY GamespyProtocol::ValueForKey('%s', '%s')", packet_data, key);

    std::string packet_data_str = std::string(packet_data);
    std::string key_str = std::string(key);

    size_t key_start_pos = packet_data_str.find(key_str);

    if (key_start_pos == std::string::npos) {
        return 0;
    }

    size_t start_of_result = key_start_pos + key_str.length();

    std::string result;

    // Find first \ after key (or none if its the end of the string)
    size_t next_backslash = packet_data_str.find("\\", start_of_result);
    if (next_backslash == std::string::npos) {
        result = packet_data_str.substr(start_of_result);
    } else {
        result = packet_data_str.substr(start_of_result, next_backslash - start_of_result);
    }

    result.copy(dest, len - 1);
    // copy doesnt add null termination
    size_t result_len = std::min(static_cast<size_t>(len-1), result.length());
    dest[result_len] = '\0';

    return 1;
}
