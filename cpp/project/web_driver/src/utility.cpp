#include "../include/utility.hpp"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace kjr::learning::web_driver {

std::string generate_uuid()
{
    static boost::uuids::random_generator generator{};
    std::stringstream ss{};
    ss << generator();

    return ss.str();
}

}