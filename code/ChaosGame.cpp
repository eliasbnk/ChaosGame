// // Include important C++ libraries here
// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
// #include <iostream>
// #include <sstream>
// #include <vector>

// // Make code easier to type with "using namespace"
// using namespace sf;
// using namespace std;

// int main()
// {
//     // Create a video mode object
// 	VideoMode vm(1920, 1080);
// 	// Create and open a window for the game
// 	RenderWindow window(vm, "Timber Game!!", Style::Default);

//     vector<Vector2f> vertices;
//     vector<Vector2f> points;

// 	while (window.isOpen())
// 	{
//         /*
// 		****************************************
// 		Handle the players input
// 		****************************************
// 		*/
//         Event event;
// 		while (window.pollEvent(event))
// 		{
//             if (event.type == Event::Closed)
//             {
// 				// Quit the game when the window is closed
// 				window.close();
//             }
//             if (event.type == sf::Event::MouseButtonPressed)
//             {
//                 if (event.mouseButton.button == sf::Mouse::Left)
//                 {
//                     std::cout << "the left button was pressed" << std::endl;
//                     std::cout << "mouse x: " << event.mouseButton.x << std::endl;
//                     std::cout << "mouse y: " << event.mouseButton.y << std::endl;

//                     if(vertices.size() < 3)
//                     {
//                         vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
//                     }
//                     else if(points.size() == 0)
//                     {
//                         ///fourth click
//                         ///push back to points vector
//                     }
//                 }
//             }
//         }
//         if (Keyboard::isKeyPressed(Keyboard::Escape))
// 		{
// 			window.close();
// 		}
//         /*
// 		****************************************
// 		Update
// 		****************************************
// 		*/

//         if(points.size() > 0)
//         {
//             ///generate more point(s)
//             ///select random vertex
//             ///calculate midpoint between random vertex and the last point in the vector
//             ///push back the newly generated coord.
//         }

//         /*
// 		****************************************
// 		Draw
// 		****************************************
// 		*/
//         window.clear();
//         for(int i = 0; i < vertices.size(); i++)
//         {
//             RectangleShape rect(Vector2f(10,10));
//             rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
//             rect.setFillColor(Color::Blue);
//             window.draw(rect);
//         }
//         window.display();
//     }
// }

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

// Function to calculate midpoint
Vector2f midpoint(const Vector2f& p1, const Vector2f& p2) {
    return Vector2f((p1.x + p2.x) / 2.f, (p1.y + p2.y) / 2.f);
}

// Function to generate points for the fractal
void generatePoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
    if (vertices.size() != 3) return;

    // Clear existing points
    points.clear();

    // Start with the fourth point as the first vertex
    points.push_back(vertices[3]);

    // Generate more points using the midpoint displacement algorithm
    for (size_t i = 0; i < points.size(); ++i) {
        // Select a random vertex
        int randomVertexIndex = rand() % 3;
        Vector2f randomVertex = vertices[randomVertexIndex];

        // Calculate midpoint between random vertex and the last point in the vector
        Vector2f mid = midpoint(randomVertex, points.back());

        // Add a new point displaced slightly from the midpoint
        float displacement = 10.f; // Adjust displacement factor as needed
        float angle = (float)(rand() % 360) * 3.14159265359f / 180.f;
        float offsetX = cos(angle) * displacement;
        float offsetY = sin(angle) * displacement;
        points.push_back(mid + Vector2f(offsetX, offsetY));
    }
}

int main() {
    // Create a video mode object
    VideoMode vm(800, 600);
    // Create and open a window for the game
    RenderWindow window(vm, "Fractal Triangle", Style::Default);

    // Load font
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
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

    int clickCount = 0; // Keep track of mouse click count

    while (window.isOpen()) {
        // Handle events
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

                        // If all three vertices are chosen, prompt for the fourth point
                        if (clickCount == 3) {
                            instructionText.setString("Click on a fourth point to start the algorithm");
                        }
                    }
                    else if (clickCount == 3) {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        clickCount++;

                        // Generate points for the fractal
                        generatePoints(points, vertices);
                    }
                }
            }
        }

        // Draw everything
        window.clear();
        window.draw(instructionText);

        // Draw vertices
        for (const auto& vertex : vertices) {
            CircleShape circle(5.f);
            circle.setFillColor(Color::Blue);
            circle.setPosition(vertex);
            window.draw(circle);
        }

        // Draw points
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
