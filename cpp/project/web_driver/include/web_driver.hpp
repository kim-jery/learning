#ifndef KJR_WEB_DRIVER_WEB_DRIVER_HPP
#define KJR_WEB_DRIVER_WEB_DRIVER_HPP
#pragma once

#include "capabilities.hpp"
#include "http_client.hpp"
#include "utility.hpp"
#include <string>

namespace kjr::learning::web_driver {
class firefox_capabilities;

class http_session;

class element;

class web_driver final
{

public:
    enum class navigation
    {
        back,
        forward,
        refresh
    };

private:
    http_session m_http_session;
    std::string m_session_id{};

public:
    web_driver(http_session&&, firefox_capabilities const&);
    web_driver(web_driver const&) = delete;
    web_driver(web_driver&&) = delete;
    web_driver& operator=(web_driver const&) = delete;
    web_driver& operator=(web_driver&&) = delete;
    ~web_driver();
    void get(std::string&&);
    std::string current();
    std::string title();
    std::string source();
    bool is_ready();
    void back();
    void forward();
    void refresh();
    void new_tab();
    void switch_tab(std::string&&);
    element find(std::string&&);

    template<navigation Direction>
    inline void navigate()
    {
        constexpr static auto direction{ []() -> std::string_view {
            using
            enum navigation;
            if constexpr (Direction == back) {
                return "/back";
            } else if constexpr (Direction == forward) {
                return "/forward";
            } else {
                return "/refresh";
            }
        }() };

        request req{ http::verb::post, make_string("/session/", m_session_id, direction), 11 };
        req.body() = "{}";
        m_http_session.send(std::move(req));
    }

};

class element final
{

private:
    http_session& m_session;
    std::string_view m_session_id{};
    std::string m_id{};

public:
    element(http_session&, std::string_view, std::string&&);
    [[nodiscard]] std::string name() const;
    [[nodiscard]] std::string text() const;
    void click() const;

};

}

#endif //KJR_WEB_DRIVER_WEB_DRIVER_HPP