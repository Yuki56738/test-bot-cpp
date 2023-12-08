//
// Created by user on 2023/12/01.
//

#include "voice_generator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <cstdlib>

using namespace std;

// A helper function to write the response data from curl to a string
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)buffer, size * nmemb);
    return size * nmemb;
}

void createWav(const char* text, const char* toPostUrl){
//    std::string to_post_url = get_env("VVOX_URL");
    std::string to_post_url = toPostUrl;
    // Create a HTTP client
    http_client client(U("http://" + to_post_url));

    // Create a JSON object with parameters
    json::value params;
    params[U("speaker")] = json::value::number(14);
    params[U("text")] = json::value::string(text);

    // Make a POST request to /audio_query endpoint
    return client.request(methods::POST, U("/audio_query"), params)
            .then([](http_response response [aborted]

}
