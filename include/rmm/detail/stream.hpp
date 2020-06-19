/*
 * Copyright (c) 2020, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstddef>
#include <cstdint>

// forward decl
using cudaStream_t = struct CUstream_st*;

namespace rmm {

/**
 * @brief Strongly-typed wrapper for CUDA streams with default constructor.
 */
class stream_view {
 public:
  stream_view(stream_view const&) = default;
  stream_view(stream_view&&)      = default;
  stream_view& operator=(stream_view const&) = default;
  stream_view& operator=(stream_view&&) = default;

  // TODO disable construction from 0 after cuDF and others adopt stream_view
  // stream_view(int)            = delete; //< Prevent cast from 0
  // stream_view(std::nullptr_t) = delete; //< Prevent cast from nullptr

  /**
   * @brief Construct a default cudaStream_t.
   */
  constexpr explicit stream_view() : _stream{0} {}

  /**
   * @brief Implicitly convert from cudaStream_t.
   */
  stream_view(cudaStream_t stream) : _stream{stream} {}

  /**
   * @brief Implicitly convert to cudaStream_t.
   */
  operator cudaStream_t() const { return _stream; }

  /**
   * @brief Explicit conversion to uintptr_t.
   */
  explicit operator uintptr_t() const { return reinterpret_cast<uintptr_t>(_stream); }

  /**
   * @brief Compare two streams for equality.
   */
  bool operator==(stream_view const& other) { return _stream == other._stream; }

 private:
  cudaStream_t _stream;
};

}  // namespace rmm