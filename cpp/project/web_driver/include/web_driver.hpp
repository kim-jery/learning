#ifndef KJR_WEB_DRIVER_WEB_DRIVER_HPP
#define KJR_WEB_DRIVER_WEB_DRIVER_HPP
#pragma once

#include <memory>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <functional>
#include <boost/json.hpp>

#include "driver_process.hpp"

namespace kjr::learning::web_driver {

namespace http = boost::beast::http;

using request = http::request<http::string_body>;
using response = http::response<http::string_body>;

template<Driver_Process T>
class web_driver
{

private:
    boost::beast::tcp_stream m_stream;
    std::function<void(http::request<http::string_body>&)> m_request_decorator;
    T m_process;

public:
    template<class... Process_Args>
    web_driver(boost::asio::ip::tcp::resolver& resolver, boost::asio::io_context& ioc, Process_Args&& ... args);
    bool is_ready();

private:
    template<std::same_as<request> Request>
    response send_request(Request&&);

};

template<Driver_Process T>
template<class... Process_Args>
web_driver<T>::web_driver(boost::asio::ip::tcp::resolver& resolver, boost::asio::io_context& ioc, Process_Args&& ... args):
m_stream{ ioc },
m_request_decorator{ [&](request& req) {
    if constexpr (sizeof...(Process_Args) == 1) {
        req.set(http::field::host, make_string("127.0.0.1:", std::forward<Process_Args>(args)...));
    } else {
        std::stringstream ss{};
        ((ss << std::forward<Process_Args>(args) << ':'), ...);
        auto host{ ss.str() };
        host.pop_back();

        req.set(http::field::host, host);
    }
} },
m_process{ T{ std::forward<Process_Args>(args)... } }
{
    if constexpr (sizeof...(Process_Args) == 1) {
        m_stream.connect(resolver.resolve("127.0.0.1", std::forward<Process_Args>(args)...));
    } else {
        m_stream.connect(resolver.resolve(std::forward<Process_Args>(args)...));
    }
}

template<Driver_Process T>
bool web_driver<T>::is_ready()
{
    return boost::json::parse(send_request(request{ http::verb::get, "/status", 11 }).body()).at("value").at("ready").as_bool();
}

template<Driver_Process T>
template<std::same_as<request> Request>
response web_driver<T>::send_request(Request&& request)
{
    if (std::forward<Request>(request).method() == http::verb::post) {
        std::forward<Request>(request).prepare_payload();
    }
    m_request_decorator(request);
    http::write(m_stream, std::forward<Request>(request));

    response response{};
    boost::beast::flat_buffer buffer{};
    http::read(m_stream, buffer, response);

    return response;
}

}

#endif //KJR_WEB_DRIVER_WEB_DRIVER_HPP
