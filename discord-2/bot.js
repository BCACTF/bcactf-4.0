const Discord = require("discord.js");
const { REST } = require('@discordjs/rest');
const { Routes } = require('discord-api-types/v9');

require('dotenv').config()
const client = new Discord.Client({
    intents: ['Guilds', 'GuildMessages', 'GuildMembers', 'MessageContent']
});

const token = process.env['token'];
const guildId = process.env['server'];
const roleId = process.env['role'];
const clientId = process.env['client'];
const rest = new REST({ version: '9' }).setToken(token);
(async () => {
    try {
        console.log('Started refreshing application commands.');

        await rest.put(
            Routes.applicationGuildCommands(clientId, guildId),
            {
                body: [new Discord.ContextMenuCommandBuilder()
                    .setName("Get Flag Part 2")
                    .setType(Discord.ApplicationCommandType.User)]
            },
        );

        console.log('Successfully reloaded application commands.');
    } catch (error) {
        console.error(error);
    }
})();

client.login(token);

client.on("ready", () => {
    console.log(`Logged in as ${client.user.tag}.`);
});

client.on("guildMemberAdd", member => {
    member.guild.roles.fetch(roleId).then(
        role => member.guild.members.addRole({ user: member, role: role })
    )
})

client.on("interactionCreate", interaction => {
    if (!interaction.isUserContextMenuCommand()) return;
    interaction.reply({ content: 'xcb8vh3t}', ephemeral: true });
});

client.on("messageCreate", message => {
    if (message.author.id != message.guild.ownerId) {
        message.delete();
    }
})