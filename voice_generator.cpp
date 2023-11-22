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
using namespace std;

void createWav(const utility::string_t& text, const utility::string_t& to_post_url){
    // Set the parameters
//    utility::string_t to_post_url = U("your_server_address");
//    utility::string_t text = U("your_text");
    utility::string_t speaker = U("14");

    // Prepare parameters for the first request
    http_client client(to_post_url);
    uri_builder builder(U("/audio_query"));
    builder.append_query(U("speaker"), speaker);
    builder.append_query(U("text"), text);

    // Make the first POST request
    http_response response = client.request(methods::POST, builder.to_string()).get();
    wcout << L"Response status code: " << response.status_code() << std::endl;

    // Prepare parameters for the second request
    http_client client2(to_post_url);
    uri_builder builder2(U("/synthesis"));
    builder2.append_query(U("speaker"), speaker);

    // Make the second POST request
    http_request request2(methods::POST);
    request2.headers().set_content_type(U("application/json"));
    request2.headers().set_content_length(response.headers().content_length());

    request2.set_body(response.body());

    http_response response2 = client2.request(request2.method(), builder2.to_string(), request2.body(), request2.headers()).get();

    // Save the response content to a file
    auto fileStream = std::make_shared<ostream>();

    // Open stream to output file.
    pplx::task<void> writeTask = fstream::open_ostream(U("output.wav")).then([=](ostream outFile) {
        *fileStream = outFile;

        // Write the response content to the file.
        return response2.body().read_to_end(fileStream->streambuf());
    });

    // Wait for the write operation to finish.
    writeTask.wait();

    wcout << L"File 'output.wav' saved." << std::endl;
    }

