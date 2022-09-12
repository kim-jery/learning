#ifndef KJR_WEB_DRIVER_DRIVER_PROCESS_HPP
#define KJR_WEB_DRIVER_DRIVER_PROCESS_HPP
#pragma once

#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <string>
#include <filesystem>

namespace kjr::learning::web_driver {

class geckodriver_process final
{

private:
    boost::asio::io_service m_ios{};
    boost::process::child m_process{};

public:
    geckodriver_process(std::string&&, std::string&&);
    geckodriver_process(std::filesystem::path&&, std::string&&, std::string&&);
    ~geckodriver_process();
    geckodriver_process(geckodriver_process const&) = delete;
    geckodriver_process(geckodriver_process&&) = delete;
    geckodriver_process& operator=(geckodriver_process const&) = delete;
    geckodriver_process& operator=(geckodriver_process&&) = delete;

};

class msedgedriver_process final
{
private:
    boost::asio::io_service m_ios{};
    boost::process::child m_process{};

public:
    explicit msedgedriver_process(std::string&&);
    msedgedriver_process(std::filesystem::path&&, std::string&&);
    ~msedgedriver_process();
    msedgedriver_process(msedgedriver_process const&) = delete;
    msedgedriver_process(msedgedriver_process&&) = delete;
    msedgedriver_process& operator=(msedgedriver_process const&) = delete;
    msedgedriver_process& operator=(msedgedriver_process&&) = delete;

};

template<class T>
concept Driver_Process = requires {
    std::same_as<geckodriver_process, T> || std::same_as<msedgedriver_process, T>;
};

}

#endif //KJR_WEB_DRIVER_DRIVER_PROCESS_HPP