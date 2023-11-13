//
// Created by user on 2023/11/13.
//

#include "voice_generator.h"
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

void createWav(const utility::string_t& text, const utility::string_t& toPostUrl){
    http_client client(U("http://" + toPostUrl));

    uri_builder builder(U("/audio_query"));
    builder.append_query(U("speaker"), U("14"));
    builder.append_query(U("text"), utility::conversions::to_string_t(text));

    client.request(methods::POST, builder.to_string())
            .then([toPostUrl](http_response response) {
                std::cout << "Status code: " << response.status_code() << std::endl;
                auto res = response.extract_string();
//            })
//            .then([toPostUrl](std::string response_content) {
                http_client client1(U("http://" + toPostUrl));

                uri_builder builder1(U("/synthesis"));
                builder1.append_query(U("speaker"), U("14"));


                http_request request(methods::POST);
                request.headers().add(U("Content-Type"), U("application/json"));

                request.set_body(res.get());

                auto res1 = client1.request(methods::POST, builder1.to_string(),request.to_string());
                std::cout << res1.get().status_code() << std::endl;
//            })
//            .then([](http_response response) {
                auto res2 = res1.get().extract_vector();
//            })
//            .then([](std::vector<uint8_t> response_content) {
                std::ofstream output_file("output.wav", std::ios::binary);
                output_file.write(reinterpret_cast<const char*>(res2.get().data()), res2.get().size());
                output_file.close();
                std::cout << "WAV file created." << std::endl;
            });
}

