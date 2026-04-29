#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "Button.h"
#include "EventManager.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Character SFML - Invert Mode");
    window.setFramerateLimit(60);

    sf::Shader invertShader;
    if (!invertShader.loadFromFile("asset/invert.frag", sf::Shader::Type::Fragment)) {
        std::cerr << "Erreur : Impossible de charger le shader !" << std::endl;
    }

    sf::RenderTexture sceneTexture;
    if (!sceneTexture.resize({ 800, 600 }))
        return -1;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("asset/background/maison.png"))
        return -1;
    sf::Sprite background(backgroundTexture);

    sf::Texture screamerTexture;
    if (!screamerTexture.loadFromFile("asset/Romain.jpg"))
        return -1;
    sf::Sprite screamerSprite(screamerTexture);
    screamerSprite.setOrigin({ screamerTexture.getSize().x / 2.f, screamerTexture.getSize().y / 2.f });
    screamerSprite.setPosition({ 400.f, 600.f });

    sf::SoundBuffer screamBuff;
    if (!screamBuff.loadFromFile("sound/Scream.mp3"))
        return -1;
    sf::Sound screamSound(screamBuff);

    sf::Texture pandariaTexture;
    pandariaTexture.loadFromFile("asset/Pandaria.png");
    sf::Sprite pandariaSprite(pandariaTexture);
	pandariaSprite.setOrigin({ pandariaTexture.getSize().x / 2.f, pandariaTexture.getSize().y / 2.f });
    pandariaSprite.setPosition({ 400.f, 300.f });

    sf::SoundBuffer pandariaBuff;
    pandariaBuff.loadFromFile("sound/Foule.mp3");
    sf::Sound pandariaSound(pandariaBuff);

	sf::SoundBuffer fartBuff;
    if(!fartBuff.loadFromFile("sound/Fart.mp3"))
		return -1;
	sf::Sound fartSound(fartBuff);

    Character player;
    Button button;
    EventManager eventMana;

    // Configuration des animations
    player.addAnimation("idle", "asset/Buck Borris/idle.png", 36, 0, 10, 23, 4, 0.15f, true);
    player.addAnimation("run", "asset/Buck Borris/run.png", 36, 0, 10, 23, 3, 0.08f, true);
    player.addAnimation("air", "asset/Buck Borris/jump.png", 36, 0, 10, 23, 5, 10.10f, true);
    player.addAnimation("landing", "asset/Buck Borris/land.png", 36, 0, 10, 23, 5, 0.10f, false);
    player.addAnimation("attack", "asset/Buck Borris/attacks.png", 36, 0, 10, 23, 11, 0.10f, false);

    player.setPosition(100.f, 400.f);
    player.playAnimation("idle");
    button.setPositionButton(500.f, 435.f);
    button.loadTextureButton("asset/buttons.png");
    button.setPositionButton(500.f, 430.f);

    sf::Clock clock;
    bool wasKeyPressed = false; // Pour éviter que l'inversion clignote trop vite

    while (window.isOpen())
    {
        // --- Events ---
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // --- Update ---
        const float dt = clock.restart().asSeconds();
        player.update(dt);
        button.playAnimation(player);
        eventMana.update();

        // On vérifie si la touche E est pressée ET si le joueur touche le bouton
        bool isPressingE = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
        bool collision = button.isColliding(button.getSprite(), player.getSprite());

        if (isPressingE && collision && !wasKeyPressed) {
            eventMana.triggerRandomEvent(player);
            if (eventMana.isScreamer())
                screamSound.play();
            if (eventMana.isPandaria())
                pandariaSound.play();
			if (eventMana.isFart())
				fartSound.play();

            wasKeyPressed = true;     // Marqueur pour ne changer qu'une fois par pression
        }
        if (!isPressingE) {
            wasKeyPressed = false;    // On reset quand on relâche la touche
        }

        // --- Draw ---
        sceneTexture.clear(sf::Color(230, 130, 30));
        sceneTexture.draw(background);
        button.drawButton(sceneTexture);
        button.playAnimation(player);
        player.draw(sceneTexture);
        sceneTexture.display();

        window.clear();

        // On crée un sprite à partir de la texture de la scène
        sf::Sprite sceneSprite(sceneTexture.getTexture());

        // Gestion du Flip (Retournement)
        if (eventMana.isFlipped()) {
            sceneSprite.setOrigin({ 400.f, 300.f });
            sceneSprite.setPosition({ 400.f, 300.f });
            sceneSprite.setScale({ 1.f, -1.f });
        }

        // Gestion de l'Inversion (Shader)
        if (eventMana.isInverted()) {
            window.draw(sceneSprite, &invertShader);
        }
        else {
            window.draw(sceneSprite);
        }
        if (eventMana.isScreamer()) {
            window.draw(screamerSprite);
        }
        if (eventMana.isPandaria()) {
            window.draw(pandariaSprite);
        }
        window.display();
    }
	return 0;
}