#pragma once
// Placeholder for crow.h
#include <string>
#include <functional>
#include <iostream>

namespace crow {
    struct request {
        std::string body;
    };
    struct response {
        response(int code, std::string body) {}
    };
    namespace json {
        struct wvalue {
            std::string s() { return ""; }
            double d() { return 0.0; }
            wvalue& operator[](const std::string& key) { return *this; }
            void operator=(const std::string& val) {}
            void operator=(double val) {}
        };
        wvalue load(std::string) { return wvalue(); }
    }
    struct SimpleApp {
        SimpleApp& port(int) { return *this; }
        SimpleApp& multithreaded() { return *this; }
        void run() {}
    };
}
#define CROW_ROUTE(app, url) 
