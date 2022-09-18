#include "../include/web_driver.hpp"
#include <boost/json.hpp>
#include <iostream>

namespace kjr::learning::web_driver {

namespace json = boost::json;

web_driver::web_driver(http_session&& http_session, firefox_capabilities const& capabilities):
m_http_session(std::move(http_session))
{
    m_session_id = json::parse(m_http_session.send([&capabilities]() -> request {
        request req{ http::verb::post, "/session", 11 };
        req.body() = json::serialize(json::value_from(capabilities));

        return req;
    }()).body()).at("value").at("sessionId").as_string();
}

web_driver::~web_driver()
{
    m_http_session.send({ http::verb::delete_, make_string("/session/", m_session_id), 11 });
}

void web_driver::get(std::string&& url)
{
    m_http_session.send([this, &url]() -> request {
        request req{ http::verb::post, make_string("/session/", m_session_id, "/url"), 11 };
        req.body() = json::serialize(json::value{
        { "url", url }
        });

        return req;
    }());
}

std::string web_driver::current()
{
    return std::string{
    json::parse(m_http_session.send({ http::verb::get, make_string("/session/", m_session_id, "/url"), 11 }).body()).at("value").as_string()
    };
}

std::string web_driver::title()
{
    return std::string{
    json::parse(m_http_session.send({ http::verb::get, make_string("/session/", m_session_id, "/title"), 11 }).body()).at("value").as_string()
    };
}

std::string web_driver::source()
{
    return std::string{
    json::parse(m_http_session.send({ http::verb::get, make_string("/session/", m_session_id, "/source"), 11 }).body()).at("value").as_string()
    };
}

bool web_driver::is_ready()
{
    return json::parse(m_http_session.send({ http::verb::get, "/status", 11 }).body()).at("value").at("ready").as_bool();
}

void web_driver::back()
{
    navigate<navigation::back>();
}

void web_driver::forward()
{
    navigate<navigation::forward>();
}

void web_driver::refresh()
{
    navigate<navigation::refresh>();
}

void web_driver::new_tab()
{
    switch_tab(std::string{ json::parse(m_http_session.send([this]() -> auto {
        request req{ http::verb::post, make_string("/session/", m_session_id, "/window/new"), 11 };
        req.body() = json::serialize(json::value{
        { "type", "tab" }
        });

        return req;
    }()).body()).at("value").at("handle").as_string() });

}

void web_driver::switch_tab(std::string&& handle)
{
    m_http_session.send([&handle, this]() -> auto {
        request req{ http::verb::post, make_string("/session/", m_session_id, "/window"), 11 };
        req.body() = json::serialize(json::value{
        { "handle", handle }
        });

        return req;
    }());
}

element web_driver::find(std::string&& xpath)
{
    request req{ http::verb::post, make_string("/session/", m_session_id, "/element"), 11 };
    req.body() = json::serialize(json::value{
    { "using", "xpath" },
    { "value", xpath }
    });

    auto const json_value{ json::parse(m_http_session.send(std::move(req)).body()).at("value").as_object() };

    return { m_http_session, m_session_id, std::string{ json_value.begin()->value().as_string() } };
}

element::element(http_session& session, std::string_view session_id, std::string&& id):
m_session{ session },
m_session_id{ session_id },
m_id{ std::move(id) }
{}

std::string element::name() const
{
    return std::string{ json::parse(m_session.send([this]() -> request {
        return { http::verb::get, make_string("/session/", m_session_id, "/element/", m_id, "/name"), 11 };
    }()).body()).at("value").as_string() };
}

std::string element::text() const
{
    return std::string{ json::parse(m_session.send([this]() -> request {
        return { http::verb::get, make_string("/session/", m_session_id, "/element/", m_id, "/text"), 11 };
    }()).body()).at("value").as_string() };
}

}