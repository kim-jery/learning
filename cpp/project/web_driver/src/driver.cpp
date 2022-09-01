#include "../include/driver.hpp"
#include <utility>
#include <boost/json.hpp>
#include <iostream>

namespace kjr::learning::web_driver {

namespace json = boost::json;

driver::driver(std::string host, std::string port, std::optional<profile>&& profile):
    m_host {std::move(host)},
    m_port {std::move(port)}
{
    connect();
    if (profile) {
        std::cout << profile->m_tmp_path << '\n';
    }
}

driver::~driver()
{
    m_stream.socket().shutdown(asio::socket_base::shutdown_both);
}

void driver::connect()
{
    m_stream.connect(m_resolver.resolve(m_host, m_port));

    auto const& json {json::parse(consume_request(request {http::verb::get, "/status", 11}).body())};

    if (auto const ready {json.at("value").at("ready").as_bool()}; !ready) {
        throw std::runtime_error {json.at("value").at("message").as_string().c_str()};
    }
}

template<class Request>
void driver::decorate_request(Request&& request) const
{
    std::forward<Request>(request).set(http::field::host, make_path(m_host, ':', m_port));
}

template<class Request>
response driver::consume_request(Request&& request) const
{
    decorate_request(std::forward<Request>(request));
    if (std::forward<Request>(request).method() == http::verb::post) {
        std::forward<Request>(request).prepare_payload();
    }

    http::write(m_stream, std::forward<Request>(request));

    beast::flat_buffer buffer {};
    response response {};
    http::read(m_stream, buffer, response);

    return response;
}

}

