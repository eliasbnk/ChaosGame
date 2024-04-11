#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

class ChaosGame {
private:
    RenderWindow window;
    vector<Vector2f> vertices;
    vector<Vector2f> points;
    Font font;
    Text instructions;

public:
    ChaosGame() : window(VideoMode(800, 600), "Chaos Game!!") {
        if (!font.loadFromFile("KOMIKAP_.ttf")) {
            cerr << "Failed to load font" << endl;
        }
        instructions.setFont(font);
        instructions.setString("Click on any three points on the screen to create the vertices for the triangle.");
        instructions.setCharacterSize(20);
        instructions.setFillColor(Color::White);
        instructions.setPosition(20, 20);
    }

    void run() {
        srand(time(0));

        while (window.isOpen()) {
            handleEvents();
            update();
            draw();
        }
    }

private:
    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }

    void handleMouseClick(float mouseX, float mouseY) {
        if (vertices.size() < 3) {
            vertices.push_back(Vector2f(mouseX, mouseY));
            if (vertices.size() == 3) {
                instructions.setString("Click on a fourth point to start the algorithm.");
            }
        } else if (points.empty()) {
            points.push_back(Vector2f(mouseX, mouseY));
        }
    }

    void update() {
        if (points.size() > 0 && points.size() < 100000) {
            for (int i = 0; i < 100; i++) {
                int vert = rand() % 3;

                Vector2f newPoint;
                newPoint.x = (vertices[vert].x + points.back().x) / 2;
                newPoint.y = (vertices[vert].y + points.back().y) / 2;
                points.push_back(newPoint);
            }
        }
    }

    void draw() {
        window.clear();


        for (const auto& vertex : vertices) {
            CircleShape circle(5);
            circle.setFillColor(Color::Blue);
            circle.setPosition(vertex);
            window.draw(circle);
        }

        for (const auto& point : points) {
            RectangleShape rect(Vector2f(1, 1));
            rect.setPosition(point);
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }

        window.draw(instructions);

        window.display();
    }
};

int main() {
    ChaosGame game;
    game.run();
    return 0;
}
