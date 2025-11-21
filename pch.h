/**
 * @file pch.h
 * @brief Precompiled header for faster compilation
 */

#ifndef PCH_H
#define PCH_H

// Standard library headers (most commonly used)
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <array>
#include <memory>
#include <functional>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <optional>
#include <variant>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cmath>

// SIMD intrinsics
#ifdef __AVX512F__
#include <immintrin.h>
#endif

#ifdef __AVX2__
#include <immintrin.h>
#endif

#ifdef __AES__
#include <wmmintrin.h>
#endif

// Common project headers
#include "core/CPUFeatures.h"

#endif // PCH_H
