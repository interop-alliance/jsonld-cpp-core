//
// Created by user on 25.07.20.
//

#ifndef JSONLDPROMISE_H
#define JSONLDPROMISE_H

#include <exception>
#include <future>

class JsonldPromise {
public:
    std::optional<nlohmann::json> getData() {
        return{};
    }
private:
    std::future<std::optional<nlohmann::json>> m_future;

    // Pass this to a thread
    std::exception_ptr m_error;
};

#endif JSONLDPROMISE_H
