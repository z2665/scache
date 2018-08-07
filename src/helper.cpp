#include "helper.h"
namespace Helper
{
std::vector<std::string> SplitString(std::string_view s, std::string_view c)
{
    std::vector<std::string> v
        std::string::size_type pos1,
        pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
    {
        v.push_back(s.substr(pos1));
    }
    return v;
}
} // namespace Helper