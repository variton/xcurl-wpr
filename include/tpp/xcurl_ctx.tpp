
#include <xcwpr_concepts.h>

namespace xcgen{

template <typename Client, typename ClientArg, typename Ctx>
requires xcurl_topology<Client> && 
client_arg_topology<ClientArg> &&
xcwpr::HasBoolStatus<Ctx>
XcurlCtx<Client, ClientArg, Ctx>::XcurlCtx(ClientArg arg) noexcept
    : ctx_{}, client_{arg} {}

template <typename Client, typename ClientArg, typename Ctx>
requires xcurl_topology<Client> && 
client_arg_topology<ClientArg> &&
xcwpr::HasBoolStatus<Ctx>
bool XcurlCtx<Client, ClientArg, Ctx>::ctx_status() const noexcept {
    return ctx_.status();
}

template <typename Client, typename ClientArg, typename Ctx>
requires xcurl_topology<Client> && 
client_arg_topology<ClientArg> &&
xcwpr::HasBoolStatus<Ctx>
Client& XcurlCtx<Client, ClientArg, Ctx>::ref() noexcept {
    return client_;
}

template <typename Client, typename ClientArg, typename Ctx>
requires xcurl_topology<Client> && 
client_arg_topology<ClientArg> &&
xcwpr::HasBoolStatus<Ctx>
const Client& XcurlCtx<Client, ClientArg, Ctx>::ref() const noexcept {
    return client_;
}

template <typename Client, typename ClientArg, typename Ctx>
requires xcurl_topology<Client> && 
client_arg_topology<ClientArg> &&
xcwpr::HasBoolStatus<Ctx>
Client* XcurlCtx<Client, ClientArg, Ctx>::operator->() noexcept {
    return &client_;
}

template <typename Client, typename ClientArg, typename Ctx>
requires xcurl_topology<Client> && 
client_arg_topology<ClientArg> &&
xcwpr::HasBoolStatus<Ctx>
const Client* XcurlCtx<Client, ClientArg, Ctx>::operator->() const noexcept {
    return &client_;
}

}
