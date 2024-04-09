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
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(800, 600);
    // Create and open a window for the game
 RenderWindow window(vm, "Triangle Algorithm", Style::Default);
window.setVerticalSyncEnabled(false); // Disable VSync

Font font;
if (!font.loadFromFile("arial.ttf")) {
    cerr << "Failed to load font file!" << endl;
    // Add fallback font or exit the program gracefully
    return EXIT_FAILURE;
}

    Text instructions;
    instructions.setFont(font);
    instructions.setString("Click on any three points on the screen to create the vertices for the triangle.\nClick on a fourth point to start the algorithm.");
    instructions.setCharacterSize(20);
    instructions.setFillColor(Color::White);
    instructions.setPosition(20, 20);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "Mouse X: " << event.mouseButton.x << endl;
                    cout << "Mouse Y: " << event.mouseButton.y << endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        window.clear();

        // Draw instructions
        window.draw(instructions);

        // Draw vertices
for (vector<Vector2f>::size_type i = 0; i < vertices.size(); i++)
{
    CircleShape vertex(5);
    vertex.setFillColor(Color::Blue);
    vertex.setPosition(vertices[i]);
    window.draw(vertex);
}

// Draw points
for (vector<Vector2f>::size_type i = 0; i < points.size(); i++)
{
    CircleShape point(5);
    point.setFillColor(Color::Red);
    point.setPosition(points[i]);
    window.draw(point);
}

        window.display();
    }

    return EXIT_SUCCESS;
}
