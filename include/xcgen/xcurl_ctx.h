/**
 * @file xcurl_ctx.h
 * @brief cURL wrapper that includes context management for simple HTTP
 * requests.
 */

#ifndef XCURL_CTX_H
#define XCURL_CTX_H

#include <ncnm.h>
#include <xcgen>
#include <xcwpr>

/**
 * @namespace xcgen
 * @brief Namespace containing utilities for Xcurl context management.
 */
namespace xcgen
{

/**
 * @brief Default wrapper type.
 *
 * Alias for utils::NCNM<T>, typically used to enforce non-copyable/non-movable
 * semantics or other ownership constraints defined by NCNM.
 *
 * @tparam T The underlying type.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief Context-aware client wrapper.
 *
 * XcurlCtx encapsulates a client instance together with an associated context.
 * It provides safe access to the client while maintaining context state.
 *
 * @tparam Client     The client type being wrapped.
 * @tparam ClientArg  The type used to construct the client.
 * @tparam Ctx        The context type associated with the client.
 */
template <typename Client, typename ClientArg, typename Ctx>
  requires topology::xcgen::XcurlTy<Client> && 
  topology::xcgen::ClientArgTy<ClientArg> &&
  topology::xcwpr::HasBoolStatus<Ctx>
class XcurlCtx
{
public:
  /**
   * @brief Constructs the context and client.
   *
   * Initializes the internal context and client using the provided argument.
   *
   * @param arg Argument used to construct the client.
   */
  explicit XcurlCtx(ClientArg arg) noexcept;

  /**
   * @brief Checks whether the context is in a valid state.
   *
   * @return true if the context is valid, false otherwise.
   */
  bool ctx_status() const noexcept;

  /**
   * @brief Returns a reference to the client.
   *
   * @return Reference to the underlying client.
   */
  Client &ref() noexcept;

  /**
   * @brief Returns a const reference to the client.
   *
   * @return Const reference to the underlying client.
   */
  const Client &ref() const noexcept;

  /**
   * @brief Accesses the client via pointer-like semantics.
   *
   * @return Pointer to the client.
   */
  Client *operator->() noexcept;

  /**
   * @brief Accesses the client via pointer-like semantics (const version).
   *
   * @return Const pointer to the client.
   */
  const Client *operator->() const noexcept;

private:
  /// Context associated with the client.
  Ctx ctx_;

  /// Wrapped client instance.
  Client client_;
};

} // namespace xcgen

#include <xcurl_ctx.tpp>

#endif
