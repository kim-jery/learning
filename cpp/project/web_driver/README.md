# Web Driver

## Intro
Little implementation of a web driver specification using C++ and Boost library.

Currently, is only tested with firefox (geckodriver) and the only purpose of this is to apply what's learned.

BTW should never be used in a serious environment :) It is clearly NOT a full implementation of the WebDriver specification.
- No error handling or event report
- Most of responses from the WebDriver are ignored
- All functionalities are not implemented
- ...

## Dependencies
- C++ 20
- Boost
    - [Beast](https://www.boost.org/doc/libs/master/libs/beast/doc/html/index.html)
    - [Json](https://www.boost.org/doc/libs/master/libs/json/doc/html/index.html)

## How to use in One* line