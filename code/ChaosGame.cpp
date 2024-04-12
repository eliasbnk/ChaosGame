#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 675;
const int MAX_POINTS = 40000;
const int VERTEX_RADIUS = 5;
const int POINT_SIZE = 2;
const int FONT_SIZE = 20;
const sf::Color VERTEX_COLOR = sf::Color::Blue;
const sf::Color POINT_COLOR = sf::Color::Yellow;
const sf::Color INSTRUCTION_COLOR = sf::Color::White;
const std::string FONT_FILE = "KOMIKAP_.ttf";
const int NUMBER_VERTICES = 3;
const sf::Vector2f STARTING_POSITION(20, 20);
const std::string GAME_NAME = "Chaos Game!!";
const int POINT_DRAW_SPEED = 75; //lower is faster

class Game {
protected:
    sf::RenderWindow window;
    std::vector<sf::Vector2f> vertices;
    std::vector<sf::Vector2f> points;
    sf::Font font;
    sf::Text instructions;
    std::mt19937 randomEngine;

public:
    Game() : randomEngine(std::random_device()()) { 
        try {
            if (!font.loadFromFile(FONT_FILE)) {
                throw std::runtime_error("Failed to load font");
            }
        } catch (const std::exception& e) {
            handleException(e);
        }

        instructions.setFont(font);
        instructions.setString("Click on any three points on the screen\nto create the vertices for the triangle.");
        instructions.setCharacterSize(FONT_SIZE);
        instructions.setFillColor(INSTRUCTION_COLOR);
        instructions.setPosition(STARTING_POSITION);
    }

    virtual ~Game() {}

    virtual void run() {
        if (!window.isOpen()) {
            handleException(std::runtime_error("Failed to create window"));
            return;
        }
        while (window.isOpen()) {
            handleEvents();
            update();
            draw();
        }
    }

protected:
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    void handleException(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        window.close();
    }

    void drawVertices() {
        for (const auto &vertex : vertices) {
            sf::CircleShape circle(VERTEX_RADIUS);
            circle.setFillColor(VERTEX_COLOR);
            circle.setPosition(vertex);
            window.draw(circle);
        }
    }

    void drawPoints() {
        for (const auto &point : points) {
            sf::RectangleShape rect(sf::Vector2f(POINT_SIZE, POINT_SIZE));
            rect.setPosition(point);
            rect.setFillColor(POINT_COLOR);
            window.draw(rect);
        }
    }

    void drawMidpoints(int points_to_draw) {
        std::uniform_int_distribution<int> distribution(0, NUMBER_VERTICES - 1);
        for (int i = 0; i < points_to_draw; i++) {
            int vert = distribution(randomEngine); 
            sf::Vector2f newPoint;
            newPoint.x = (vertices[vert].x + points.back().x) / 2;
            newPoint.y = (vertices[vert].y + points.back().y) / 2;
            points.push_back(newPoint);
        }
    }
};

class ChaosGame : public Game {
public:
    ChaosGame() : Game() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
        if (!window.isOpen()) {
            handleException(std::runtime_error("Failed to create window"));
        }
    }

    void run() override {
        Game::run();
    }

protected:
    void handleEvents() override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }

    void handleMouseClick(float mouseX, float mouseY) {
        if (vertices.size() < NUMBER_VERTICES) {
            vertices.push_back(sf::Vector2f(mouseX, mouseY));
            if (vertices.size() == NUMBER_VERTICES) {
                instructions.setString("Click on a fourth point\nto start the algorithm.");
            }
        } else if (points.size() < 1) {
            points.push_back(sf::Vector2f(mouseX, mouseY));
        }
    }

    void update() override {
        if (points.size() > 0 && points.size() < MAX_POINTS) {
            instructions.setString("Drawing Midpoints...");
            int points_to_draw = points.size() / POINT_DRAW_SPEED + 1; 
            drawMidpoints(points_to_draw);
            std::cout << points.size() << " Total points rendered\n";
        }
        if (points.size() >= MAX_POINTS) {
            instructions.setString("Simulation Complete!");
        }
    }

    void draw() override {
        window.clear();
        drawVertices();
        drawPoints();
        window.draw(instructions);
        window.display();
    }
};

int main() {
    ChaosGame game;
    game.run();
    return 0;
}
