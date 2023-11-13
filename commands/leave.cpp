//
// Created by user on 2023/11/12.
//

#include "leave.h"

void leave(const dpp::slashcommand_t& event){
    dpp::guild* g = dpp::find_guild(event.command.guild_id);

    auto current_vc = event.from->get_voice(event.command.guild_id);
    if(current_vc){
//        auto users_vc = g->voice_members.find((event.command.get_issuing_user()).id);
        event.from->disconnect_voice(event.command.guild_id);
        event.reply("Disconnected.");
//        current_vc->disconnect();
    }

}