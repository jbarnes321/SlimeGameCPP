#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"

class Player : public GameObject
{
	public:

		enum attackState
        {
            START = 0,
            POISON,
            FIRE,
            ICE,
            GHOST,
            NECRO,
            ELECTRIC,
            EARTH
        } currentAttackState;

		Player();
		Player(sf::Vector2f position, sf::Clock sfClock);
		~Player() {};

		void LoadContent();
		void Update(sf::Event event);
		void Draw(sf::RenderWindow &window);

	private:
		AnimationPlayer spritePlayer;

		Animation slimeStart;
		Animation slimePoison;
		Animation slimeFire;
		Animation slimeIce;
		Animation slimeGhost;
		Animation slimeNecro;
		Animation slimeElectric;
		Animation slimeEarth;
		Animation slimeInvisible;
		Animation currentSlimeAnimation;

		sf::Texture slimeStartTexture;
		sf::Texture slimePoisonTexture;
		sf::Texture slimeFireTexture;
		sf::Texture slimeIceTexture;
		sf::Texture slimeGhostTexture;
		sf::Texture slimeNecroTexture;
		sf::Texture slimeElectricTexture;
		sf::Texture slimeEarthTexture;
		sf::Texture slimeInvisibleTexture;

		sf::Texture healthContainerTexture;
		sf::Texture healthBallTexture;
		sf::Texture shieldBallTexture;

		sf::Texture manaBarOutlineTexture;
		sf::Texture manaBarFillTexture;
		sf::Sprite manaBarOutlineSprite;
		sf::Sprite manaBarFillSprite;

		sf::Texture keyCountTexture;
		sf::Texture xpCountTexture;
		sf::Sprite keyCountSprite;
		sf::Sprite xpCountSprite;

		sf::Text keyCountText;
		sf::Text xpCountText;
		sf::Font keyFont;

		sf::Texture guiElementOutlineTexture;
		sf::Sprite guiElementOutlineSprite;
		sf::Texture guiElementsTexture;
		sf::Sprite guiElementsSprite;
		sf::Texture guiCurrentElementTexture;
		sf::Sprite guiCurrentElementSprite;

		int maxHealth;
		int currentHealth;
		int currentShield;
		float normalMoveSpeed;

		float maxMana;
		float currentMana;
		int currentKeys;
		int currentXP;
		bool hasBossKey;

		bool hasPoison, hasFire, hasIce, hasGhost, hasNecro, hasElectric, hasEarth;
        sf::Vector2f poisonPos, firePos, icePos, ghostPos, necroPos, elePos, earthPos;
        sf::Vector2f nextElementPos;
		sf::Keyboard::Key poisonKey, fireKey, iceKey, ghostKey, necroKey, electricKey, earthKey;
        int nextKey;

		bool isInvisible;
		sf::Time invisibleTimer;
};


#endif // PLAYER_H_INCLUDED