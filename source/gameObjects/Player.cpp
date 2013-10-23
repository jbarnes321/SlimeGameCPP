#include "Player.h"

Player::Player()
	:GameObject() {}

Player::Player(sf::Vector2f pos, sf::Clock sfClock)
	: GameObject(pos, sfClock)
{
	position = pos;
	origin = sf::Vector2f(25, 25);
	assetDir = "assets/player/";

	body = Body(position, sf::Vector2f(0, 0), sf::Vector2f(0, 0), Body::PLAYER, 40, 40, 0);

	//player's initial health
    maxHealth = 3;
    currentHealth = maxHealth;
    currentShield = currentHealth;

	//player's initial consumable values
    maxMana = 100;
    currentMana = maxMana;
	currentKeys = 1;
	currentXP = 0;
	hasBossKey = false;

	//player's initial stats
	currentAttackState = START;
	normalMoveSpeed = 4.75f;

	hasPoison = false;
    hasFire = false;
    hasIce = true;
    hasGhost = false;
    hasNecro = true;
    hasElectric = false;
    hasEarth = false;
    nextElementPos = sf::Vector2f(450, 5);
    nextKey = 0;
	isInvisible = false;
	invisibleTimer = sf::seconds(0);

	//set default values for gui Elements
	poisonPos = sf::Vector2f(450, 5);
    firePos = sf::Vector2f(490, 5);
    icePos = sf::Vector2f(530, 5);
    ghostPos = sf::Vector2f(570, 5);
    necroPos = sf::Vector2f(610, 5);
    elePos = sf::Vector2f(650, 5);
    earthPos = sf::Vector2f(690, 5);

	poisonKey = sf::Keyboard::Num1;
    fireKey = sf::Keyboard::Num2;
    iceKey = sf::Keyboard::Num3;
    ghostKey = sf::Keyboard::Num4;
    necroKey = sf::Keyboard::Num5;
    electricKey = sf::Keyboard::Num6;
    earthKey = sf::Keyboard::Num7;;

}


void Player::LoadContent()
{
	//slime elemental textures
	if(!slimeStartTexture.loadFromFile(assetDir + "slimeStartSheet.png"))
		return;
	if(!slimePoisonTexture.loadFromFile(assetDir + "slimePoisonSheet.png"))
		return;
	if(!slimeFireTexture.loadFromFile(assetDir + "slimeFireSheet.png"))
		return;
	if(!slimeIceTexture.loadFromFile(assetDir + "slimeIceSheet.png"))
		return;
	if(!slimeGhostTexture.loadFromFile(assetDir + "slimeGhostSheet.png"))
		return;
	if(!slimeNecroTexture.loadFromFile(assetDir + "slimeNecroSheet.png"))
		return;
	if(!slimeElectricTexture.loadFromFile(assetDir + "slimeElectricSheet.png"))
		return;
	if(!slimeEarthTexture.loadFromFile(assetDir + "slimeEarthSheet.png"))
		return;
	if(!slimeInvisibleTexture.loadFromFile(assetDir + "slimeInvisible.png"))
		return;

	slimeStart = Animation::Animation(slimeStartTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimePoison = Animation::Animation(slimePoisonTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeFire = Animation::Animation(slimeFireTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeIce = Animation::Animation(slimeIceTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeGhost = Animation::Animation(slimeGhostTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeNecro = Animation::Animation(slimeNecroTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeElectric = Animation::Animation(slimeElectricTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeEarth = Animation::Animation(slimeEarthTexture, sf::seconds(0.19f), true, 4, 4, 0);
	slimeInvisible = Animation::Animation(slimeInvisibleTexture, sf::seconds(0.19f), true, 1, 1, 0);

	currentSlimeAnimation = slimeStart;
	

	//HUD Textures
	if(!healthContainerTexture.loadFromFile("assets/gui/healthContainer.png"))
		return;
	if(!healthBallTexture.loadFromFile("assets/gui/healthBall.png"))
		return;
	if(!shieldBallTexture.loadFromFile("assets/gui/shield.png"))
		return;
	if(!manaBarOutlineTexture.loadFromFile("assets/gui/manaBar.png"))
		return;
	if(!manaBarFillTexture.loadFromFile("assets/gui/manaBarFill.png"))
		return;
	

	manaBarOutlineSprite.setTexture(manaBarOutlineTexture);
	manaBarOutlineSprite.setPosition(200, 10);
	manaBarFillSprite.setTexture(manaBarFillTexture);
	manaBarFillSprite.setPosition(200, 10);

	if(!keyCountTexture.loadFromFile("assets/pickups/key.png"))
		return;
	if(!xpCountTexture.loadFromFile("assets/pickups/xp.png"))
		return;
	if (!keyFont.loadFromFile("assets/arial.ttf"))
		return;


	keyCountSprite.setTexture(keyCountTexture);
	keyCountSprite.setPosition(375, 5);
	xpCountSprite.setTexture(xpCountTexture);
	xpCountSprite.setPosition(380, 36);

	keyCountText.setFont(keyFont);
	keyCountText.setPosition(400, 8);
	keyCountText.setCharacterSize(12);
	xpCountText.setFont(keyFont);
	xpCountText.setPosition(400, 32);
	xpCountText.setCharacterSize(12);

	if(!guiElementOutlineTexture.loadFromFile("assets/gui/guiElementOutline.png"))
		return;
	if(!guiElementsTexture.loadFromFile("assets/gui/guiElements.png"))
		return;
	if(!guiCurrentElementTexture.loadFromFile("assets/gui/guiCurrentElement.png"))
		return;

	guiElementOutlineSprite.setTexture(guiElementOutlineTexture);
	guiElementOutlineSprite.setPosition(450, 5);
	guiElementsSprite.setTexture(guiElementsTexture);
	guiCurrentElementSprite.setTexture(guiCurrentElementTexture);
	guiCurrentElementSprite.setPosition(450, 5);

}

void Player::Update(sf::Event event)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        body.applyForce(-normalMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        body.applyForce(normalMoveSpeed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        body.applyForce(0, -normalMoveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        body.applyForce(0, normalMoveSpeed);

    position = body.position;

	//change slime's attack state
    if (sf::Keyboard::isKeyPressed(poisonKey) && hasPoison)    //poison
    {
		currentAttackState = POISON;
		currentSlimeAnimation = slimePoison;

    }
    else if (sf::Keyboard::isKeyPressed(fireKey) && hasFire)   //fire
    {
        currentAttackState = FIRE;
		currentSlimeAnimation = slimeFire;
    }
    else if (sf::Keyboard::isKeyPressed(iceKey) && hasIce)   //ice
    {
        currentAttackState = ICE;
		currentSlimeAnimation = slimeIce;
    }
    else if (sf::Keyboard::isKeyPressed(ghostKey) && hasGhost)   //ghost
    {
        currentAttackState = GHOST;
		currentSlimeAnimation = slimeGhost;
    }
    else if (sf::Keyboard::isKeyPressed(necroKey) && hasNecro)   //necro
    {
        currentAttackState = NECRO;
		currentSlimeAnimation = slimeNecro;
    }
    else if (sf::Keyboard::isKeyPressed(electricKey) && hasElectric)   //electric
    {
        currentAttackState = ELECTRIC;
		currentSlimeAnimation = slimeElectric;
    }
    else if (sf::Keyboard::isKeyPressed(earthKey) && hasEarth)   //earth
    {
        currentAttackState = EARTH;
		currentSlimeAnimation = slimeEarth;
    }
	else if (isInvisible && invisibleTimer > sf::seconds(0))
		currentSlimeAnimation = slimeInvisible;
	else if (isInvisible && invisibleTimer <= sf::seconds(0))
		currentSlimeAnimation = slimeGhost;

	spritePlayer.PlayAnimation(currentSlimeAnimation);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //Fire(new Vector2(0, -1));
        currentSlimeAnimation.currentRow = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //Fire(new Vector2(0, 1));
        currentSlimeAnimation.currentRow = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //Fire(new Vector2(-1, 0));
        currentSlimeAnimation.currentRow = 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //Fire(new Vector2(1, 0));
        currentSlimeAnimation.currentRow = 2;
    }
    else
		currentSlimeAnimation.currentRow = 0;

}

void Player::Draw(sf::RenderWindow &window)
{
	//draw the health containers
    int healthColumn = 0;
    for (int i = 0; i < maxHealth; i++)
    {
        if (i == 6)
            healthColumn = 0;
		sf::Sprite healthContainer(healthContainerTexture);
		healthContainer.setPosition(sf::Vector2f(healthColumn += 25.0, (i / 6 * 20.0) + 7));
		window.draw(healthContainer);
    }

    //draw the full health containers, 6 per row
    healthColumn = 0;
    for (int i = 0; i < currentHealth; i++)
    {
        if (i == 6)
            healthColumn = 0;

		sf::Sprite healthBall(healthBallTexture);
		healthBall.setPosition(sf::Vector2f(healthColumn += 25, (i / 6 * 20) + 7));
		window.draw(healthBall);
    }

    //draw the current shields, 6 per row. surrounds the health balls
    healthColumn = 0;
    for (int i = 0; i < currentShield; i++)
    {
        if (i == 6)
            healthColumn = 0;
		sf::Sprite shieldBall(shieldBallTexture);
		shieldBall.setPosition(sf::Vector2f(healthColumn += 25, (i / 6 * 20) + 7));
		window.draw(shieldBall);
    }

	//draw the mana bar
	manaBarFillSprite.setTextureRect(sf::IntRect(0, 0, (int)(maxMana * ((double)currentMana / maxMana)), 20));
	window.draw(manaBarFillSprite);
	window.draw(manaBarOutlineSprite);

	//draw key and xp count
	window.draw(keyCountSprite);
	window.draw(xpCountSprite);

	keyCountText.setString("x " + std::to_string(static_cast<long long>(currentKeys)));
	window.draw(keyCountText);

	xpCountText.setString("= " + std::to_string(static_cast<long long>(currentXP)));	
	window.draw(xpCountText);

	window.draw(guiElementOutlineSprite);

	//draw the elements
    if (hasPoison)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
		guiElementsSprite.setPosition(poisonPos);
		window.draw(guiElementsSprite);
	}
    if (hasFire)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
		guiElementsSprite.setPosition(firePos);
		window.draw(guiElementsSprite);
	}
    if (hasIce)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(80, 0, 40, 40));
		guiElementsSprite.setPosition(icePos);
		window.draw(guiElementsSprite);
	}
    if (hasGhost)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(120, 0, 40, 40));
		guiElementsSprite.setPosition(ghostPos);
		window.draw(guiElementsSprite);
	}
    if (hasNecro)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(160, 0, 40, 40));
		guiElementsSprite.setPosition(necroPos);
		window.draw(guiElementsSprite);
	}
    if (hasElectric)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(200, 0, 40, 40));
		guiElementsSprite.setPosition(elePos);
		window.draw(guiElementsSprite);
	}
    if (hasEarth)
	{
		guiElementsSprite.setTextureRect(sf::IntRect(240, 0, 40, 40));
		guiElementsSprite.setPosition(earthPos);
		window.draw(guiElementsSprite);
	}

	//draw the current element outline box
	if (currentAttackState == POISON && hasPoison)
		guiCurrentElementSprite.setPosition(poisonPos);		
    else if (currentAttackState == FIRE && hasFire)
        guiCurrentElementSprite.setPosition(firePos);
    else if (currentAttackState == ICE && hasIce)
        guiCurrentElementSprite.setPosition(icePos);
    else if (currentAttackState == GHOST && hasGhost)
        guiCurrentElementSprite.setPosition(ghostPos);
    else if (currentAttackState == NECRO && hasNecro)
        guiCurrentElementSprite.setPosition(necroPos);
    else if (currentAttackState == ELECTRIC && hasElectric)
        guiCurrentElementSprite.setPosition(elePos);
    else if (currentAttackState == EARTH && hasEarth)
        guiCurrentElementSprite.setPosition(earthPos);

	window.draw(guiCurrentElementSprite);

	//draw the player sprite
	spritePlayer.Draw(window, position, origin, clock);

	

}