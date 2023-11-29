//
// Created by ubuntu on 11/25/23.
//

#ifndef TEST_BOT_CPP_VOICE_GENERATOR_H
#define TEST_BOT_CPP_VOICE_GENERATOR_H

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/details/basic_types.h>

void createWav(const utility::string_t& text, const utility::string_t& toPostUrl);


#endif //TEST_BOT_CPP_VOICE_GENERATOR_H
