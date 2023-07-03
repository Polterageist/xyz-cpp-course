// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <cstdlib>

const std::string RESOURCES_PATH = "Resources/";

// Game settings constants
const float PLAYER_SIZE = 20.f;
const float APPLE_SIZE = 20.f;
const float INITIAL_SPEED = 100.f;
const float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
const int NUM_APPLES = 20;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEGHT = 600;


struct Vector2D
{
	float x = 0.f;
	float y = 0.f;
};

// usin Position = Vector2D;
typedef Vector2D Position;

enum class PlayerDirection
{
	Up = 0,
	Right,
	Down,
	Left
};

struct Player
{
	Position position;
	float speed = 0.f; // Pixels per second
	PlayerDirection direction = PlayerDirection::Up;
	sf::RectangleShape shape;
};

struct Apple
{
	Position position;
	sf::CircleShape shape;
};

struct GameState
{
	Player player;
	Apple apples[NUM_APPLES];
	int numEatenApples = 0;
	bool isGameOver = false;
};

void HandleWindowEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close window if close button or Escape key pressed
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void InitPlayer(Player& player)
{
	// Init player state
	player.position.x = (float)SCREEN_WIDTH / 2.f;
	player.position.y = (float)SCREEN_HEGHT / 2.f;
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Up;

	// Init player representation
	player.shape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.shape.setFillColor(sf::Color::Green);
	player.shape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	player.shape.setPosition(player.position.x, player.position.y);
}

void InitApple(Apple& apple)
{
	// init apple state
	apple.position.x = (float)(rand() % SCREEN_WIDTH);
	apple.position.y = (float)(rand() % SCREEN_HEGHT);

	// Init apple representation
	apple.shape.setRadius(APPLE_SIZE / 2.f);
	apple.shape.setFillColor(sf::Color::Red);
	apple.shape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	apple.shape.setPosition(apple.position.x, apple.position.y);
}

void InitGame(GameState& gameState)
{
	// Init player
	InitPlayer(gameState.player);
	// Init apples
	for (int i = 0; i < NUM_APPLES; i++)
	{
		InitApple(gameState.apples[i]);
	}

	// Init game state
	gameState.numEatenApples = 0;
	gameState.isGameOver = false;
}

void HandleInput(GameState& gameState)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		gameState.player.direction = PlayerDirection::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gameState.player.direction = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		gameState.player.direction = PlayerDirection::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gameState.player.direction = PlayerDirection::Left;
	}
}

void UpdatePlayer(Player& player, float timeDelta)
{
	// Move player
	if (player.direction == PlayerDirection::Up)
	{
		player.position.y -= player.speed * timeDelta;
	}
	else if (player.direction == PlayerDirection::Right)
	{
		player.position.x += player.speed * timeDelta;
	}
	else if (player.direction == PlayerDirection::Down)
	{
		player.position.y += player.speed * timeDelta;
	}
	else if (player.direction == PlayerDirection::Left)
	{
		player.position.x -= player.speed * timeDelta;
	}
}

bool HasPlayerCollisionWithScreenBorder(const Player& player)
{
	return (player.position.x - PLAYER_SIZE / 2.f < 0) ||
		(player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH) ||
		(player.position.y - PLAYER_SIZE / 2.f < 0) ||
		(player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEGHT);
}

bool HasPlayerCollisionWithApple(const Player& player, const Apple& apple)
{
	float dx = player.position.x - apple.position.x;
	float dy = player.position.y - apple.position.y;
	float distance = sqrt(dx * dx + dy * dy);
	return distance < (PLAYER_SIZE + APPLE_SIZE) / 2.f;
}

void UpdateGame(GameState& gameState, float timeDelta)
{
	// Update player
	UpdatePlayer(gameState.player, timeDelta);

	// Check collision with screen border
	if (HasPlayerCollisionWithScreenBorder(gameState.player))
	{
		gameState.isGameOver = true;
		return;
	}

	for (int i = 0; i < NUM_APPLES; i++)
	{
		// Check collision with apple
		if (HasPlayerCollisionWithApple(gameState.player, gameState.apples[i]))
		{
			// Move apple to a new random position
			InitApple(gameState.apples[i]);
			// Increase eaten apples counter
			gameState.numEatenApples++;
			// Increase player speed
			gameState.player.speed += ACCELERATION;
		}
	}
}

void DrawGame(GameState& gameState, sf::RenderWindow& window)
{
	// Draw player
	window.draw(gameState.player.shape);
	// Draw apples
	for (int i = 0; i < NUM_APPLES; i++)
	{
		window.draw(gameState.apples[i].shape);
	}
}


int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEGHT), "AppleGame");

	GameState gameState;
	InitGame(gameState);

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

	// Game loop
	while (window.isOpen())
	{
		// Calculate time delta
		sf::Time currentTime = game_clock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;

		HandleWindowEvents(window);
		if (!window.isOpen())
		{
			return 0;
		}

		HandleInput(gameState);
		UpdateGame(gameState, timeDelta);

		// Draw everything here
		// Clear the window first
		window.clear();

		DrawGame(gameState, window);

		// End the current frame, display window contents on screen
		window.display();

		if (gameState.isGameOver)
		{
			// Here we restart the game
			InitGame(gameState);
		}
	}

	return 0;
}
