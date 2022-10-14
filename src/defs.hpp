#pragma once

#include<string>
#include<memory>
#include<cstdint>
#include<mutex>
#include<vector>
#include<optional>
#include<unordered_map>
#include<sstream>
#include<iostream>
#include<random>


/* Aliases */
template<typename T>
using opt = std::optional<T>;
using str = std::string;
template<typename T>
using sptr = std::shared_ptr<T>;
template<typename T>
using uptr = std::unique_ptr<T>;
using i64 = int64_t;
template<typename T>
using vec = std::vector<T>;
using ID = str;  // Override to use a different type
template<typename T, typename U>
using umap = std::unordered_map<T,U>;
using RNG = std::mt19937_64;