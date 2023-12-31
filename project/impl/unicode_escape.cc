#include "../include/unicode_escape.hh"

std::unordered_map<char, int> hex_to_int {
    {'0', 0x00}, {'1', 0x01},
    {'2', 0x02}, {'3', 0x03},
    {'4', 0x04}, {'5', 0x05},
    {'6', 0x06}, {'7', 0x07},
    {'8', 0x08}, {'9', 0x09},
    {'A', 0x0A}, {'B', 0x0B},
    {'C', 0x0C}, {'D', 0x0D},
    {'E', 0x0E}, {'F', 0x0F},
    {'a', 0x0a}, {'b', 0x0b},
    {'c', 0x0c}, {'d', 0x0d},
    {'e', 0x0e}, {'f', 0x0f},
};

std::string escape_string(
    const std::string_view &str)
{
    std::string escaped = "";
    
    size_t size = str.length();

    for (size_t index = 0; index < size; index++)
    {
        if (str[index] == '\\')
        {
            index++;

            if (index > size)
            {
                throw StringEscapeError("cannot decode '\\' at end of string.");
            }

            switch (str[index])
            {
                case 'a': {
                    escaped += '\a';
                    break;
                }
                case 'b': {
                    escaped += '\b';
                    break;
                }
                case 'e': {
                    escaped += '\e';
                    break;
                }
                case 'f': {
                    escaped += '\f';
                    break;
                }
                case 'n': {
                    escaped += '\n';
                    break;
                }
                case 'r': {
                    escaped += '\r';
                    break;
                }
                case 't': {
                    escaped += '\t';
                    break;
                }
                case 'v': {
                    escaped += '\v';
                    break;
                }
                case '\\': {
                    escaped += '\\';
                    break;
                }
                case '\'': {
                    escaped += '\'';
                    break;
                }
                case '\"': {
                    escaped += '\"';
                    break;
                }
                case '?': {
                    escaped += '\?';
                    break;
                }
                case 'x': {
                    index += 2; // skip xh

                    if (index > size)
                    {
                        // use goto so no repetition, 
                        // but we have to check bounds
                        // first so no segfaults
                        goto decode_xerror;
                    }
                    
                    if (hex_to_int.find(str[index - 1]) == hex_to_int.end()) {
                      decode_xerror:
                        throw StringEscapeError(
                            "cannot decode string, truncated \\xXX escape.");
                    }

                    if (index == size) {
                        return escaped + static_cast<char>(hex_to_int[str[index - 1]]);
                    } else if (hex_to_int.find(str[index]) == hex_to_int.end()) {
                        index--;
                        escaped += hex_to_int[str[index]];
                        break;
                    }
                    
                    escaped += (hex_to_int[str[index - 1]] << 4)
                             + (hex_to_int[str[index]]);
                    break;
                }
                case 'u': {
                    index += 4; // skip uXXX

                    if (index > size)
                    {
                        // use goto so no repetition, 
                        // but we have to check bounds
                        // first so no segfaults
                        goto decode_uerror;
                    }

                    if (hex_to_int.find(str[index - 3]) == hex_to_int.end()
                     || hex_to_int.find(str[index - 2]) == hex_to_int.end()
                     || hex_to_int.find(str[index - 1]) == hex_to_int.end()
                     || hex_to_int.find(str[index]) == hex_to_int.end())
                    {
                      decode_uerror:
                        throw StringEscapeError("cannot decode string, truncated \\uXXXX escape.");
                    }

                    escaped += 0b11100000 + (hex_to_int[str[index - 3]]);

                    escaped += 0b10000000 + (hex_to_int[str[index - 2]] << 2)
                                          + (hex_to_int[str[index - 1]] >> 2);
                    escaped += 0b10000000 + ((hex_to_int[str[index - 1]] & 3) << 4)
                                          + (hex_to_int[str[index]]);
                    break;
                }
                // TODO: implement \U
                default: {
                    escaped += '\\' + str[index];
                    break;
                }
            }
            
        } else {
            escaped += str[index];
        }
    }

    return escaped;
}

std::string unescape_string(
    const std::string_view &str)
{
    std::string unescaped = "";

    size_t size = str.length();

    for (size_t index = 0; index < size; index++)
    {
        switch (str[index])
        {
            case '\a': {
                unescaped += "\\a";
                break;
            }
            case '\b': {
                unescaped += "\\b";
                break;
            }
            case '\e': {
                unescaped += "\\e";
                break;
            }
            case '\f': {
                unescaped += "\\f";
                break;
            }
            case '\n': {
                unescaped += "\\n";
                break;
            }
            case '\r': {
                unescaped += "\\r";
                break;
            }
            case '\t': {
                unescaped += "\\t";
                break;
            }
            case '\v': {
                unescaped += "\\v";
                break;
            }
            case '\'': {
                unescaped += "\\\'";
                break;
            }
            case '\"': {
                unescaped += "\\\"";
                break;
            }
            case '\?': {
                unescaped += "\\?";
                break;
            }
            case '\\': {
                unescaped += "\\\\";
                break;
            }
            default: {
                unescaped += str[index];
                break;
            }
        }
    }

    return unescaped;
}
