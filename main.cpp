#include "ip_utils.h"

int main() {
     constexpr IpAddress target_ip = generate_target_ip(12345);

    auto ips = read_ips(std::cin);
    sort_ips_reverse(ips);
    std::cout << "IP list: \n";
    for (const auto& ip : ips) {
        print_ip(ip);
    }
    print_filtered(ips, [](const auto& ip) { return std::get<0>(ip) == 1; });
    print_filtered(ips, [](const auto& ip) { return (std::get<0>(ip) == 46 and std::get<1>(ip) == 70 ); });
    print_filtered(ips, [](const auto& ip) { return (std::get<0>(ip) == 46 or std::get<1>(ip) == 46 or std::get<2>(ip) == 46 or std::get<3>(ip) == 46); });
    std::cout << '\n';

    std::cout << "Target IP: ";
    print_ip(target_ip);
    std::cout << '\n';

    auto it = std::find(ips.begin(), ips.end(), target_ip);

    if (it==ips.end()) {
        std::cout << "Target IP not found\n";
    }
    else {
        std::cout << "Target IP found\n";
    }

    return 0;
}