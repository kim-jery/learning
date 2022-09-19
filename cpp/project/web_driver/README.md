# Web Driver

## Intro

Little implementation of the [web driver specification](https://www.w3.org/TR/webdriver/) using C++ and Boost library.

Currently, is only tested with firefox (geckodriver) and the only purpose of this little project is to apply what's has
been learned.

BTW should never be used in a serious environment :) It is clearly NOT a full (serious ?) implementation of the
web driver specification.

- No error handling or event report
- Most of responses from the web driver are ignored
- All functionalities are not implemented (far from it !)
- ...

## Dependencies

- C++ 20
- Boost
    - [Beast](https://www.boost.org/doc/libs/master/libs/beast/doc/html/index.html)
    - [Json](https://www.boost.org/doc/libs/master/libs/json/doc/html/index.html)
    - [UUID](https://www.boost.org/doc/libs/master/libs/uuid/doc/index.html)
    - [Process](https://www.boost.org/doc/libs/master/doc/html/process.html)
- [Geckodriver](https://github.com/mozilla/geckodriver/releases)

## How to use in One* line

~~~cpp
#include ".../web_driver.hpp"
#include <iostream>

int main()
{
    constexpr static auto host{ "127.0.0.1" };
    constexpr static auto port{ "4445" };
    
    kjr::learning::web_driver::firefox_capabilities cap{ 
    port, 
    R"(path to firefox executable)", 
    {"-headless"} // extra cmd args - this will enable headless mode 
    };
    // assign an existing profile to the driver
    // not mandatory
    // need write-read access to the profile and system tmp directory
    cap.set_profile(kjr::learning::web_driver::profile{ R"(path to an existing firefox profile)" }); 
    
    kjr::learning::web_driver::http_client client{};
    kjr::learning::web_driver::web_driver driver{ 
    kjr::learning::web_driver::make_http_session<true>(client, host, port), 
    cap 
    }; // start the web driver with the firefox capabilities
    
    // exemple with cpp reference
    driver.get("https://en.cppreference.com/w/cpp/memory/unique_ptr");

    // extracting basic information about the page
    std::cout << driver.title() << '\n'; // page title
    std::cout << driver.current() << '\n'; // current url
    std::cout << driver.source() << '\n'; // page source

    // navigating
    driver.refresh(); // refresh the page
    driver.back(); // go back
    driver.forward(); // go forward

    // tabs
    driver.new_tab(); // open an new tab and put focus on it
    driver.get("https://en.cppreference.com/w/cpp/memory/shared_ptr"); // assign an url to the tab

    auto const element{ driver.find("//h1[@id='firstHeading']") };
    std::cout << element.name() << '\n'; // html tag name (h1 in this case)
    std::cout << element.text() << '\n'; // html tag content (std::shared_ptr in this case)
}
~~~