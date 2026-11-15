#include <iostream>   
#include <string>    
#include <vector>     
#include <tuple>      
#include <algorithm>  
#include <sstream>    
#include <cstdint>
#include <clocale>
#include <stdexcept>
#pragma once

using IpAddress = std::tuple<int, int, int, int>;

IpAddress parse_ip(const std::string& text) {
    std::istringstream stream(text);
    std::string part;
    std::vector<int> octets;

    while (std::getline(stream, part, '.')) {
        octets.push_back(std::stoi(part));
    }
    if (octets.size() != 4) {
        throw std::invalid_argument("bad ip: " + text);
    }

    return {octets[0],octets[1],octets[2],octets[3]};
}


std::vector<IpAddress> read_ips(std::istream& in) {
    std::vector<IpAddress> ips;
    std::string line;

    while (std::getline(in, line)){
        auto tab = line.find('\t');
        ips.push_back(parse_ip(line.substr(0, tab)));
    }
    return ips;
}

void sort_ips_reverse(std::vector<IpAddress>& ips) {
    std::sort(ips.begin(), ips.end(),
              [](const auto& a, const auto& b){
                return a>b;
              });
}

void print_ip(const IpAddress& ip) {
    std::cout << std::get<0>(ip) << '.'
              << std::get<1>(ip)<< '.'
              << std::get<2>(ip)<<'.'
              << std::get<3>(ip)<< '\n';
}

consteval IpAddress generate_target_ip(std::uint32_t value) {
    for (int i = 0; i < 10000; ++i) {
        value ^= value << 13;
        value ^= value >> 17;
        value *= 0x45D9F3B;
        value ^= value >> 16;
    }
    int A = (value >> 24) & 255;
    int B = (value >> 16) & 255;
    int C = (value >> 8) & 255;
    int D = value & 255;

    return {A,B,C,D};
}

template <typename Predicate>
void print_filtered(const std::vector<IpAddress>& ips, Predicate pred) {
    for (const auto& ip : ips) {
        if (pred(ip)) {
            print_ip(ip);
        }
    }
}