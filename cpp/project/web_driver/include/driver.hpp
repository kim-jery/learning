#ifndef KJR_WEB_DRIVER_DRIVER_HPP
#define KJR_WEB_DRIVER_DRIVER_HPP
#pragma once

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <variant>
#include "utility.hpp"
#include "profile.hpp"
#include <optional>

namespace kjr::learning::web_driver {
class profile;

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace http = beast::http;
using request = http::request<http::string_body>;
using response = http::response<http::string_body>;

class driver final
{

private:
    asio::io_context m_ioc {};
    asio::ip::tcp::resolver m_resolver {m_ioc};
    mutable beast::tcp_stream m_stream {m_ioc};
    std::string m_host {};
    std::string m_port {};

public:
    driver(std::string, std::string, std::optional<profile>&&);
    ~driver();
    driver(driver const&) = delete;
    driver(driver&&) = delete;
    driver& operator =(driver const&) = delete;
    driver& operator =(driver&&) = delete;

private:
    void connect() ;
    template<class Request>
    void decorate_request(Request&&) const;
    template<class Request>
    response consume_request(Request&&) const;

};

}


#endif //KJR_WEB_DRIVER_DRIVER_HPP
