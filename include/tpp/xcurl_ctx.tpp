
namespace xcgen{

template <typename Client, typename ClientArg, typename Ctx>
XcurlCtx<Client, ClientArg, Ctx>::XcurlCtx(ClientArg arg) noexcept
    : ctx_{}, client_{arg} {}

template <typename Client, typename ClientArg, typename Ctx>
bool XcurlCtx<Client, ClientArg, Ctx>::ctx_status() const noexcept {
    return ctx_.status();
}

template <typename Client, typename ClientArg, typename Ctx>
Client& XcurlCtx<Client, ClientArg, Ctx>::ref() noexcept {
    return client_;
}

template <typename Client, typename ClientArg, typename Ctx>
const Client& XcurlCtx<Client, ClientArg, Ctx>::ref() const noexcept {
    return client_;
}

template <typename Client, typename ClientArg, typename Ctx>
Client* XcurlCtx<Client, ClientArg, Ctx>::operator->() noexcept {
    return &client_;
}

template <typename Client, typename ClientArg, typename Ctx>
const Client* XcurlCtx<Client, ClientArg, Ctx>::operator->() const noexcept {
    return &client_;
}

}
