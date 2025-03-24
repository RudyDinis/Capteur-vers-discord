const { Client, GatewayIntentBits } = require('discord.js');
const express = require('express');

const USER_ID = 'VotreIdDiscord';  

const bot = new Client({ intents: [GatewayIntentBits.DirectMessages] });
const app = express();
app.use(express.json());

bot.once('ready', () => {
    console.log(`Connecté en tant que ${bot.user.tag}`);
});

app.post('/alert', async (req, res) => {
    const { distance } = req.body;

    if (distance < 150) {
        try {
            const user = await bot.users.fetch(USER_ID);
            await user.send(`🚨 Alerte ! Distance détectée : ${distance} cm`);
            res.json({ message: 'Message envoyé !' });
        } catch (error) {
            console.error('Erreur envoi message:', error);
            res.status(500).json({ error: 'Impossible d’envoyer le message' });
        }
    } else {
        res.json({ message: 'Distance OK' });
    }
});

bot.login("Token");
app.listen(3010, () => console.log('Serveur HTTP en écoute sur le port 3010'));
