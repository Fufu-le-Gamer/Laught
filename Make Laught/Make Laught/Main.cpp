#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "Button.h"
#include "EventManager.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Le jeu du pif");
	window.setFramerateLimit(60);

	sf::Shader invertShader;
	if (!invertShader.loadFromFile("asset/invert.frag", sf::Shader::Type::Fragment)) {
		std::cerr << "Erreur : Impossible de charger le shader !" << std::endl;
	}

	sf::Texture duckTexture;
	if (!duckTexture.loadFromFile("asset/duck.png"))
		return -1;

	sf::Sprite duckSprite(duckTexture);
	duckSprite.setOrigin({ duckTexture.getSize().x / 2.f, duckTexture.getSize().y / 2.f });
	duckSprite.setPosition({ 200.f, 400.f });
	sf::SoundBuffer duckBuff;
	if (!duckBuff.loadFromFile("sound/Duck.mp3"))
		return -1;
	sf::Sound duckSound(duckBuff);
	float duckX = -100.f;
	float duckSpeed = 500.f;

	sf::Texture charlesTexture;
	if (!charlesTexture.loadFromFile("asset/Charles.png"))
		return -1;
	sf::Sprite charlesSprite(charlesTexture);
	charlesSprite.setOrigin({ charlesTexture.getSize().x / 2.f, charlesTexture.getSize().y / 2.f });
	charlesSprite.setPosition({ 600.f, 200.f });
	float charlesY = -100.f;
	float charlesSpeed = 80.f;

	sf::SoundBuffer charlesBuff;
	if (!charlesBuff.loadFromFile("sound/Charles.mp3"))
		return -1;
	sf::Sound charlesSound(charlesBuff);


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

	sf::Texture catTexture;
	if (!catTexture.loadFromFile("asset/cat.png"))
		return -1;
	sf::Sprite catSprite(catTexture);
	catSprite.setOrigin({ catTexture.getSize().x / 2.f, catTexture.getSize().y / 2.f });
	catSprite.setPosition({ 600.f, 500.f });
	sf::SoundBuffer catBuff;
	if (!catBuff.loadFromFile("sound/constante.mp3"))
		return -1;
	sf::Sound catSound(catBuff);

	sf::Texture pandariaTexture;
	pandariaTexture.loadFromFile("asset/Pandaria.png");
	sf::Sprite pandariaSprite(pandariaTexture);
	pandariaSprite.setOrigin({ pandariaTexture.getSize().x / 2.f, pandariaTexture.getSize().y / 2.f });
	pandariaSprite.setPosition({ 400.f, 300.f });

	sf::SoundBuffer pandariaBuff;
	pandariaBuff.loadFromFile("sound/Foule.mp3");
	sf::Sound pandariaSound(pandariaBuff);

	sf::SoundBuffer fartBuff;
	if (!fartBuff.loadFromFile("sound/Fart.mp3"))
		return -1;
	sf::Sound fartSound(fartBuff);

	sf::SoundBuffer internalBuff;
	if (!internalBuff.loadFromFile("sound/Internal.ogg"))
		return -1;
	sf::Sound internalSound(internalBuff);

	sf::Texture macronTexture;
	if (!macronTexture.loadFromFile("asset/Macron.jpg"))
		return -1;
	sf::Sprite macronSprite(macronTexture);
	macronSprite.setOrigin({ macronTexture.getSize().x / 2.f, macronTexture.getSize().y / 2.f });
	macronSprite.setPosition({ 400.f, 300.f });

	sf::SoundBuffer macronBuff;
	if (!macronBuff.loadFromFile("sound/Macron.mp3"))
		return -1;
	sf::Sound macronSound(macronBuff);

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

		if (isPressingE && collision && !wasKeyPressed && !eventMana.isEventRunning()) {
			eventMana.triggerRandomEvent(player);
			if (eventMana.isScreamer())
				screamSound.play();
			if (eventMana.isPandaria())
				pandariaSound.play();
			if (eventMana.isFart())
				fartSound.play();
			if (eventMana.isMacron())
				macronSound.play();
			if (eventMana.isInternal())
				internalSound.play();
			if (eventMana.isCharles())
			{
				charlesY = -200.f;
				charlesSound.play();
			}
			if (eventMana.isDuck())
			{
				duckX = -200.f;
				duckSound.setPitch(3.0f);
				duckSound.play();
			}

			if (eventMana.isCat())
			{
				catSound.play();
			}

			wasKeyPressed = true;     // Marqueur pour ne changer qu'une fois par pression
		}
		if (!isPressingE) {
			wasKeyPressed = false;    // On reset quand on relâche la touche
		}
		if (eventMana.isDuck()) {
			duckX += duckSpeed * dt;
			duckSprite.setPosition({ duckX, 400.f });
		}
		if (eventMana.isCharles()) {
			if (charlesY < 300.f) {
				charlesY += charlesSpeed * dt;
				charlesSprite.setPosition({ 400.f, charlesY });
			}
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
		if (eventMana.isMacron()) {
			window.draw(macronSprite);
		}
		if (eventMana.isCharles()) {
			window.draw(charlesSprite);
		}
		if (eventMana.isCat()) {
			window.draw(catSprite);
		}
		if (eventMana.isDuck()) {

			duckSprite.setScale({ 4.f, 4.f });
			window.draw(duckSprite);
		}
		window.display();
	}
	return 0;
}
