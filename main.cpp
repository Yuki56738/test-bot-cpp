#include <iostream>
#include <dpp/dpp.h>
#include "commands/ping.h"
#include "dotenv.h"
#include "commands/join.h"
#include "commands/leave.h"
#include "voice_generator.h"

using namespace dotenv;

int main() {
//    env.load_dotenv();
    createWav("こんにちは！", "risaton.net:50021");
    auto& dotenv = env;
    dotenv.load_dotenv();
    const std::string TOKEN = dotenv.operator[]("TOKEN");
    std::cout << TOKEN << std::endl;
//    const std::string TOKEN = env["TOKEN"];
    dpp::cluster bot(TOKEN);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event){
        dpp::command_interaction interaction = event.command.get_command_interaction();
        if(event.command.get_command_name() == "ping"){
            ping(event);
        }
        if(event.command.get_command_name() == "join"){
            join(event);
        }
        if(event.command.get_command_name() == "leave"){
            leave(event);
        }
    });
    bot.on_ready([&bot](const dpp::ready_t& event){
        std::cout << "Logged in as:" << bot.me.username << std::endl;
        if(dpp::run_once<struct register_bot_commands>()){
            bot.global_command_create(
                    dpp::slashcommand("ping", "Reply with Pong!", bot.me.id)
                    );
            bot.global_command_create(dpp::slashcommand("join", "Connect to VC.", bot.me.id));
            bot.global_command_create(dpp::slashcommand("leave", "Disconnect from VC.", bot.me.id));
        }
    });
    bot.start(dpp::st_wait);
    return 0;
}
