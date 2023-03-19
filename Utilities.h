#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "settings.h"
#include "TokenType.h"
// #include "KeyWord.h"


#if DEBUG
#define LOG(x) std::cout << x << '\n'
#define DEBUG_LOG(x) std::cout << #x << ": " << x << '\n'
#else
#define LOG(x) 
#define DEBUG_LOG(x) 
#endif

namespace CulLang {

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;

using Str = std::string;

template <typename K, typename V>
using Dict = std::unordered_map<K, V>;

using DataType = TokenType;
using Operator = TokenType;
template <typename T, size_t Size>
bool checkInArray(T val, const std::array<T, Size>& vec) {
  for (const auto& i : vec) {
    if (i == val) {
      return true;
    }
  }
  return false;
}
}

#include "Position.h"
  // namespace CulLang
