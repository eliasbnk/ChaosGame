// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <vector>
// #include <cstdlib> // Include for rand() function
// #include <ctime> // Include for srand() function

// using namespace sf;
// using namespace std;

// Vector2f midpoint(const Vector2f& p1, const Vector2f& p2) {
//     return Vector2f((p1.x + p2.x) / 2.f, (p1.y + p2.y) / 2.f);
// }

// void generatePoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
//     if (vertices.size() != 3 || points.empty()) return;
    
//     for (size_t i = 0; i < 50; ++i) {
//         int randomVertexIndex = rand() % 3;
//         Vector2f randomVertex = vertices[randomVertexIndex];
//         Vector2f mid = midpoint(randomVertex, points.back());
//         points.push_back(mid);
//     }
// }

// int main() {
//     srand(static_cast<unsigned int>(time(NULL))); // Seed for rand()

//     VideoMode vm(800, 600);
//     RenderWindow window(vm, "Fractal Triangle", Style::Default);

//     Font font;
//     if (!font.loadFromFile("KOMIKAP_.ttf")) {
//         cerr << "Failed to load font" << endl;
//         return EXIT_FAILURE;
//     }

//     Text instructionText;
//     instructionText.setFont(font);
//     instructionText.setCharacterSize(24);
//     instructionText.setFillColor(Color::White);
//     instructionText.setString("Click on any three points to create vertices for the triangle");
//     instructionText.setPosition(10.f, 10.f);

//     vector<Vector2f> vertices;
//     vector<Vector2f> points;

//     int clickCount = 0;

//     while (window.isOpen()) {
//     Event event;
//     while (window.pollEvent(event)) {
//         if (event.type == Event::Closed) {
//             window.close();
//         }
//         else if (event.type == Event::MouseButtonPressed) {
//             if (event.mouseButton.button == Mouse::Left) {
//                 if (clickCount < 3) {
//                     vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
//                     clickCount++;

//                     if (clickCount == 3) {
//                         instructionText.setString("Click on a fourth point to start the algorithm");
//                     }
//                 }
//                 else if (clickCount == 3) {
//                     Vector2f startPoint(event.mouseButton.x, event.mouseButton.y);
//                     RectangleShape startShape(Vector2f(5.f, 5.f));
//                     startShape.setFillColor(Color::Green);
//                     startShape.setPosition(startPoint);
//                     window.draw(startShape);
//                     vertices.push_back(startPoint); // Add fourth point to vertices
//                     clickCount++;
//                     instructionText.setString("Generating fractal...");
//                 }
//                 else {
//                     // After the fourth point is placed, no more points are added on click
//                 }
//             }
//         }
//     }

//     // Generate points only after the fourth point is placed
//     if (clickCount > 3) {
//         generatePoints(points, vertices);
//     }

//         window.clear();
//         window.draw(instructionText);

//         for (const auto& vertex : vertices) {
//             CircleShape circle(5.f);
//             circle.setFillColor(Color::Blue);
//             circle.setPosition(vertex);
//             window.draw(circle);
//         }

//         for (const auto& point : points) {
//             CircleShape circle(2.f);
//             circle.setFillColor(Color::Red);
//             circle.setPosition(point);
//             window.draw(circle);
//         }

//         window.display();
//     }

//     return 0;
// }

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(800, 600);
	// Create and open a window for the game
	RenderWindow window(vm, "Fractal Triangle", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Random number generator for selecting vertices
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 2);

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "Mouse clicked at: " << event.mouseButton.x << ", " << event.mouseButton.y << endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        // Fourth click - initialize with user's click
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            // Generate more points
            // Select a random vertex
            int vertexIndex = distribution(generator);
            Vector2f selectedVertex = vertices[vertexIndex];
            Vector2f lastPoint = points.back();

            // Calculate midpoint between random vertex and the last point
            Vector2f newPoint = (selectedVertex + lastPoint) / 2.0f;

            // Push back the newly generated coordinate
            points.push_back(newPoint);
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        // Draw vertices
        for(int i = 0; i < vertices.size(); i++)
        {
            CircleShape vertex(5);
            vertex.setFillColor(Color::Blue);
            vertex.setPosition(vertices[i]);
            window.draw(vertex);
        }
        // Draw points
        for(int i = 0; i < points.size(); i++)
        {
            CircleShape point(2);
            point.setFillColor(Color::Red);
            point.setPosition(points[i]);
            window.draw(point);
        }
        window.display();
    }
    return 0;
}

