#include "../include/driver_process.hpp"
#include "../include/utility.hpp"

namespace kjr::learning::web_driver {

namespace process = boost::process;

geckodriver_process::geckodriver_process(std::string&& host, std::string&& port):
m_process{ make_string<true>(process::search_path("geckodriver"), "-p", port, "--host", host), process::std_out > process::null, m_ios }
{
    m_ios.run();
}

geckodriver_process::geckodriver_process(std::filesystem::path&& binary_path, std::string&& host, std::string&& port):
m_process{ make_string<true>(binary_path, "-p", port, "--host", host), process::std_out > process::null, m_ios }
{
    m_ios.run();
}

geckodriver_process::~geckodriver_process()
{
    m_ios.stop();
}

msedgedriver_process::msedgedriver_process(std::string&& port):
m_process{ make_string(process::search_path("msedgedriver"), " -port=", port), process::std_out > process::null, m_ios }
{
    m_ios.run();
}

msedgedriver_process::msedgedriver_process(std::filesystem::path&& edgedriver_binary, std::string&& port):
m_process{ make_string(edgedriver_binary, " -port=", port) }
{
    m_ios.run();
}

msedgedriver_process::~msedgedriver_process()
{
    m_ios.stop();
}

}
