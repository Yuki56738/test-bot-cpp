#include <iostream>
#include <dpp/dpp.h>
#include "commands/ping.h"

const std::string TOKEN = "MTE3MDA3MTcwNjA5NDc5Njg2MA.G9W-tX.CPwJtT65m81yFmKGNRoZPP13kfclI6a_LzLCfE";

int main() {
    dpp::cluster bot(TOKEN);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event){
        dpp::command_interaction interaction = event.command.get_command_interaction();
        if(event.command.get_command_name() == "ping"){
            ping(event);
        }
    });
    bot.on_ready([&bot](const dpp::ready_t& event){
        std::cout << "Logged in as:" << bot.me.username << std::endl;
        if(dpp::run_once<struct register_bot_commands>()){
            bot.global_command_create(
                    dpp::slashcommand("ping", "Reply with Pong!", bot.me.id)
                    );
        }
    });
    bot.start(dpp::st_wait);
    return 0;
}
