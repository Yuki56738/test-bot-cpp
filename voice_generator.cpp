//
// Created by ubuntu on 11/25/23.
//

#include "voice_generator.h"
#include <cpprest/json.h>
#include <cpprest/uri.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
//using namespace web::http::experimental::listener;          // HTTP server
//using namespace web::experimental::web_sockets::client;     // WebSockets client
using namespace web::json;                                  // JSON library
using namespace std;

void createWav(const utility::string_t& text, const utility::string_t& toPostUrl){
    http_client client(U(toPostUrl));
    uri_builder builder(U("/audio_query"));
    builder.append_query(U("speaker"), U("14"));
    builder.append_query(U("text"), U(text));

    client.request(methods::POST, builder.to_string())
        .then([=](http_response res){
            cout << res.status_code() << endl;

            http_client client2(U(toPostUrl)+U("/synthesis"));
            http_request request(methods::POST);
            request.headers().set_content_type(U("application/json"));
            json::value obj = res.extract_json().get();
            obj[U("speaker")] = json::value(14);

            request.set_body(obj);
            client2.request(request).then([](http_response res2){
               cout << res2.status_code() <<endl;


                concurrency::streams::fstream::open_ostream("output.wav").then([=](concurrency::streams::ostream output_stream) {
                    // Write the response body to the file
                    return res2.body().read_to_end(output_stream.streambuf());
                }).then([=](size_t /*bytesWritten*/) {
                    std::wcout << L"Response saved to file: " << "output.wav" << std::endl;
                }).wait(); // Wait for the file operations to complete


        }).wait();
});

}
