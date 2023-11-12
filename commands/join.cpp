//
// Created by user on 2023/11/12.
//

#include "join.h"

void join(const dpp::slashcommand_t& event){
    dpp::guild* g = dpp::find_guild(event.command.guild_id);
    auto current_vc = event.from->get_voice(event.command.guild_id);

    bool join_vc = true;

    if(current_vc){
        auto users_vc = g->voice_members.find(event.command.get_issuing_user().id);

        if (users_vc != g->voice_members.end() && current_vc->channel_id == users_vc->second.channel_id) {
            join_vc = false;

        }else{
            event.from->disconnect_voice(event.command.guild_id);
            join_vc = true;
        }
    }
    if(join_vc){
        g->connect_member_voice(event.command.get_issuing_user().id);
        event.reply("Connected.");
    }
}