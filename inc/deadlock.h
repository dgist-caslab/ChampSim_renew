/*
 *    Copyright 2023 The ChampSim Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DEADLOCK_H
#define DEADLOCK_H

#include <string>
#include <type_traits>
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace champsim
{
namespace detail
{
template <typename>
struct fmtstr_type_finder {
};

template <typename... Args>
struct fmtstr_type_finder<std::tuple<Args...>> {
  using type = fmt::format_string<Args...>;
};

template <typename R, typename F>
using fmtstr_type = typename fmtstr_type_finder<std::invoke_result_t<F, typename R::value_type>>::type;
} // namespace detail

// LCOV_EXCL_START Exclude the following function from LCOV
template <typename R, typename F>
void range_print_deadlock(const R& range, std::string kind_name, detail::fmtstr_type<R, F> fmtstr, F&& packing_func)
{
  if (std::empty(range)) {
    fmt::print("{} empty\n", kind_name);
    return;
  }

  auto unpacker = [fmtstr](auto... args) {
    fmt::print(fmtstr, args...);
  };

  std::size_t j = 0;
  for (auto entry : range) {
    fmt::print("[{}] entry: {} ", kind_name, j++);
    std::apply(unpacker, packing_func(entry));
  }
}
// LCOV_EXCL_STOP
} // namespace champsim

#endif
