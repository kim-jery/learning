#include "../include/utility.hpp"
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace kjr::learning::web_driver {

std::string generate_uuid()
{
    boost::uuids::random_generator generator {};
    std::stringstream ss {};
    ss << generator();

    return ss.str();
}

}