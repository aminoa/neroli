// Copyright 2020 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

#include <memory>
#ifdef ENABLE_HTTPLIB
#include <httplib.h>
#endif
#include "common/logging/log.h"
#include "core/nus_download.h"

namespace Core::NUS {

#ifndef ENABLE_HTTPLIB

std::optional<std::vector<u8>> Download(const std::string& path) {
    LOG_ERROR(WebService, "Cannot download {}: built without HTTP support", path);
    return {};
}

#else

std::optional<std::vector<u8>> Download(const std::string& path) {
    constexpr auto HOST = "http://nus.cdn.c.shop.nintendowifi.net";

    std::unique_ptr<httplib::Client> client = std::make_unique<httplib::Client>(HOST);
    if (client == nullptr) {
        LOG_ERROR(WebService, "Invalid URL {}{}", HOST, path);
        return {};
    }

    httplib::Request request{
        .method = "GET",
        .path = path,
        // Needed when httplib is included on android
        .matches = httplib::Match(),
    };

    client->set_follow_location(true);
    const auto result = client->send(request);
    if (!result) {
        LOG_ERROR(WebService, "GET to {}{} returned null", HOST, path);
        return {};
    }

    const auto& response = result.value();
    if (response.status >= 400) {
        LOG_ERROR(WebService, "GET to {}{} returned error status code: {}", HOST, path,
                  response.status);
        return {};
    }
    if (!response.headers.contains("content-type")) {
        LOG_ERROR(WebService, "GET to {}{} returned no content", HOST, path);
        return {};
    }

    return std::vector<u8>(response.body.begin(), response.body.end());
}

#endif // ENABLE_HTTPLIB

} // namespace Core::NUS
