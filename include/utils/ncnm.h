/**
 * @file ncnm.h
 * @brief Provides a non-copyable, non-movable CRTP base class.
 */

#ifndef NCNM_H
#define NCNM_H

#include <concepts>
#include <type_traits>

namespace utils
{

/**
 * @brief Non-copyable, non-movable CRTP base class.
 *
 * NCNM (NonCopyableNonMovable) is a utility base class that disables
 * copy and move construction and assignment in derived classes.
 *
 * Intended to be used via inheritance:
 *
 * @code
 * class MyType : public NCNM<MyType> { ... };
 * @endcode
 *
 * @tparam T Derived type.
 */
template <typename T>
class NCNM
{
protected:
  /**
   * @brief Default protected constructor.
   */
  NCNM() = default;

  /**
   * @brief Default protected destructor.
   */
  ~NCNM() = default;

public:
  NCNM(const NCNM &) = delete;            ///< Copy construction disabled.
  NCNM &operator=(const NCNM &) = delete; ///< Copy assignment disabled.

  NCNM(NCNM &&) = delete;            ///< Move construction disabled.
  NCNM &operator=(NCNM &&) = delete; ///< Move assignment disabled.
};

/**
 * @brief Concept for types that are neither copyable nor movable.
 *
 * @details
 * Satisfied if and only if the type `T`:
 * - is not copy constructible
 * - is not copy assignable
 * - is not move constructible
 * - is not move assignable
 *
 * This concept can be used to:
 * - Constrain templates requiring strict ownership semantics
 * - Assert invariants in generic code
 *
 * @tparam T Type to evaluate.
 *
 * @par Example
 * @code
 * template <utils::NonCopyableNonMovable T>
 * void process(T& obj);
 * @endcode
 */
template <typename T>
concept NonCopyableNonMovable =
  !std::is_copy_constructible_v<T> && !std::is_copy_assignable_v<T> &&
  !std::is_move_constructible_v<T> && !std::is_move_assignable_v<T>;

} // namespace utils

#endif // NCNM_H
