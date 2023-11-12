//
// Created by user on 2023/11/12.
//

#include "ping.h"

void ping(const dpp::slashcommand_t& event){
    event.reply("Pong!");
}