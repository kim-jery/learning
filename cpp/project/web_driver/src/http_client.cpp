#include "../include/http_client.hpp"
#include "../include/utility.hpp"
#include <algorithm>

namespace kjr::learning::web_driver {

beast::tcp_stream http_client::connect(std::string&& host, std::string&& port)
{
    beast::tcp_stream stream {m_ioc};
    stream.connect(m_resolver.resolve(host, port));

    return stream;
}

http_session::http_session(beast::tcp_stream&& stream):
m_stream {std::move(stream)}
{}

response http_session::send(request&& request)
{
    if (request.method() == http::verb::post) {
        request.prepare_payload();
    }
    apply_decorators(request);
    http::write(m_stream, request);

    beast::flat_buffer buffer{};
    response res {};
    http::read(m_stream, buffer, res);

    return res;
}

void http_session::apply_decorators(request& request)
{
    for (auto const& decorator : decorators) {
        decorator(request);
    }
}

}