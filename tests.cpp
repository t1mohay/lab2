#include <gtest/gtest.h>
#include "ip_utils.h"

TEST(ParseIp, ValidAddress) {
    std::string a = "192.168.1.1";
    auto res = parse_ip(a);
    IpAddress expected{192, 168, 1, 1};
    EXPECT_EQ(res, expected);
}

TEST(ParseIp, RejectsIncompleteAddress) {
    std::string a = "192.168.1";
    EXPECT_THROW(parse_ip(a), std::invalid_argument);
}

TEST(ReadIps, IgnoresExtraColumns){
    std::istringstream input(
    "192.168.1.1\t10\t20\n"
    "1.2.3.4\t30\t40\n"
);
    auto res = read_ips(input);
    std::vector<IpAddress> expected {
        {192, 168, 1, 1},
        {1, 2, 3, 4}
    };
    EXPECT_EQ(res, expected);
}