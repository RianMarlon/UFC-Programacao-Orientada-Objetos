#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

struct Pencil {
  sf::Font font;
  sf::Text text;
  sf::RenderWindow& window;

  Pencil(sf::RenderWindow& window) : window { window } {
    if (!font.loadFromFile("./fonts/Roboto-Medium.ttf")) {
      std::cout << "Font not loaded\n";
    }

    text.setFont(font);
  }

  void write(std::string str, int x, int y, int size, sf::Color color) {
    text.setString(str);
    text.setCharacterSize(size);
    text.setPosition(x, y);
    text.setFillColor(color);
    window.draw(text);
  }
};

struct Bubble {
  int x;
  int y;
  char letter;
  int speed;
  bool alive { true };

  static const int radius { 10 };

  Bubble(int x, int y, char letter, int speed) : x { x }, y { y }, letter { letter }, speed { speed } {}

  void update() {
    this->y += this->speed;
  }

  void draw(sf::RenderWindow& window) {
    sf::CircleShape bubble(Bubble::radius);
    bubble.setPosition(x, y);
    bubble.setFillColor(sf::Color::White);
    window.draw(bubble);

    static Pencil pencil(window);
    pencil.write(std::string(1, letter), x + 0.4 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Blue);
  }
};

struct Board {
  std::vector<Bubble> bubbles;
  sf::RenderWindow& window;
  Pencil pencil;

  int hits { 0 };
  int misses { 0 };

  Board(sf::RenderWindow& window) : window { window }, pencil { window } {
    bubbles.push_back(Bubble(100, 100, 'A', 1));
    bubbles.push_back(Bubble(200, 100, 'B', 2));
    bubbles.push_back(Bubble(300, 100, 'C', 3));
  }

  void update() {
    if (this->checkNewBubble()) {
      this-> addNewBubble();
    } else {
      for (Bubble& bubble : bubbles) {
        bubble.update();
      }

      this->markOutsideBubbles();
      this->removeDeadBubbles();
    }
  }

  void addNewBubble() {
    int x = rand() % (this->window.getSize().x - 2 * Bubble::radius);
		int y = -2 * Bubble::radius;
		int speed = rand() % 7 + 3;
		char letter = rand() % 26 + 'A';

		bubbles.push_back(Bubble(x, y, letter, speed));
  }

  void markOutsideBubbles() {
    for (Bubble& bubble : bubbles) {
      if (bubble.y + 2 * Bubble::radius > (int) this->window.getSize().y) {
        if (bubble.alive) {
          bubble.alive = false;
          this->misses++;
        }
      }
    }
  }

  void markByHit(char letter) {
    for (Bubble& bubble : bubbles) {
      if (bubble.alive) {
        if (bubble.letter == letter) {
          bubble.alive = false;
          this->hits++;
          break;
        }
      }
    }
  }

  bool checkNewBubble() {
    static const int newBubbleTimeout { 30 };
    static int newBubbleTimer { 0 };

    newBubbleTimer--;
    if (newBubbleTimer <= 0) {
      newBubbleTimer = newBubbleTimeout;
      return true;
    }

    return false;
  }

  void removeDeadBubbles() {
    std::vector<Bubble> bubblesAlive;

    for (Bubble& bubble : bubbles) {
      if (bubble.alive) {
        bubblesAlive.push_back(bubble);
      }
    }

    this->bubbles = bubblesAlive;
  }

  void draw() {
    pencil.write("Hits: " + std::to_string(this->hits) + " Misses: " + std::to_string(this->misses), 10, 10, 20, sf::Color::White);
    pencil.write("Size: " + std::to_string(this->bubbles.size()), 10, 40, 20, sf::Color::White);
    for (Bubble& bubble : bubbles) {
      bubble.draw(window);
    }
  }
};

struct Game {
  sf::RenderWindow window;
  Board board;
  std::function<void()> onUpdate;

  Game() : window(sf::VideoMode(800, 600), "Bubbles"), board(window) {
    this->onUpdate = [&]() {
      this->gameplay();
    };
    window.setFramerateLimit(30);
  }

  void processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::TextEntered) {
        char code = static_cast<char>(event.text.unicode);
        code = toupper(code);
        board.markByHit(code);
      }
    }
  }

  void gameplay() {
    board.update();
    window.clear(sf::Color::Black);
    board.draw();
    window.display();

    if (board.misses >= 5) {
      this->onUpdate = [&]() {
        this->gameover();
      };
    }
  }

  void gameover() {
    window.clear(sf::Color::Red);
    static Pencil pencil(window);

    pencil.write("Game Over", 300, 250, 50, sf::Color::Black);

    window.display();
  }

  void mainLoop() {
    while (window.isOpen()) {
      processEvents();
      this->onUpdate();
    }
  }
};

int main() {
  Game game;
  game.mainLoop();

  return 0;
}