#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

Vector2f midpoint(const Vector2f& p1, const Vector2f& p2) {
    return Vector2f((p1.x + p2.x) / 2.f, (p1.y + p2.y) / 2.f);
}


void generatePoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
    if (vertices.size() != 3) return;

 
    for (size_t i = 0; i < 50; ++i) {
      
        int randomVertexIndex = rand() % 3;
        Vector2f randomVertex = vertices[randomVertexIndex];

        Vector2f mid = midpoint(randomVertex, points.back());


        points.push_back(mid); 
    }
}

int main() {
   
    VideoMode vm(800, 600);
    
    RenderWindow window(vm, "Fractal Triangle", Style::Default);

   
    Font font;
    if (!font.loadFromFile("KOMIKAP_.ttf")) {
        cerr << "Failed to load font" << endl;
        return EXIT_FAILURE;
    }

    Text instructionText;
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(Color::White);
    instructionText.setString("Click on any three points to create vertices for the triangle");
    instructionText.setPosition(10.f, 10.f);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    int clickCount = 0;

    while (window.isOpen()) {
 
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (clickCount < 3) {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        clickCount++;

                        if (clickCount == 3) {
                            instructionText.setString("Click on a fourth point to start the algorithm");
                        }
                    }
                    else if (clickCount == 3) {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        clickCount++;

                    }
                }
            }
        }


        generatePoints(points, vertices);



        window.clear();
        window.draw(instructionText);


        for (const auto& vertex : vertices) {
            CircleShape circle(5.f);
            circle.setFillColor(Color::Blue);
            circle.setPosition(vertex);
            window.draw(circle);
        }


        for (const auto& point : points) {
            CircleShape circle(2.f);
            circle.setFillColor(Color::Red);
            circle.setPosition(point);
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}
