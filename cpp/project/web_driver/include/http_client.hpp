#ifndef KJR_WEB_DRIVER_HTTP_CLIENT_HPP
#define KJR_WEB_DRIVER_HTTP_CLIENT_HPP
#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <vector>
#include <functional>
#include "utility.hpp"

namespace kjr::learning::web_driver {

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace http = beast::http;

using request = http::request<http::string_body>;
using response = http::response<http::string_body>;

class http_client final
{

private:
    asio::io_context m_ioc {};
    asio::ip::tcp::resolver m_resolver {m_ioc};

public:
    beast::tcp_stream connect(std::string&&, std::string&&);

};

class http_session final
{

private:
    beast::tcp_stream m_stream;

public:
    std::vector<std::function<void(request&)>> decorators {};

public:
    explicit http_session(beast::tcp_stream&& stream);
    response send(request&&);

private:
    void apply_decorators(request&);

};

template<bool Inject_User_Agent = false>
http_session make_http_session(http_client& client, std::string&& host, std::string&& port)
{
    auto const decorator {[host, port](request& request) -> void {
        request.set(http::field::host, make_string<':'>(host, port));
    }};
    http_session session {client.connect(std::move(host), std::move(port))};
    session.decorators.emplace_back(decorator);
    if constexpr (Inject_User_Agent) {
        session.decorators.emplace_back([](request& request) -> void {
            request.set(http::field::user_agent, R"(Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:104.0) Gecko/20100101 Firefox/104.0)");
        });
    }

    return session;
}

}

#endif //KJR_WEB_DRIVER_HTTP_CLIENT_HPP