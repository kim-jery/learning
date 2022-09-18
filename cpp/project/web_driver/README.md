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

## How to use in One* line