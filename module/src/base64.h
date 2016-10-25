// example
// const std::string s = "jikongzhongxin" ;
// std::string encoded = Base64::base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
// std::string decoded = Base64::base64_decode(encoded);
// printf("encoded:%s\n, decoded:%s\n",encoded.c_str(),decoded.c_str());

#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>
class Base64 {
public:
    static std::string base64_encode(unsigned char const* , unsigned int len);
    static std::string base64_decode(std::string const& s);
};
#endif


